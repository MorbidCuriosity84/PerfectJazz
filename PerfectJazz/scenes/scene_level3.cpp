#include "scene_level3.h"
#include <iostream>
#include <thread>
#include <LevelSystem.h>
#include "../enemies/creates_enemies.h"
#include "../player/creates_player.h"
#include "../panels/creates_panels.h"
#include "../powerups/creates_powerups.h"
#include "../background/create_background.h"
#include "../game.h"
#include "../pools/entityPool.h"
#include <system_physics.h>
#include "../pools/powerupPool.h"
#include "../pools/enemyPool.h"
#include "../enemies/levelManager.h"
#include "../movement/cmp_move_sine.h"


using namespace std;
using namespace sf;

sf::View leftView;
sf::View rightView;
sf::View mainView;
sf::View menuView;
sf::SoundBuffer sBuffs[128];
sf::Sound sounds[128];

const unsigned int soundsPerBuffer = 8;

void Level3Scene::Load() {
  	cout << " Scene 3 Load" << endl;

	Engine::isLevelComplete = false;
	Engine::_nextScene = &level3;

 	for (int sndInt = PLAYER_DIE_1; sndInt != PICKUP_5; sndInt++) {
		sBuffs[sndInt].loadFromFile(soundFilenames[sndInt]);
		sounds[sndInt].setBuffer(sBuffs[sndInt]);
		sounds[sndInt].setVolume(25.f);
		sounds[sndInt].setPitch(1.f);
	}

	//MARK This is temporary, once title screen is loaded then the array should be initialised
	//then its just a case of calling the musicArray with the relevvant music enum
	for (int i = 0; i < 8; i++) {
		if (!musicArray[i].openFromFile(musicFiles[i])) {
		}
		else {
			cout << "Loaded music " << musicFiles[i] << endl;
		}
	}

	musicArray[MUSIC_LEVEL_3].setPosition(0, 1, 50);
	musicArray[MUSIC_LEVEL_3].setVolume(25);
	musicArray[MUSIC_LEVEL_3].setLoop(true);
	musicArray[MUSIC_LEVEL_3].play();		
		

	//Create background	
	{
 		Background::createBackground(dynamic_cast<Scene*>(&level3));
	}
	
	//Create powerups
	{
		PowerupPool::init(&level3);
		Powerups::createPowerups(dynamic_cast<Scene*>(&level3));
	}

	EntityPool::init(&level3);
	//Create player
	{
		//Player::createPlayer(dynamic_cast<Scene*>(&level3));
		Player::createPlayerFromSettings(&level3);
	}

	EnemyPool::init(&level3);
	//Create Enemies
	{
		LevelManager::loadLevel(1);
		Enemies::createEnemies("wave1", dynamic_cast<Scene*>(&level3));
	}

	//Create text for left and right boxes
	{
   		Panels::createPanels(dynamic_cast<Scene*>(&level3));
	}

	//std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	cout << " Scene 3 Load Done" << endl;
	setLoaded(true);	
}

void Level3Scene::UnLoad() {
	cout << "Scene 3 Unload" << endl;
	ls::unload();

	for (auto e : EntityPool::pool) {
		e->clearComponents();
		e.reset();
	}
	for (auto e : PowerupPool::pwp_pool) {
		e->clearComponents();
		e.reset();
	}
	for (auto e : EnemyPool::en_pool) {
		e->clearComponents();
		e.reset();
	}
	Scene::UnLoad();
}

void Level3Scene::Update(const double& dt) {
	LevelManager::update(&level3, false, 4, dt);
	Scene::Update(dt);
}

void Level3Scene::Render() {
	ls::render(Engine::GetWindow());
	Scene::Render();
}
