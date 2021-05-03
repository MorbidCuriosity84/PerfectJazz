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
int LevelManager::airCount;
int LevelManager::sargCount;
int LevelManager::colCount;
int LevelManager::kamCount;
int LevelManager::desCount;
float LevelManager::levelOverTimer;
float LevelManager::kamikazeTimer;
float LevelManager::countTimer;
float LevelManager::singleTimer;
bool LevelManager::isBoss;
textureSettings _eTexHelper;
textureSettings _bTexHelper;
enemySettings _eSettings;
weaponSettings _wSettings;
bulletSettings _bSettings;

void LevelManager::loadLevel(int level)
{
	std::queue<std::string> empty;
	std::swap(waves, empty); 

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

void LevelManager::playLevel(Scene* s)
{	
	if (enemyCount == 0) {
		if (!waves.empty()) {			
			Enemies::createEnemies(waves.front(), s);			
			Scene::deadEnemies = 0;
			waves.pop();
		}
	}	
	if (kamikazeTimer < 0 && !Engine::isLevelComplete) {
		//cout << "Enemy count before creation of kamikaze = " << LevelManager::enemyCount << endl;
		spawnKamikaze(s);		
		//cout << "Enemy count after creation of kamikaze = " << LevelManager::enemyCount << endl;
		kamikazeTimer = 5.f;
	}	
	if (waves.empty() && !isBoss) {
		waves.push("wave7");
		isBoss = true;
	}
	if (waves.empty()) {			
		if (enemyCount == 0) {
			s->levelOver();
		}
	}	
}

//updates the level 
void LevelManager::update(Scene* s, bool infinite, int numWaveFiles, double dt)
{
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
		cout << "Enemy count = " << enemyCount << endl;
		cout << "Timer = " << singleTimer << endl;
		countTimer = 1.f;
	}
	kamikazeTimer -= dt;
	if (infinite) {
		infiniteLevel(s, numWaveFiles);
		return;
	}
	playLevel(s);
	if (Engine::isLevelComplete) {
		levelOverTimer -= dt;
		if (levelOverTimer <= 0.0) {
			Engine::ChangeScene(&upgradeMenu);
		}
	}	
}

void LevelManager::infiniteLevel(Scene* s, int numWaveFiles) {

	if (enemyCount == 0) {
		int wave = RandomNumber::genRandomNumBetween(0, numWaveFiles - 1);
		Enemies::createEnemies(waveFilenames[wave], s);
	}
	if (kamikazeTimer < 0 && !Engine::isLevelComplete) {
		spawnKamikaze(s);		
		kamikazeTimer = 5.f;
	}
	if (Scene::deadEnemies > 5 && !Engine::isLevelComplete) {
		spawnBeserker(s);
		Scene::deadEnemies = 0;
	}
}

void LevelManager::spawnKamikaze(Scene* s)
{	
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

void LevelManager::spawnBeserker(Scene* s)
{	
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
