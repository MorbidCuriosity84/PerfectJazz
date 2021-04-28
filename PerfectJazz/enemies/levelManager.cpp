#include "levelManager.h"
#include "../settings/level_settings.h"
#include "LevelSystem.h"
#include "maths.h"

std::queue<std::string> LevelManager::waves;
int LevelManager::enemyCount;


void LevelManager::loadLevel(int level)
{
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

void LevelManager::update(Scene* s)
{
	playLevel(s);
}
