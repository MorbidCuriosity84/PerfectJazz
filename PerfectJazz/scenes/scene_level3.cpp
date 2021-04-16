#include "scene_level3.h"
#include <iostream>
#include <thread>
#include <LevelSystem.h>
#include "../components/cmp_player_physics.h"
#include "../components/cmp_background_physics.h"
#include "../components/cmp_sprite.h"
#include "../components/cmp_text.h"
#include "../components/cmp_hp.h"
#include "../components/cmp_damage.h"
#include "../enemies/create_enemies.h"
#include "../player/create_player.h"
#include "../game.h"


using namespace std;
using namespace sf;

static shared_ptr<Entity> background;
static shared_ptr<Entity> background2;
static shared_ptr<Entity> overbackground;
static shared_ptr<Entity> overbackground2;
sf::Texture sc3_backgroundtexture_1;
sf::Texture sc3_backgroundtexture_2;
sf::Texture sc3_overbackgroundtexture_1;
sf::Texture sc3_overbackgroundtexture_2;
sf::View leftView;
sf::View rightView;
sf::View mainView;


void Level3Scene::Load() {
	cout << " Scene 3 Load" << endl;

	//Create left view
	sf::View tempLeft(sf::FloatRect(0, 0, Engine::getWindowSize().x / 5, Engine::getWindowSize().y));
	leftView = tempLeft;
	leftView.setViewport(sf::FloatRect(0, 0, 0.2f, 1.f));
	//views.push_back(leftView);
	//Create right view
	sf::View tempRight(sf::FloatRect(0, 0, Engine::getWindowSize().x / 5, Engine::getWindowSize().y));
	rightView = tempRight;
	rightView.setViewport(sf::FloatRect(0.8f, 0, 0.2f, 1.f));
	//views.push_back(rightView);
	//Create main view
	sf::View tempMain(sf::FloatRect(0, 0, (floor)(Engine::getWindowSize().x / 1.66666), Engine::getWindowSize().y));
	mainView = tempMain;
	mainView.setViewport(sf::FloatRect(0.2f, 0, 0.6f, 1.f));
	//views.push_back(mainView);	


	//Create background	
	{
		background = makeEntity();
		background2 = makeEntity();
		overbackground = makeEntity();
		overbackground2 = makeEntity();

		//Loading background sprite1
		if (sc3_backgroundtexture_1.loadFromFile("res/img/backgrounds/desert_900.png")) {
			background->addComponent<BackgroundPhysicsComponent>(Vector2f((float)sc3_backgroundtexture_1.getSize().x, (float)sc3_backgroundtexture_1.getSize().y));
			background->setPosition(Vector2f((mainView.getSize().x - (float)sc3_backgroundtexture_1.getSize().x), 0.f));
			auto dessert_b = background->addComponent<SpriteComponent>();
			dessert_b->getSprite().setTexture(sc3_backgroundtexture_1);
			background->setView(mainView);
		}
		//Loading background sprite2
		if (sc3_backgroundtexture_2.loadFromFile("res/img/backgrounds/desert_900.png")) {
			background2->addComponent<BackgroundPhysicsComponent>(Vector2f((float)sc3_backgroundtexture_2.getSize().x, (float)sc3_backgroundtexture_2.getSize().y));
			background2->setPosition(Vector2f((mainView.getSize().x - (float)sc3_backgroundtexture_1.getSize().x), -(float)sc3_backgroundtexture_2.getSize().y + 1.f));
			auto dessert_b2 = background2->addComponent<SpriteComponent>();
			dessert_b2->getSprite().setTexture(sc3_backgroundtexture_2);
			background2->setView(mainView);
		}

		//Loading over background sprite1
		if (sc3_overbackgroundtexture_1.loadFromFile("res/img/backgrounds/desert_clouds.png")) {
			auto cloud_b = overbackground->addComponent <SpriteComponent>();
			cloud_b->getSprite().setTexture(sc3_overbackgroundtexture_1);
			overbackground->addComponent<BackgroundPhysicsComponent>(Vector2f((float)sc3_overbackgroundtexture_1.getSize().x, (float)sc3_overbackgroundtexture_1.getSize().y));
			overbackground->setPosition(Vector2f((mainView.getSize().x - (float)sc3_backgroundtexture_1.getSize().x), 0.f));
			auto b = overbackground->GetCompatibleComponent<BackgroundPhysicsComponent>()[0];
			b->ChangeVelocity(Vector2f(0.f, 30.f));
			overbackground->setView(mainView);
		}

		//Loading over background sprite2
		if (sc3_overbackgroundtexture_2.loadFromFile("res/img/backgrounds/desert_clouds_rotated.png")) {
			auto cloud_b2 = overbackground2->addComponent <SpriteComponent>();
			cloud_b2->getSprite().setTexture(sc3_overbackgroundtexture_2);
			overbackground2->addComponent<BackgroundPhysicsComponent>(Vector2f((float)sc3_overbackgroundtexture_2.getSize().x, (float)sc3_overbackgroundtexture_2.getSize().y));
			overbackground2->setPosition(Vector2f((mainView.getSize().x - (float)sc3_backgroundtexture_1.getSize().x), -(float)sc3_overbackgroundtexture_2.getSize().y));
			auto b2 = overbackground2->GetCompatibleComponent<BackgroundPhysicsComponent>()[0];
			b2->ChangeVelocity(Vector2f(0.f, 65.f));
			overbackground2->setView(mainView);
		}
	}

	//Create player
	{
		Player::createPlayer(dynamic_cast<Scene*>(&level3));
	}

	//Create Enemies
	{
		CreateEnemies::initiliseEnemies("wave1", dynamic_cast<Scene*>(&level3));
	}

	//Create text for left and right boxes
	{
		auto txt = makeEntity();
		txt->setView(leftView);
		auto t = txt->addComponent<TextComponent>("This is the left view");
		t->setFontSize(18u);

		auto txt2 = makeEntity();
		txt2->setView(rightView);
		auto t2 = txt2->addComponent<TextComponent>("This is the right view");
		t2->setFontSize(18u);
	}

	//std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	cout << " Scene 1 Load Done" << endl;
	setLoaded(true);
}

