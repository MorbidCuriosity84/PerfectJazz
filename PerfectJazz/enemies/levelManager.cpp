#include "levelManager.h"
#include "../settings/level_settings.h"
#include "LevelSystem.h"
#include "maths.h"
#include "../services/randomNumber.h"
#include "../settings/texture_helper_settings.h"
#include "../settings/enemy_settings.h"
#include "../settings/weapon_settings.h"
#include "../settings/bullet_settings.h"
#include "cmp_kamikaze.h"
#include "cmp_beserker.h"
#include "../pools/enemyPool.h"

std::queue<std::string> LevelManager::waves;
int LevelManager::enemyCount;
float LevelManager::levelOverTimer;
float LevelManager::kamikazeTimer;
float LevelManager::countTimer;
float LevelManager::singleTimer;
textureSettings _eTexHelper;
textureSettings _bTexHelper;
enemySettings _eSettings;
weaponSettings _wSettings;
bulletSettings _bSettings;

//Helps the level scene to load the waves
void LevelManager::loadLevel(int level) {
	std::queue<std::string> empty;
	std::swap(waves, empty);

	enemyCount = 0;
	levelOverTimer = 3.f;
	kamikazeTimer = 5.f;
	countTimer = 3.f;
	singleTimer = 5.f;
	Scene::deadEnemies = 0;
	if (level == -1) { // infinite level flag
		return;
	}
	for (char c : levels[level]) {
		int idx = c - 48; //converts level character to int        
		LevelManager::waves.push(waveFilenames[idx]);
	}
}

//Tells the scene when it's time for loading a new level,
//based on the number of enemies left for the current wave
void LevelManager::playLevel(Scene* s) {
	if (enemyCount == 0) {
		if (!waves.empty()) {
			Enemies::createEnemies(waves.front(), s);
			Scene::deadEnemies = 0;
			waves.pop();
		}
	}
	//Generates a number between 5 and 15, and uses it as a timer for spawning a kamikaze
	if (kamikazeTimer < 0 && !Engine::isLevelComplete) {
		spawnKamikaze(s);
		kamikazeTimer = (float)RandomNumber::generateUniformRealNumber(5, 15);
	}
	//If no more enemies in the current wave, level is over
	if (waves.empty()) {
		if (enemyCount == 0) {
			s->levelOver();
		}
	}
}

//Ypdates the level 
void LevelManager::update(Scene* s, bool infinite, int numWaveFiles, double dt) {
	if (enemyCount == 1 || enemyCount == 2) { singleTimer -= dt; }
	else { singleTimer = 5.f; }

	//When single timer goes to 0, the enemy count will be zero and the current 
	//wave will be completed
	if (singleTimer < 0) { enemyCount = 0; singleTimer = 5.f; }

	countTimer -= dt;
	if (countTimer < 0) {
		countTimer = 3.f;
	}
	kamikazeTimer -= dt;
	//Feeds waves for the infinite mode
	if (infinite) {
		infiniteLevel(s, numWaveFiles);
		return;
	}
	playLevel(s);
	//When the level is complete, change scene to the upgrade menu
	if (Engine::isLevelComplete) {
		levelOverTimer -= dt;
		if (levelOverTimer <= 0.0) {
			Engine::ChangeScene(&upgradeMenu);
		}
	}
}


//Feeds enemies for the infinite level, spawning kamikazes and beserker randomly
void LevelManager::infiniteLevel(Scene* s, int numWaveFiles) {

	if (enemyCount == 0) {
		int wave = RandomNumber::genRandomNumBetween(0, numWaveFiles - 1);
		Enemies::createEnemies(waveFilenames[wave], s);
	}
	//If the kamikaze timer is below 0 and the level is not complete, spawn a kamikaze
	if (kamikazeTimer < 0 && !Engine::isLevelComplete) {
		spawnKamikaze(s);
		kamikazeTimer = (float)RandomNumber::generateUniformRealNumber(5, 15);
	}
	//If the deads counter is bigger than 5 and level is not complete, spawn a beserker
	if (Scene::deadEnemies > 5 && !Engine::isLevelComplete) {
		spawnBeserker(s);
		Scene::deadEnemies = (float)RandomNumber::generateUniformRealNumber(-5, 0);
	}
}

//Creates a new kamikaze enemy and sets it alive
void LevelManager::spawnKamikaze(Scene* s) {
	auto en = EnemyPool::en_pool[EnemyPool::en_poolPointer++];
	en->setView(mainView);
	_eSettings = EnemySettings::LoadSettings(BANSAI, s);
	_eTexHelper = TextureHelpingSettings::LoadSettings(BANSAI, s);
	_wSettings = WeaponSettings::LoadSettings(EMPTY, s);
	_bSettings = BulletSettings::LoadSettings(TYPE3, s);
	_bTexHelper = TextureHelpingSettings::LoadSettings(TYPE3, s);
	en->addComponent<Kamikaze>(_eTexHelper, _bTexHelper, _eSettings, _wSettings, _bSettings, 0);
	en->setAlive(true);
	enemyCount++;
}
//Creates a new berseker enemy and sets it alive
void LevelManager::spawnBeserker(Scene* s) {
	auto en = EnemyPool::en_pool[EnemyPool::en_poolPointer++];
	en->setView(mainView);
	_eSettings = EnemySettings::LoadSettings(MADMAN, s);
	_eTexHelper = TextureHelpingSettings::LoadSettings(MADMAN, s);
	_wSettings = WeaponSettings::LoadSettings(GUN, s);
	_bSettings = BulletSettings::LoadSettings(TYPE3, s);
	_bTexHelper = TextureHelpingSettings::LoadSettings(TYPE3, s);
	en->addComponent<Beserker>(_eTexHelper, _bTexHelper, _eSettings, _wSettings, _bSettings, 0);
	en->setAlive(true);
	enemyCount++;
}
