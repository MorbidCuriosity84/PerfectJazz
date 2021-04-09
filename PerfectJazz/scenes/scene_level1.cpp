#include "scene_level1.h"
#include "../components/cmp_player_physics.h"
#include "../components/cmp_background_physics.h"
#include "../components/cmp_sprite.h"
#include "../game.h"
#include <LevelSystem.h>
#include <iostream>
#include <thread>

using namespace std;
using namespace sf;

static shared_ptr<Entity> player;
static shared_ptr<Entity> background;
static shared_ptr<Entity> background2;
static shared_ptr<Entity> overbackground;
static shared_ptr<Entity> overbackground2;
sf::Texture texture;
sf::Texture texture2;
sf::Texture texture_clouds1;
sf::Texture texture_clouds2;

void Level1Scene::Load() {
	cout << " Scene 1 Load" << endl;
	ls::loadLevelFile("res/levels/level_1.txt", 40.0f);

	auto ho = Engine::getWindowSize().y - (ls::getHeight() * 40.f);
	ls::setOffset(Vector2f(0, ho));

	//Create background	
	background = makeEntity();
	background2 = makeEntity();
	overbackground = makeEntity();
	overbackground2 = makeEntity();


	if (texture.loadFromFile("res/img/backgrounds/desert_900.png")) {
		//Loading backgroun sprite 1
		auto dessert_b = background->addComponent<SpriteComponent>();
		dessert_b->getSprite().setTexture(texture);
		background->addComponent<BackgroundPhysicsComponent>(Vector2f((float)texture.getSize().x, (float)texture.getSize().y));
		background->setPosition(Vector2f((Engine::getWindowSize().x - (float)texture.getSize().x) / 2, 0.f));
		
		//Loading backgroun sprite 2
		texture2.loadFromFile("res/img/backgrounds/desert_900.png");
		auto dessert_b2 = background2->addComponent<SpriteComponent>();
		dessert_b2->getSprite().setTexture(texture2);
		background2->addComponent<BackgroundPhysicsComponent>(Vector2f((float)texture2.getSize().x, (float)texture2.getSize().y));
		background2->setPosition(Vector2f((Engine::getWindowSize().x - (float)texture2.getSize().x) / 2, -(float)texture2.getSize().y + 1.f));
	
		//Loading over background sprite1
		texture_clouds1.loadFromFile("res/img/backgrounds/desert_clouds.png");
		auto cloud_b = overbackground->addComponent <SpriteComponent>();
		cloud_b->getSprite().setTexture(texture_clouds1);
		overbackground->addComponent<BackgroundPhysicsComponent>(Vector2f((float)texture_clouds1.getSize().x, (float)texture_clouds1.getSize().y));
		overbackground->setPosition(Vector2f((Engine::getWindowSize().x - (float)texture.getSize().x) / 2, 0.f));
		auto b = overbackground->GetCompatibleComponent<BackgroundPhysicsComponent>()[0];
		b->ChangeVelocity(Vector2f(0.f, 30.f));

		//Loading over background sprite2
		texture_clouds2.loadFromFile("res/img/backgrounds/desert_clouds_rotated.png");
		auto cloud_b2 = overbackground2->addComponent <SpriteComponent>();
		cloud_b2->getSprite().setTexture(texture_clouds2);
		overbackground2->addComponent<BackgroundPhysicsComponent>(Vector2f((float)texture_clouds2.getSize().x, (float)texture_clouds2.getSize().y));
		overbackground2->setPosition(Vector2f((Engine::getWindowSize().x - (float)texture.getSize().x) / 2, - (float)texture_clouds2.getSize().y));
		auto b2 = overbackground2->GetCompatibleComponent<BackgroundPhysicsComponent>()[0];
		b2->ChangeVelocity(Vector2f(0.f, 65.f));
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
	cout << " Scene 1 Load Done" << endl;
	setLoaded(true);

	while (Engine::GetWindow().isOpen()) {

	}
}

void Level1Scene::UnLoad() {
	cout << "Scene 1 Unload" << endl;
	player.reset();
	background.reset();
	background2.reset();
	overbackground.reset();
	overbackground2.reset();
	ls::unload();
	Scene::UnLoad();
}

void Level1Scene::Update(const double& dt) 
{
	if (background->getPosition().y > Engine::getWindowSize().y) {
		background->setPosition(Vector2f((Engine::getWindowSize().x - (float)texture.getSize().x) / 2,
			background2->getPosition().y - texture.getSize().y + 1.f));
		cout << "out" << endl;
	}

	if (background2->getPosition().y > Engine::getWindowSize().y) {
		background2->setPosition(Vector2f((Engine::getWindowSize().x - (float)texture.getSize().x) / 2,
			background->getPosition().y - texture.getSize().y + 1.f));
		cout << "out2" << endl;
	}

	//TODO set the y value from SetPosition to a range of random
	if (overbackground->getPosition().y > Engine::getWindowSize().y) {
		overbackground->setPosition(Vector2f((Engine::getWindowSize().x - (float)texture.getSize().x) / 2, -(float)texture_clouds1.getSize().y));
	}

	if (overbackground2->getPosition().y > Engine::getWindowSize().y) {
		overbackground2->setPosition(Vector2f((Engine::getWindowSize().x - (float)texture.getSize().x) / 2, -(float)texture_clouds1.getSize().y * 3));
	}
	Scene::Update(dt);
}

void Level1Scene::Render() {
	ls::render(Engine::GetWindow());
	Scene::Render();
}