void Level3Scene::UnLoad() {
	cout << "Scene 3 Unload" << endl;
	ls::unload();
	for (auto e : enemies) {
		enemies.clear();
		e.reset();
	}
	for (auto b : playerBullets) {
		b.reset();
	}
	for (auto b : enemyBullets) {
		b.reset();
	}
	enemyBullets.clear();
	player.reset();
	bullet.reset();
	background.reset();
	background2.reset();
	overbackground.reset();
	overbackground2.reset();


	Scene::UnLoad();
}

void Level3Scene::Update(const double& dt) {
	//Update background
	{
		if (background->getPosition().y > Engine::getWindowSize().y) {
			background->setPosition(Vector2f((mainView.getSize().x - (float)sc3_backgroundtexture_1.getSize().x),
				background2->getPosition().y - sc3_backgroundtexture_1.getSize().y + 1.f));
		}
		if (background2->getPosition().y > Engine::getWindowSize().y) {
			background2->setPosition(Vector2f((mainView.getSize().x - (float)sc3_backgroundtexture_1.getSize().x),
				background->getPosition().y - sc3_backgroundtexture_1.getSize().y + 1.f));
		}
	}

	//Update overbackground
	{
		if (overbackground->getPosition().y > Engine::getWindowSize().y) {
			overbackground->setPosition(Vector2f((mainView.getSize().x - (float)sc3_backgroundtexture_1.getSize().x),
				-(float)sc3_overbackgroundtexture_2.getSize().y));
		}
		if (overbackground2->getPosition().y > Engine::getWindowSize().y) {
			overbackground2->setPosition(Vector2f((mainView.getSize().x - (float)sc3_backgroundtexture_1.getSize().x),
				-(float)sc3_overbackgroundtexture_2.getSize().y * 3));
		}
	}

	Scene::Update(dt);
}

void Level3Scene::Render() {
	ls::render(Engine::GetWindow());
	Scene::Render();
}