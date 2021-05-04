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
#include "cmp_boss.h"

std::queue<std::string> LevelManager::waves;
int LevelManager::enemyCount;
float LevelManager::levelOverTimer;
float LevelManager::kamikazeTimer;
float LevelManager::countTimer;
float LevelManager::singleTimer;
bool LevelManager::isBoss;
bool LevelManager::splashMusic;
int LevelManager::waveCount;
textureSettings _eTexHelper;
textureSettings _bTexHelper;
enemySettings _eSettings;
weaponSettings _wSettings;
bulletSettings _bSettings;

//Helps the level scene to load the waves
void LevelManager::loadLevel(int level) {
	std::queue<std::string> empty;
	std::swap(waves, empty);

	splashMusic = false;
	isBoss = false;
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
		kamikazeTimer = (float)RandomNumber::generateUniformRealNumber(5, 8);
	}
	//If level waves are finished, push boss wave7 onto queue
	if (waves.empty() && !isBoss) {
		waves.push("wave7");
		isBoss = true;		
	}
	////stop current level music, play boss splash music
	//if (isBoss) {
	//	if (musicArray[currentLvlMusicIndex].Playing) {
	//		musicArray[currentLvlMusicIndex].stop();
	//		musicArray[MUSIC_BOSS_SPLASH].setPosition(0, 1, 50);
	//		musicArray[MUSIC_BOSS_SPLASH].setVolume(25);
	//		musicArray[MUSIC_BOSS_SPLASH].setLoop(false);
	//		musicArray[MUSIC_BOSS_SPLASH].play();
	//		currentLvlMusicIndex = MUSIC_BOSS_SPLASH;
	//		splashMusic = true;
	//	}
	//}
	////play boss fight music
	//if (splashMusic && isBoss) {
	//	if (!musicArray[MUSIC_BOSS_SPLASH].Playing) {
	//		musicArray[MUSIC_BOSS_FIGHT].setPosition(0, 1, 50);
	//		musicArray[MUSIC_BOSS_FIGHT].setVolume(25);
	//		musicArray[MUSIC_BOSS_FIGHT].setLoop(true);
	//		musicArray[MUSIC_BOSS_FIGHT].play();
	//		currentLvlMusicIndex = MUSIC_BOSS_FIGHT;
	//	}
	//}

	//If no more enemies in the current wave, level is over
	if (Engine::currentPlayerLevel == 4) {
		if (waves.empty() && Boss::isBossDead) { s->gameComplete(); return; }
	}
	if (waves.empty() && Boss::isBossDead) { s->levelOver(); }
}

//updates the level 
void LevelManager::update(Scene* s, bool infinite, int numWaveFiles, double dt)
{
	//checks if level has got stuck with enemy count at 1 or 2, resets count after timer runs out
	if (!isBoss) {
		if (enemyCount == 1 || enemyCount == 2) {
			singleTimer -= dt;
		}
		else {
			singleTimer = 5.f;
		}
		if (singleTimer < 0) {
			enemyCount = 0;
			singleTimer = 5.f;
		}
	}	
	countTimer -= dt;
	if (countTimer < 0) {
		cout << "Enemies = " << enemyCount << endl;
		countTimer = 1.f;
	}
	kamikazeTimer -= dt;
	//Feeds waves for the infinite mode
	if (infinite) {
		infiniteLevel(s, numWaveFiles);
		return;
	}
	playLevel(s);
	//When game is complete, load credits
	if (Engine::isGameComplete) {
		levelOverTimer -= dt;
		if (levelOverTimer <= 0.0) {
			Engine::isGameComplete = false;
			Engine::ChangeScene(&creditScene);
		}
		return;
	}
	//When the level is complete, change scene to the upgrade menu
	if (Engine::isLevelComplete) {
		levelOverTimer -= dt;		
		if (levelOverTimer <= 0.0) {			
			Engine::currentPlayerLevel++;
			Engine::ChangeScene(&upgradeMenu);
		}
	}
}


//Feeds enemies for the infinite level, spawning kamikazes and beserker randomly
void LevelManager::infiniteLevel(Scene* s, int numWaveFiles) {

	if (enemyCount == 0) {
		int wave = RandomNumber::genRandomNumBetween(0, numWaveFiles - 1);
		Enemies::createEnemies(waveFilenames[wave], s);
		waveCount++;
	}
	//If the kamikaze timer is below 0 and the level is not complete, spawn a kamikaze
	if (kamikazeTimer < 0 && !Engine::isLevelComplete) {
		spawnKamikaze(s);
		kamikazeTimer = (float)RandomNumber::generateUniformRealNumber(5, 15);
	}	

	//increment count every 10 waves to scale enemy difficulty
	if (waveCount > 0 && waveCount % 5 == 0) {
		Engine::currentPlayerLevel++;
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
