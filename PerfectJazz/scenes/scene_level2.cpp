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
#include "../settings/player_settings.h"
#include "../settings/weapon_settings.h"
#include "../settings/bullet_settings.h"
#include "../settings/texture_helper_settings.h"

using namespace std;
using namespace sf;


const unsigned int soundsPerBuffer = 8;

void Level2Scene::Load() {
	cout << " Scene 2 Load" << endl;

	Engine::isLevelComplete = false;
	Engine::_nextScene = &level3;

	//Loops through from the start of the sound enum (PLAYER_1_DIE) to the last PICKUP_5 and loads the relevent files
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

	musicArray[MUSIC_LEVEL_2].setPosition(0, 1, 50);
	musicArray[MUSIC_LEVEL_2].setVolume(25);
	musicArray[MUSIC_LEVEL_2].setLoop(true);
	musicArray[MUSIC_LEVEL_2].play();

	//Create background	
	{
		Background::createBackground(dynamic_cast<Scene*>(&level2));
	}

	//Create powerups
	{
		PowerupPool::init(&level2);
		Powerups::createPowerups(dynamic_cast<Scene*>(&level2));
	}

	EntityPool::init(&level2);
	//Create player
	{
		Player::createPlayer(dynamic_cast<Scene*>(&level2));
	}

	EnemyPool::init(&level2);
	//Create Enemies
	{
		LevelManager::loadLevel(2); //-- only needed for specific levels, infinite levels just need a call to LevelManager in the update
		//Enemies::createEnemies("wave1", dynamic_cast<Scene*>(&level2));
	}

	//Create text for left and right boxes
	{
		Panels::createPanels(dynamic_cast<Scene*>(&level2));
	}

	//std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	cout << " Scene 2 Load Done" << endl;
	setLoaded(true);
}

void Level2Scene::UnLoad() {
	cout << "Scene 2 Unload" << endl;
	ls::unload();
	//saving player settings
	/*auto pCMP = player->GetCompatibleComponent<PlayerComponent>()[0];
	pSettings = pCMP->_playerSettings;
	pWepSettings = pCMP->_weaponSettings;
	pBulSettings = pCMP->_bulletSettings;
	pBulletHelper = pCMP->_bulletTextureHelper;
	pTextHelper = pCMP->_playerTextureHelper;*/
	//unloading entities
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

void Level2Scene::Update(const double& dt) {
	LevelManager::update(&level2, false, 4, dt);
	Scene::Update(dt);
}

void Level2Scene::Render() {
	ls::render(Engine::GetWindow());
	Scene::Render();
}