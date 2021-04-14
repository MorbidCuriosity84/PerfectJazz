#include "scene_level2.h"
#include "../components/cmp_player_physics.h"
#include "../components/cmp_background_physics.h"
#include "../components/cmp_sprite.h"
#include "../game.h"
#include <LevelSystem.h>
#include <iostream>
#include <thread>

using namespace std;
using namespace sf;

static shared_ptr<Entity> background;
static shared_ptr<Entity> background2;
sf::Texture sc2_backgroundtexture_1;
sf::Texture sc2_backgroundtexture_2;


void Level2Scene::Load() {
	cout << " Scene 2 Load" << endl;
	ls::loadLevelFile("res/levels/level_2.txt", 40.0f);

	auto ho = Engine::getWindowSize().y - (ls::getHeight() * 40.f);
	ls::setOffset(Vector2f(0, ho));

	//Create background

	background = makeEntity();
	background2 = makeEntity();


	if (sc2_backgroundtexture_1.loadFromFile("res/img/backgrounds/desert_1080.png")) {
		sc2_backgroundtexture_2.loadFromFile("res/img/backgrounds/desert_1080.png");
		auto s = background->addComponent<SpriteComponent>();
		auto s2 = background2->addComponent<SpriteComponent>();
		s->getSprite().setTexture(sc2_backgroundtexture_1);
		s2->getSprite().setTexture(sc2_backgroundtexture_2);

		cout << sc2_backgroundtexture_2.getSize().y;
		background->addComponent<BackgroundPhysicsComponent>(Vector2f((float)sc2_backgroundtexture_1.getSize().x, (float)sc2_backgroundtexture_1.getSize().y));
		background->setPosition(Vector2f((Engine::getWindowSize().x - (float)sc2_backgroundtexture_1.getSize().x) / 2, 0.f));
		background2->addComponent<BackgroundPhysicsComponent>(Vector2f((float)sc2_backgroundtexture_2.getSize().x, (float)sc2_backgroundtexture_2.getSize().y));
		background2->setPosition(Vector2f((Engine::getWindowSize().x - (float)sc2_backgroundtexture_1.getSize().x) / 2, -(float)sc2_backgroundtexture_2.getSize().y + 1.f));
	}

	//Create player
	{
		player = makeEntity();
		player->setPosition(ls::getTilePosition(ls::findTiles(ls::START)[0]));
		auto s = player->addComponent<ShapeComponent>();
		s->setShape<sf::RectangleShape>(Vector2f(20.f, 30.f));
		s->getShape().setFillColor(Color::Magenta);
		s->getShape().setOrigin(10.f, 15.f);

		player->addComponent<PlayerPhysicsComponent>(Vector2f(20.f, 30.f));
	}

	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	cout << " Scene 2 Load Done" << endl;
	setLoaded(true);

	while (Engine::GetWindow().isOpen()) {
		if (background->getPosition().y > Engine::getWindowSize().y) {
			background->setPosition(Vector2f((Engine::getWindowSize().x - (float)sc2_backgroundtexture_1.getSize().x) / 2,
				background2->getPosition().y - sc2_backgroundtexture_1.getSize().y + 1.f));
			cout << "out" << endl;
		}

		if (background2->getPosition().y > Engine::getWindowSize().y) {
			background2->setPosition(Vector2f((Engine::getWindowSize().x - (float)sc2_backgroundtexture_1.getSize().x) / 2,
				background->getPosition().y - sc2_backgroundtexture_1.getSize().y + 1.f));
			cout << "out2" << endl;
		}
	}
}

void Level2Scene::UnLoad() {
	cout << "Scene 2 Unload" << endl;
	ls::unload();
	player.reset();
	background.reset();
	background2.reset();
	Scene::UnLoad();
}


void Level2Scene::Update(const double& dt) {

	Scene::Update(dt);
}

void Level2Scene::Render() {
	ls::render(Engine::GetWindow());
	Scene::Render();
}