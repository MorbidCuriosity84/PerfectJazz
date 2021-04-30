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

std::queue<std::string> LevelManager::waves;
int LevelManager::enemyCount;
float LevelManager::levelOverTimer;
float LevelManager::kamikazeTimer;
textureSettings _eTexHelper;
textureSettings _bTexHelper;
enemySettings _eSettings;
weaponSettings _wSettings;
bulletSettings _bSettings;

void LevelManager::loadLevel(int level)
{
	enemyCount = 0;
	levelOverTimer = 3.f;
	kamikazeTimer = 5.f;
	if (level == -1) { // infinite level flag
		return;
	}
	int i = 0;
	for (char c : levels[level]) {
		int idx = c - 48; //converts level character to int		
		LevelManager::waves.push(waveFilenames[i]);
		i++;
	}
	
}

void LevelManager::playLevel(Scene* s)
{

	if (enemyCount == 0) {
		if (!waves.empty()) {
			Enemies::createEnemies(waves.front(), s);
			waves.pop();
		}
	}	
	if (kamikazeTimer < 0 && !Engine::isLevelComplete) {
		spawnKamikaze(s);
		kamikazeTimer = 5.f;
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
}

void LevelManager::spawnKamikaze(Scene* s)
{
	auto en = s->makeEntity();
	en->setView(mainView);
	_eSettings = EnemySettings::LoadSettings(BANSAI, s);
	_eTexHelper = TextureHelpingSettings::LoadSettings(BANSAI, s);
	_wSettings = WeaponSettings::LoadSettings(EMPTY, s);
	_bSettings = BulletSettings::LoadSettings(TYPE3, s);
	_bTexHelper = TextureHelpingSettings::LoadSettings(TYPE3, s);
	en->addComponent<Kamikaze>(_eTexHelper, _bTexHelper, _eSettings, _wSettings, _bSettings, 0);	
	enemyCount++;
}