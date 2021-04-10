#include "scene_level3.h"
#include "../components/cmp_player_physics.h"
#include "../components/cmp_background_physics.h"
#include "../components/cmp_enemy_physics.h"
#include "../components/cmp_enemy_turret.h"
#include "../components//cmp_hurt_player.h"
#include "../components/cmp_sprite.h"
#include "../game.h"
#include <LevelSystem.h>
#include <iostream>
#include <thread>
#include "../components/cmp_text.h"

using namespace std;
using namespace sf;

static shared_ptr<Entity> player;
static shared_ptr<Entity> background;
static shared_ptr<Entity> background2;
static shared_ptr<Entity> overbackground;
static shared_ptr<Entity> overbackground2;
static vector<shared_ptr<Entity>> enemies;
sf::Texture sc3_backgroundtexture_1;
sf::Texture sc3_backgroundtexture_2;
sf::Texture sc3_overbackgroundtexture_1;
sf::Texture sc3_overbackgroundtexture_2;
sf::Texture playerTexture;
sf::IntRect playerRectangle;
sf::View leftView;
sf::View rightView;
sf::View mainView;
sf::Clock timer;

void Level3Scene::Load() {
	cout << " Scene 3 Load" << endl;
	ls::loadLevelFile("res/levels/wave1.txt", mainView.getSize().x / 16);

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
	sf::View tempMain(sf::FloatRect(0, 0, Engine::getWindowSize().x / 1.666, Engine::getWindowSize().y));
	mainView = tempMain;
	mainView.setViewport(sf::FloatRect(0.2f, 0, 0.6f, 1.f));
	//views.push_back(mainView);	


	auto ho = Engine::getWindowSize().y - (ls::getHeight() * 40.f);
	ls::setOffset(Vector2f(0, ho));

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
		player = makeEntity();
		player->setPosition(Vector2f(mainView.getSize().x / 2, mainView.getSize().y - 100.f));
		player->setView(mainView);
		auto s = player->addComponent<SpriteComponent>();
		playerTexture.loadFromFile("res/img/player/player_900.png");
		playerRectangle.left = (playerTexture.getSize().x / 5) * 2;
		playerRectangle.top = (playerTexture.getSize().y / 2) * 0;
		playerRectangle.width = (playerTexture.getSize().x / 5);
		playerRectangle.height = (playerTexture.getSize().y / 2);
		s->getSprite().setTexture(playerTexture);
		s->getSprite().setTextureRect(playerRectangle);
		s->getSprite().setOrigin(playerTexture.getSize().x / 10, playerTexture.getSize().y / 4);
		player->addComponent<PlayerPhysicsComponent>(Vector2f(playerTexture.getSize().x / 5, playerTexture.getSize().y / 2));
		player->addTag("player");
	}

	cout << "main view size: " << mainView.getSize();
	//Create Enemies
	{
		for (int i = 0; i < ls::findTiles(ls::ENEMY).size(); i++) {
			auto en = makeEntity();
			en->setView(mainView);
			auto s = en->addComponent<ShapeComponent>();
			s->setShape<sf::CircleShape>(15.f);
			s->getShape().setFillColor(Color::Red);
			s->getShape().setOrigin(15.f, 15.f);
			vector<Vector2ul> tile = ls::findTiles(ls::ENEMY);
			en->setPosition(Vector2f(ls::getTilePosition(tile[i]).x + 15.f, ls::getTilePosition(tile[i]).y - 500.f));
			en->addComponent<EnemyPhysicsComponent>(Vector2f(15.f, 15.f));
			en->addTag("enemies");
		}
	}



	//Create text for left and right boxes
	{
		auto txt = makeEntity();
		txt->setView(leftView);
		auto t = txt->addComponent<TextComponent>("This is the left view");
		t->setFontSize(18);

		auto txt2 = makeEntity();
		txt2->setView(rightView);
		auto t2 = txt2->addComponent<TextComponent>("This is the right view");
		t2->setFontSize(18);
	}

	//std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	cout << " Scene 1 Load Done" << endl;
	setLoaded(true);
	timer.restart();
}

void Level3Scene::UnLoad() {
	cout << "Scene 3 Unload" << endl;
	ls::unload();
	player.reset();
	background.reset();
	background2.reset();
	overbackground.reset();
	overbackground2.reset();
	for (auto e : enemies) {
		e.reset();
	}
	Scene::UnLoad();
}

void Level3Scene::Update(const double& dt) {
	if (background->getPosition().y > Engine::getWindowSize().y) {
		background->setPosition(Vector2f((mainView.getSize().x - (float)sc3_backgroundtexture_1.getSize().x),
			background2->getPosition().y - sc3_backgroundtexture_1.getSize().y + 1.f));
		cout << "out" << endl;
	}
	if (background2->getPosition().y > Engine::getWindowSize().y) {
		background2->setPosition(Vector2f((mainView.getSize().x - (float)sc3_backgroundtexture_1.getSize().x),
			background->getPosition().y - sc3_backgroundtexture_1.getSize().y + 1.f));
		cout << "out2" << endl;
	}

	//TODO set the y value from SetPosition to a range of random
	if (overbackground->getPosition().y > Engine::getWindowSize().y) {
		overbackground->setPosition(Vector2f((mainView.getSize().x - (float)sc3_backgroundtexture_1.getSize().x),
			-(float)sc3_overbackgroundtexture_2.getSize().y));
	}
	if (overbackground2->getPosition().y > Engine::getWindowSize().y) {
		overbackground2->setPosition(Vector2f((mainView.getSize().x - (float)sc3_backgroundtexture_1.getSize().x),
			-(float)sc3_overbackgroundtexture_2.getSize().y * 3));
	}

	//Update player texture
	auto pPhysics = player->GetCompatibleComponent<PlayerPhysicsComponent>();
	auto pSprite = player->GetCompatibleComponent<SpriteComponent>();

	if (timer.getElapsedTime().asSeconds() > 0.1f) {

		//Check if the loaded sprite is the bottom, if so, load the top. And viceversa
		if (playerRectangle.top == playerTexture.getSize().y / 2) { playerRectangle.top = 0; }
		else { playerRectangle.top = playerTexture.getSize().y / 2; }

		//Check if it's loaded the right sprite for the movement
		if (pPhysics[0]->GetDirection() == "right") {
			if (timer.getElapsedTime().asSeconds() > 0.2f) {
				playerRectangle.left = (playerTexture.getSize().x / 5) * 4;
			}
			else { playerRectangle.left = (playerTexture.getSize().x / 5) * 3; }
		}
		if (pPhysics[0]->GetDirection() == "left") {
			if (timer.getElapsedTime().asSeconds() > 0.2f) {
				playerRectangle.left = (playerTexture.getSize().x / 5) * 0;
			}
			else { playerRectangle.left = (playerTexture.getSize().x / 5) * 1; }
		}
		if (pPhysics[0]->GetDirection() == "none") {
			playerRectangle.left = (playerTexture.getSize().x / 5) * 2;
			timer.restart();
		}
		pSprite[0]->getSprite().setTextureRect(playerRectangle);
	}

	Scene::Update(dt);
}

void Level3Scene::Render() {
	ls::render(Engine::GetWindow());
	Scene::Render();
}

