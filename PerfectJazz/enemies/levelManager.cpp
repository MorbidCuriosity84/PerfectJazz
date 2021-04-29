#include "levelManager.h"
#include "../settings/level_settings.h"
#include "LevelSystem.h"
#include "maths.h"
#include "../randomNumber.h"

std::queue<std::string> LevelManager::waves;
int LevelManager::enemyCount;


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
}

void LevelManager::playLevel(Scene* s)
{
	if (enemyCount == 0) {
		if (!waves.empty()) {
			Enemies::createEnemies(waves.front(), s);
			waves.pop();
		}
	}
}

void LevelManager::update(Scene* s, bool infinite, int numWaveFiles)
{
	if (infinite) {
		infiniteLevel(s, numWaveFiles);
		return;
	}
	playLevel(s);
}

void LevelManager::infiniteLevel(Scene* s, int numWaveFiles) {
		
	if (enemyCount == 0) {
		int wave = RandomNumber::genRandomNumBetween(0, numWaveFiles - 1);
		Enemies::createEnemies(waveFilenames[wave], s);
	}
}