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
std::string Engine::_gameName;
bool Engine::isGamePaused;
bool Engine::isPausedMenu;
bool Engine::isMenu;
bool Engine::isLevelComplete;
bool Engine::isLoading;
bool Engine::isLevelFinished;
bool Engine::isInfiniteLevel;
bool Engine::isGameComplete;
double Engine::FPS;
int Engine::currentPlayerLevel;
int Scene::deadEnemies;
float deathTimer;
bool isDead;
static bool loading = false;
static float loadingspinner = 0.1f;
static float loadingTime;
static RenderWindow* _window;
static Panels panels;

void Loading_update(float dt, const Scene* const scn) {
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
	const float dt = clock.restart().asSeconds();
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
			FPS = davg;
		}
	}

	if (loading) {
		Loading_update(dt, _activeScene);
	}
	else if (_activeScene != nullptr) {
		_activeScene->Update(dt);
		// Checks if the game is paused before performing a physics update
		if (!isGamePaused) { Physics::update(dt); }
	}
}

// Renders the active scene
void Engine::Render(RenderWindow& window) {
	if (loading) {
		Loading_render();
	}
	else if (_activeScene != nullptr) {
		_activeScene->Render();
	}

	Renderer::render();
}

// Updates the size of the views
void Engine::updateViewsSize() {
	//Updates the size of the left view
	sf::View tempLeft(sf::FloatRect(0, 0, Engine::getWindowSize().x / 5, Engine::getWindowSize().y));
	leftView = tempLeft;
	leftView.setViewport(sf::FloatRect(0, 0, 0.2f, 1.f));
	//Updates the size of the right view
	sf::View tempRight(sf::FloatRect(0, 0, Engine::getWindowSize().x / 5, Engine::getWindowSize().y));
	rightView = tempRight;
	rightView.setViewport(sf::FloatRect(0.8f, 0, 0.2f, 1.f));
	//Updates the size of the main view
	sf::View tempMain(sf::FloatRect(0, 0, (round)(Engine::getWindowSize().x / 1.66666), Engine::getWindowSize().y));
	mainView = tempMain;
	mainView.setViewport(sf::FloatRect(0.2f, 0, 0.6f, 1.f));
	//Updates the size of the  menuView
	sf::View tempMenu(sf::FloatRect(0, 0, Engine::getWindowSize().x, Engine::getWindowSize().y));
	menuView = tempMenu;
	menuView.setViewport(sf::FloatRect(0, 0, 1.f, 1.f));
}

void Engine::Start(unsigned int width, unsigned int height,
	const std::string& gameName, Scene* scn) {
	RenderWindow window(VideoMode(width, height), gameName, sf::Style::None);
	auto desktop = sf::VideoMode::getDesktopMode();
	window.setPosition(Vector2i(desktop.width / 2 - window.getSize().x / 2, desktop.height / 2 - window.getSize().y / 2));
	//Limits the framerate to 60
	window.setFramerateLimit(60);
	_gameName = gameName;
	_window = &window;
	// Sets the initial values for the booleans
	isLoading = false;
	isGamePaused = true;
	isMenu = true;
	isPausedMenu = true;
	isLevelFinished = false;
	isInfiniteLevel = false;
	isGameComplete = false;
	currentPlayerLevel = 0;

	Renderer::initialise(window);
	Physics::initialise();
	ChangeScene(scn);

	//Updates the view, so the elements inside don't auto-resize
	updateViewsSize();

	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
			}
			//If the window is resized, the views will be set accordinly, avoiding components to be auto-resized
			if (event.type == sf::Event::Resized) {
				updateViewsSize();
			}
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

	// Before unloading, checks if the game is paused or the menu is the paused menu
	if (isGamePaused && !isPausedMenu && _lastScene != nullptr) {
		_lastScene->UnLoad();
		old = nullptr;
	}

	_activeScene = s;

	// Before unloading, checks if the game is paused or the menu is the paused menu
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

		// This are cheeky cheats for the demo
		if (sf::Keyboard::isKeyPressed(Keyboard::Num1)) {
			player->GetCompatibleComponent<PlayerComponent>()[0]->_playerSettings.shopPoints += 10000;
		}
		// This are cheeky cheats for the demo
		if (sf::Keyboard::isKeyPressed(Keyboard::Num3)) {
			Engine::isMenu = true;
			Engine::isGamePaused = true;
			Engine::isPausedMenu = true;
			musicArray[currentLvlMusicIndex].pause();
			musicArray[MUSIC_UPGRADE_MENU].play();
			Engine::ChangeScene(&upgradeMenu);
		}
		// Opens the pause menu
		if (sf::Keyboard::isKeyPressed(Keyboard::Escape)) {
			Engine::isGamePaused = true;
			Engine::isMenu = true;
			Engine::isPausedMenu = true;
			musicArray[currentLvlMusicIndex].pause();
			Engine::ChangeScene(&pauseMenu);
		}
		auto playerCMP = player->GetCompatibleComponent<PlayerComponent>()[0];
		// Checks if the player is alive. If not, and the lifes more than 0,
		// sets the death timer and revives the player
		if (!player->isAlive() && playerCMP->_playerSettings.lifes > 0) {
			deathTimer += dt;
			if (deathTimer > 2) {
				playerCMP.get()->revive();
				deathTimer = 0;
			}
		}
		//Only load GameOver once, then keep updating the scene as normal
		if (!isDead && playerCMP->_playerSettings.lifes <= 0) {
			GameOver();
			isDead = true;
		}
		ents.update(dt);
		Panels::update(dt);
		Powerups::update(dt);
	}
}
// Displayes a "GAME OVER" text when the player is dead
void Scene::GameOver() {
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

// When the level is over, ccreates a text component that says "LEVEL COMPLETE"
void Scene::levelOver() {
	Engine::isLevelComplete = true;
	// If the player is not dead, sets the text setttigns and displays the text 
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

// When the level is over, ccreates a text component that says "GAME COMPLETE"
void Scene::gameComplete() {
	Engine::isGameComplete = true;
	// If the player is not dead, sets the text setttigns and displays the text 
	if (!isDead) {
		auto ent = player->scene->makeEntity();
		ent->setView(mainView);
		auto t = ent->addComponent<TextComponent>("GAME COMPLETE!");
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

// Unloads the scene
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