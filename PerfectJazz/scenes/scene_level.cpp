#include "scene_level.h"
#include <iostream>
#include <LevelSystem.h>
#include "../enemies/creates_enemies.h"
#include "../player/creates_player.h"
#include "../panels/creates_panels.h"
#include "../powerups/creates_powerups.h"
#include "../background/create_background.h"
#include "../game.h"
#include "../pools/entityPool.h"
#include "../pools/powerupPool.h"
#include "../pools/enemyPool.h"
#include "../enemies/levelManager.h"

using namespace std;
using namespace sf;
static Panels panels;
sf::SoundBuffer sBuffs[128];
sf::Sound sounds[128];
sf::Music musicArray[8];

const unsigned int soundsPerBuffer = 8;

//Level scene is used to load levels
void LevelScene::Load() {
	cout << " Scene " << Engine::currentPlayerLevel << " Load" << endl;

	Scene::deadEnemies = 0;
	Engine::isLevelComplete = false;

	//Loops through from the start of the sound enum (PLAYER_1_DIE) to the last PICKUP_5 and loads the relevent files
	for (int sndInt = PLAYER_DIE_1; sndInt != PICKUP_5; sndInt++) {
		sBuffs[sndInt].loadFromFile(soundFilenames[sndInt]);
		sounds[sndInt].setBuffer(sBuffs[sndInt]);
		sounds[sndInt].setVolume(25.f);
		sounds[sndInt].setPitch(1.f);
	}

	//Sets the settings for the music, adjusting the volume, the loop and playing
	currentLvlMusicIndex = Engine::currentPlayerLevel + 2;
	musicArray[currentLvlMusicIndex].setPosition(0, 1, 50);
	musicArray[currentLvlMusicIndex].setVolume(25);
	musicArray[currentLvlMusicIndex].setLoop(true);
	musicArray[currentLvlMusicIndex].play();

	//Create background	
	{
		if (!Engine::isLoading) {
			Background::createBackground(dynamic_cast<Scene*>(&levelScene));
		}
	}

	//Create powerups
	{
		//Initializes powerups pool
		PowerupPool::init(&levelScene);
		Powerups::createPowerups(dynamic_cast<Scene*>(&levelScene));
	}

	//Initializes entity pool
	EntityPool::init(&levelScene);
	//Create player
	{
		if (!Engine::isLoading && !Engine::isLevelFinished) {
			Player::createPlayer(dynamic_cast<Scene*>(&levelScene));
		}

		else if (Engine::isLevelFinished) {
			Player::createPlayerFromSettings(dynamic_cast<Scene*>(&levelScene));
			Engine::isLevelFinished = false;
		}
	}

	EnemyPool::init(&levelScene);
	//Create Enemies
	{
		if (!Engine::isInfiniteLevel) {
			LevelManager::loadLevel(Engine::currentPlayerLevel++); //-- only needed for specific levels, infinite levels just need a call to LevelManager in the update
		}
	}

	//Create text for left and right boxes
	{
		Panels::createPanels(dynamic_cast<Scene*>(&levelScene));
	}

	//std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	cout << " Scene 2 Load Done" << endl;
	setLoaded(true);
}

//Unlodas the level scene, clearing all the components and panel
void LevelScene::UnLoad() {
	cout << "Scene Unload" << endl;
	ls::unload();
	panels.~Panels();

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

//Updates the scene
void LevelScene::Update(const double& dt) {
	if (Engine::currentPlayerLevel != -1) {	LevelManager::update(&levelScene, false, 4, dt);}
	if (Engine::currentPlayerLevel == -1) {	LevelManager::update(&levelScene, true, 4, dt);}
	Scene::Update(dt);
}

//Renders the components
void LevelScene::Render() {
	ls::render(Engine::GetWindow());
	Scene::Render();
}