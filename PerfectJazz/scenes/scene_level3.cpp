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

using namespace std;
using namespace sf;

static shared_ptr<Entity> player;
static shared_ptr<Entity> background;
static shared_ptr<Entity> background2;
static shared_ptr<Entity> overbackground;
static shared_ptr<Entity> overbackground2;
static vector<shared_ptr<Entity>> enemies;

void Level3Scene::Load() {
	cout << " Scene 3 Load" << endl;	
	ls::loadLevelFile("res/levels/wave1.txt", 40.0f);

	auto ho = Engine::getWindowSize().y - (ls::getHeight() * 40.f);
	ls::setOffset(Vector2f(0, ho));	

	//Create background	
	background = makeEntity();
	background2 = makeEntity();
	overbackground = makeEntity();
	overbackground2 = makeEntity();
	sf::Clock clock;
	sf::Texture texture;
	sf::Texture texture2;
	sf::Texture texture_clouds1;
	sf::Texture texture_clouds2;
	sf::Time lastTime;
	sf::Vector2f scale;

	if (texture.loadFromFile("res/img/backgrounds/desert_900.png")) {
		texture2.loadFromFile("res/img/backgrounds/desert_900.png");
				
		//Creates target size for texture, used to create scale factor
		sf::Vector2f targetSize = { Engine::getWindowSize().x * 0.6f, Engine::getWindowSize().y * 1.0f };

		auto dessert_b = background->addComponent<SpriteComponent>();
		auto dessert_b2 = background2->addComponent<SpriteComponent>();
		dessert_b->getSprite().setTexture(texture);
		dessert_b2->getSprite().setTexture(texture2);
		//Scale factor applied to all textures
		//TODO create scaling component rather than hardcode it here
		scale = { targetSize.x / dessert_b->getSprite().getGlobalBounds().width, targetSize.y / dessert_b->getSprite().getGlobalBounds().height },
		dessert_b->getSprite().setScale(scale);
		dessert_b2->getSprite().setScale(scale);		

		background->addComponent<BackgroundPhysicsComponent>(Vector2f((float)texture.getSize().x * scale.x, (float)texture.getSize().y * scale.y));
		background->setPosition(Vector2f((Engine::getWindowSize().x - (float)texture.getSize().x * scale.x) / 2, 0.f));
		background2->addComponent<BackgroundPhysicsComponent>(Vector2f((float)texture2.getSize().x * scale.x, (float)texture2.getSize().y * scale.y));
		background2->setPosition(Vector2f((Engine::getWindowSize().x - (float)texture.getSize().x * scale.x) / 2, -(float)texture2.getSize().y * scale.y + 1.f));


		//Loading over background sprite1
		texture_clouds1.loadFromFile("res/img/backgrounds/desert_clouds.png");
		auto cloud_b = overbackground->addComponent <SpriteComponent>();
		cloud_b->getSprite().setTexture(texture_clouds1);
		cloud_b->getSprite().setScale(scale);
		overbackground->addComponent<BackgroundPhysicsComponent>(Vector2f((float)texture_clouds1.getSize().x * scale.x, (float)texture_clouds1.getSize().y * scale.y));
		overbackground->setPosition(Vector2f((Engine::getWindowSize().x - (float)texture.getSize().x * scale.x) / 2, 0.f));
		auto b = overbackground->GetCompatibleComponent<BackgroundPhysicsComponent>()[0];
		b->ChangeVelocity(Vector2f(0.f, 30.f));

		//Loading over background sprite2
		texture_clouds2.loadFromFile("res/img/backgrounds/desert_clouds_rotated.png");
		auto cloud_b2 = overbackground2->addComponent <SpriteComponent>();
		cloud_b2->getSprite().setTexture(texture_clouds2);
		cloud_b2->getSprite().setScale(scale);
		overbackground2->addComponent<BackgroundPhysicsComponent>(Vector2f((float)texture_clouds2.getSize().x * scale.x, (float)texture_clouds2.getSize().y * scale.y));
		overbackground2->setPosition(Vector2f((Engine::getWindowSize().x - (float)texture.getSize().x * scale.x) / 2, -(float)texture_clouds2.getSize().y * scale.y));
		auto b2 = overbackground2->GetCompatibleComponent<BackgroundPhysicsComponent>()[0];
		b2->ChangeVelocity(Vector2f(0.f, 65.f));
	}

	//Create player
	{
		player = makeEntity();
		player->setPosition({ gameWidth / 2.f, gameHeight / 2.f });
		auto s = player->addComponent<ShapeComponent>();
		s->setShape<sf::RectangleShape>(Vector2f(20.f, 30.f));
		s->getShape().setFillColor(Color::Magenta);
		s->getShape().setOrigin(10.f, 15.f);		
		player->addComponent<PlayerPhysicsComponent>(Vector2f(20.f, 30.f));
		player->addTag("player");
	}

	//Create Enemies
	{
		for (int i = 0; i < ls::findTiles(ls::ENEMY).size(); i++)
		{
			auto en = makeEntity();
			en->setPosition(ls::getTilePosition(ls::findTiles(ls::ENEMY)[i]));
			
			en->setPosition({ en->getPosition().x + ((gameWidth /2.f) - (0.5f * ls::getWidth() * ls::getTileSize())) , en->getPosition().y - gameHeight });
			
			cout << "Position " + to_string(ls::getTilePosition(ls::findTiles(ls::ENEMY)[i]).x);
			auto s = en->addComponent<ShapeComponent>();
			s->setShape<sf::CircleShape>(15.f);
			s->getShape().setFillColor(Color::Red);
			s->getShape().setOrigin(7.5f, 7.5f);			

			en->addComponent<EnemyPhysicsComponent>(Vector2f(15.f, 15.f));			
			en->addComponent<EnemyTurretComponent>();			
			en->addComponent<HurtComponent>();
		}
	}

	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	cout << " Scene 1 Load Done" << endl;
	setLoaded(true);

	while (Engine::GetWindow().isOpen()) {
		if (background->getPosition().y > Engine::getWindowSize().y) {
			background->setPosition(Vector2f((Engine::getWindowSize().x - (float)texture.getSize().x * scale.x) / 2,
				background2->getPosition().y - texture.getSize().y * scale.y + 1.f));
			cout << "out" << endl;
		}

		if (background2->getPosition().y > Engine::getWindowSize().y) {
			background2->setPosition(Vector2f((Engine::getWindowSize().x - (float)texture.getSize().x * scale.x) / 2,
				background->getPosition().y - texture.getSize().y * scale.y + 1.f));
			cout << "out2" << endl;
		}

		//TODO set the y value from SetPosition to a range of random
		if (overbackground->getPosition().y > Engine::getWindowSize().y) {
			overbackground->setPosition(Vector2f((Engine::getWindowSize().x - (float)texture.getSize().x * scale.x) / 2, -(float)texture_clouds1.getSize().y * scale.y));
		}

		if (overbackground2->getPosition().y > Engine::getWindowSize().y) {
			overbackground2->setPosition(Vector2f((Engine::getWindowSize().x - (float)texture.getSize().x * scale.x) / 2, -(float)texture_clouds1.getSize().y * scale.y * 3));
		}
	}
}

void Level3Scene::UnLoad() {
	cout << "Scene 3 Unload" << endl;
	ls::unload();
	Scene::UnLoad();
}


void Level3Scene::Update(const double& dt) {

	Scene::Update(dt);
}

void Level3Scene::Render() {
	ls::render(Engine::GetWindow());	
	Scene::Render();
}

