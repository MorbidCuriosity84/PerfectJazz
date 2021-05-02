#include "engine.h"
#include "maths.h"
#include "system_physics.h"
#include "system_renderer.h"
#include "system_resources.h"
#include <SFML/Graphics.hpp>
#include <future>
#include <iostream>
#include <stdexcept>
#include "../lib_tile_level_loader/LevelSystem.h"
#include "../PerfectJazz/components/cmp_text.h"
#include "../PerfectJazz/components/cmp_enemy_physics.h"
#include "../PerfectJazz/panels/creates_panels.h"
#include "../PerfectJazz/player/cmp_player.h"
#include "../PerfectJazz/powerups/creates_powerups.h"
#include "../PerfectJazz/pools/entityPool.h"
#include "../PerfectJazz/services/load_save_game.h"


using namespace sf;
using namespace std;
Scene* Engine::_activeScene = nullptr;
Scene* Engine::_lastScene = nullptr;
Scene* Engine::_nextScene = nullptr;
std::string Engine::_gameName;
bool Engine::isGamePaused;
bool Engine::isPausedMenu;
bool Engine::isMenu;
bool Engine::isLevelComplete;
bool Engine::isLoading;
int Engine::currentPlayerLevel;
float deathTimer;
bool isDead;
int Scene::deadEnemies;

static bool loading = false;
static float loadingspinner = 0.1f;
static float loadingTime;
static RenderWindow* _window;
static Panels panels;

void Loading_update(float dt, const Scene* const scn) {
	//  cout << "Eng: Loading Screen\n";
	if (scn->isLoaded()) {
		cout << "Eng: Exiting Loading Screen\n";
		loading = false;
	}
	else {
		loadingspinner += 220.0f * dt;
		loadingTime += dt;
	}
}
void Loading_render() {
	// cout << "Eng: Loading Screen Render\n";
	static CircleShape octagon(80, 8);
	octagon.setOrigin(80, 80);
	octagon.setRotation(loadingspinner);
	octagon.setPosition(Vcast<float>(Engine::getWindowSize()) * .5f);
	octagon.setFillColor(Color(255, 255, 255, min(255.f, 40.f * loadingTime)));
	static Text t("Loading", *Resources::get<sf::Font>("RobotoMono-Regular.ttf"));
	t.setFillColor(Color(255, 255, 255, min(255.f, 40.f * loadingTime)));
	t.setPosition(Vcast<float>(Engine::getWindowSize()) * Vector2f(0.4f, 0.3f));
	Renderer::queue(&t, Engine::GetWindow().getView());
	Renderer::queue(&octagon, Engine::GetWindow().getView());
}

float frametimes[256] = {};
uint8_t ftc = 0;

void Engine::Update() {
	static sf::Clock clock;
	float dt = clock.restart().asSeconds();
	{
		frametimes[++ftc] = dt;
		static string avg = _gameName + " FPS:";
		if (ftc % 60 == 0) {
			double davg = 0;
			for (const auto t : frametimes) {
				davg += t;
			}
			davg = 1.0 / (davg / 255.0);
			_window->setTitle(avg + toStrDecPt(2, davg));
		}
	}

	if (loading) {
		Loading_update(dt, _activeScene);
	}
	else if (_activeScene != nullptr) {
		_activeScene->Update(dt);
		if (!isGamePaused) { Physics::update(dt); }
	}
}

void Engine::Render(RenderWindow& window) {
	if (loading) {
		Loading_render();
	}
	else if (_activeScene != nullptr) {
		_activeScene->Render();
	}

	Renderer::render();
}

void Engine::Start(unsigned int width, unsigned int height,
	const std::string& gameName, Scene* scn) {
	RenderWindow window(VideoMode(width, height), gameName, sf::Style::None);
	auto desktop = sf::VideoMode::getDesktopMode();
	window.setPosition(Vector2i(desktop.width / 2 - window.getSize().x / 2, desktop.height / 2 - window.getSize().y / 2));
	//Limits the framerate
	window.setFramerateLimit(60);
	_gameName = gameName;
	_window = &window;

	//Create left view
	sf::View tempLeft(sf::FloatRect(0, 0, Engine::getWindowSize().x / 5, Engine::getWindowSize().y));
	leftView = tempLeft;
	leftView.setViewport(sf::FloatRect(0, 0, 0.2f, 1.f));
	//Create right view
	sf::View tempRight(sf::FloatRect(0, 0, Engine::getWindowSize().x / 5, Engine::getWindowSize().y));
	rightView = tempRight;
	rightView.setViewport(sf::FloatRect(0.8f, 0, 0.2f, 1.f));
	//Create main view
	sf::View tempMain(sf::FloatRect(0, 0, (round)(Engine::getWindowSize().x / 1.66666), Engine::getWindowSize().y));
	mainView = tempMain;
	mainView.setViewport(sf::FloatRect(0.2f, 0, 0.6f, 1.f));

	isLoading = false;
	isGamePaused = false;
	isMenu = false;
	isPausedMenu = false;

	Renderer::initialise(window);
	Physics::initialise();
	ChangeScene(scn);

	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::Escape)) {
			isPausedMenu = false;
			isGamePaused = false;
			isMenu = false;
			if (_lastScene != nullptr) {
				_lastScene->UnLoad();
			}
			if (upgradeMenu.ents.list.size() != 0) {
				upgradeMenu.UnLoad();
			}
			window.close();
		}

		window.clear();

		Update();

		Render(window);
		window.display();
	}
	if (_activeScene != nullptr) {
		_activeScene->UnLoad();
		_activeScene = nullptr;
	}

	player.reset();
	window.close();
	Physics::shutdown();
	Renderer::shutdown();
}

