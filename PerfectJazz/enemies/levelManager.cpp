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
		/*ls::loadLevelFile(waveFilenames[idx], (round)((mainView.getSize().x / 15)));
		size_t w = ls::getWidth();
		size_t h = ls::getHeight();
		for (int j = 0; j < w * h; j++) {
			if (ls::getTile({ (j % w), (j / w) % w }) != LevelSystem::TILES::EMPTY) {				
			}
		}*/
		LevelManager::waves.push(waveFilenames[i]);
		i++;
	}
	enemyCount = 0;
}

void LevelManager::playLevel(Scene* s)
{
	if (enemyCount == 0) {
		Enemies::createEnemies(waves.front(), s);
		waves.pop();
	}
}

void LevelManager::update(Scene* s)
{
	playLevel(s);
}
