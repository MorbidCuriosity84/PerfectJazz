#include "levelManager.h"
#include "../settings/level_settings.h"
#include "LevelSystem.h"
#include "maths.h"
<<<<<<< Updated upstream
#include "../randomNumber.h"
#include "../game.h"
=======
#include "../services/randomNumber.h"
>>>>>>> Stashed changes

std::queue<std::string> LevelManager::waves;
int LevelManager::enemyCount;
float LevelManager::levelOverTimer;

void LevelManager::loadLevel(int level)
{
	if (level == -1) { // infinite level flag
		return;
	}
	int i = 0;
	for (char c : levels[level]) {
		int idx = c - 48; //converts level character to int		
		LevelManager::waves.push(waveFilenames[i]);
		i++;
	}
	enemyCount = 0;
	levelOverTimer = 3.f;
}

void LevelManager::playLevel(Scene* s)
{
	if (enemyCount == 0) {
		if (!waves.empty()) {
			Enemies::createEnemies(waves.front(), s);
			waves.pop();
		}
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
}
