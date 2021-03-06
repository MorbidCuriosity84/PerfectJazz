#pragma once
#include <queue>
#include "../lib_tile_level_loader/LevelSystem.h"
#include "creates_enemies.h"

using namespace std;

class LevelManager {
protected:
public:
	LevelManager() = default;
	~LevelManager() = default;
	static std::queue<std::string> waves;					//queue of filenames representing waves and the count of enemies for that wave
	static float levelOverTimer;							//timer for the level over
	static int enemyCount;									//count of current enemies in play. needs to be decremented when enemy dies or offscreen
	static bool isBoss;
	static bool splashMusic;
	static int waveCount;
	static int airCount;									//count of current airman in play. needs to be decremented when enemy dies or offscreen
	static float kamikazeTimer;								//kamikaze timer
	static float countTimer;								//total count timer
	static float singleTimer;								//individual timer 
	static void loadLevel(int i);
	static void playLevel(Scene* s);
	static void update(Scene* s, bool infinite, int numWaveFiles, double dt);
	static void infiniteLevel(Scene* s, int numWaveFiles);
	static void spawnKamikaze(Scene* s);
	static void spawnBeserker(Scene* s);
	static void spawnBoss(Scene* s);
	static void scaleDifficulty(Scene* s);
};