std::shared_ptr<Entity> Scene::makeEntity() {
	auto e = make_shared<Entity>(this);
	ents.list.push_back(e);
	return std::move(e);
}

void Engine::setVsync(bool b) { _window->setVerticalSyncEnabled(b); }

void Engine::ChangeScene(Scene* s) {
	cout << "Eng: changing scene: " << s << endl;

	_lastScene = _activeScene;
	auto old = _activeScene;

	if (isGamePaused && !isPausedMenu && _lastScene != nullptr) {
		_lastScene->UnLoad();
		old = nullptr;
	}

	_activeScene = s;

	if (old != nullptr && !isGamePaused && !isPausedMenu) {
		old->UnLoad();
	}

	if (!s->isLoaded()) {
		cout << "Eng: Entering Loading Screen\n";
		loadingTime = 0.f;
		_activeScene->LoadAsync();
		loading = true;
		deathTimer = 0;
		isDead = false;
	}
}

void Scene::Update(const double& dt) {

	if (!Engine::isGamePaused) {
		if (sf::Keyboard::isKeyPressed(Keyboard::Num1)) {
			Engine::isGamePaused = true;
			Engine::isMenu = true;
			Engine::isPausedMenu = true;
			musicArray[currentLvlMusicIndex].pause();
			musicArray[MUSIC_UPGRADE_MENU].play();
			Engine::ChangeScene(&upgradeMenu);
		}
		if (sf::Keyboard::isKeyPressed(Keyboard::Space)) {
			Engine::isGamePaused = true;
			Engine::isMenu = true;
			Engine::isPausedMenu = true;
			musicArray[currentLvlMusicIndex].pause();
			Engine::ChangeScene(&pauseMenu);
		}
		auto playerCMP = player->GetCompatibleComponent<PlayerComponent>()[0];

		if (!player->isAlive() && playerCMP->_playerSettings.lifes > 0) {
			deathTimer += dt;
			if (deathTimer > 2) {
				playerCMP.get()->revive();
				deathTimer = 0;
			}
		}
		//Here only load GameOver once, then keep updating the scene as normal
		if (!isDead && playerCMP->_playerSettings.lifes <= 0) {
			GameOver();
			isDead = true;
		}
		ents.update(dt);
		Panels::update(dt);
		Powerups::update(dt);
	}
}

void Scene::GameOver() {
	//CARLOS - Text will draw over the sprites, then, because it wont be updated again, it will be drawn under the sprites
	if (!isDead) {
		auto ent = player->scene->makeEntity();
		ent->setView(mainView);
		auto t = ent->addComponent<TextComponent>("GAME OVER");
		t->setFontSize(220u);
		t->_text.setColor(Color::White);
		t->_text.setOutlineColor(Color::White);
		t->_text.setOutlineThickness(2);
		sf::FloatRect textRect = t->getLocalBounds();
		t->setOrigin(Vector2f((round)(textRect.left + textRect.width / 2.f), (round)(textRect.top + textRect.height / 2.f)));
		t->setPosition(Vector2f((round)(mainView.getSize().x / 2), (round)(mainView.getSize().y / 2)));
	}
}

void Scene::Render() { ents.render(); }

bool Scene::isLoaded() const {
	{
		std::lock_guard<std::mutex> lck(_loaded_mtx);
		// Are we already loading asynchronously?
		if (_loaded_future.valid() // yes
			&&                     // Has it finished?
			_loaded_future.wait_for(chrono::seconds(0)) ==
			future_status::ready) {
			// Yes
			_loaded_future.get();
			_loaded = true;
		}
		return _loaded;
	}
}

void Scene::levelOver() {
	Engine::isLevelComplete = true;
	if (!isDead) {
		auto ent = player->scene->makeEntity();
		ent->setView(mainView);
		auto t = ent->addComponent<TextComponent>("LEVEL COMPLETE");
		t->setFontSize(110u);
		t->_text.setColor(Color::White);
		t->_text.setOutlineColor(Color::White);
		t->_text.setOutlineThickness(2);
		sf::FloatRect textRect = t->getLocalBounds();
		t->setOrigin(Vector2f((round)(textRect.left + textRect.width / 2.f), (round)(textRect.top + textRect.height / 2.f)));
		t->setPosition(Vector2f((round)(mainView.getSize().x / 2), (round)(mainView.getSize().y / 2)));
	}
}

void Scene::setLoaded(bool b) {
	{
		std::lock_guard<std::mutex> lck(_loaded_mtx);
		_loaded = b;
	}
}

void Scene::UnLoad() {
	panels.~Panels();
	Physics::GetWorld().reset();
	ents.list.clear();
	setLoaded(false);
}

void Scene::LoadAsync() { _loaded_future = std::async(&Scene::Load, this); }

sf::Vector2u Engine::getWindowSize() { return _window->getSize(); }

sf::RenderWindow& Engine::GetWindow() { return *_window; }

namespace timing {
	// Return time since Epoc
	long long now() {
		return std::chrono::high_resolution_clock::now()
			.time_since_epoch()
			.count();
	}
	// Return time since last() was last called.
	long long last() {
		auto n = now();
		static auto then = now();
		auto dt = n - then;
		then = n;
		return dt;
	}
} // namespace timing

Scene::~Scene() { UnLoad(); }