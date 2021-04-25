#include "scene_level3.h"
#include <iostream>
#include <thread>
#include <LevelSystem.h>
#include "system_physics.h"
#include "../enemies/creates_enemies.h"
#include "../player/creates_player.h"
#include "../panels/creates_panels.h"
#include "../powerups/creates_powerups.h"
#include "../background/create_background.h"
#include "../game.h"


using namespace std;
using namespace sf;
using namespace Physics;

sf::View leftView;
sf::View rightView;
sf::View mainView;

void Level3Scene::Load() {
	cout << " Scene 3 Load" << endl;

	EntityPool::init(this);
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
	sf::View tempMain(sf::FloatRect(0, 0, (round)(Engine::getWindowSize().x / 1.66666), Engine::getWindowSize().y));
	mainView = tempMain;

	mainView.setViewport(sf::FloatRect(0.2f, 0, 0.6f, 1.f));

	//views.push_back(mainView);	


	//Create background	
	{
		Background::createBackground(dynamic_cast<Scene*>(&level3));
	}

	//Create player
	{
		Player::createPlayer(dynamic_cast<Scene*>(&level3));
	}

	//Create Enemies
	{
		Enemies::createEnemies("wave1", dynamic_cast<Scene*>(&level3));
	}

	//Create text for left and right boxes
	{
		Panels::createPanels(dynamic_cast<Scene*>(&level3));
	}

	//Create powerups
	{
		Powerups::createPowerups(dynamic_cast<Scene*>(&level3));
	}

	//std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	cout << " Scene 1 Load Done" << endl;
	setLoaded(true);
}

void Level3Scene::UnLoad() {
	cout << "Scene 3 Unload" << endl;
	ls::unload();

	for (auto b : playerBullets) {
		b.reset();
	}
	for (auto b : enemyBullets) {
		b.reset();
	}
	enemyBullets.clear();
	player.reset();
	cout << Physics::GetWorld().get()->GetBodyCount() << endl;
	if (!Physics::GetWorld().get()->IsLocked()) {
		for (auto e : EntityPool::pool) {
			e.reset();			
		}
		EntityPool::pool->reset();
		EntityPool::poolPointer = NULL;				
	}
	cout << Physics::GetWorld().get()->GetBodyCount() << endl;
	Scene::UnLoad();
}

void Level3Scene::Update(const double& dt) {
	Scene::Update(dt);
}

void Level3Scene::Render() {
	ls::render(Engine::GetWindow());
	Scene::Render();
}