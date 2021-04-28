#pragma once
#include "engine.h"
#include "../game.h"
#include <queue>
#include "ecm.h"


class Enemies {
public:
	static void createEnemies(std::string _waveFile, Scene*);
	static void setType(_enemyType type, Scene*);
	static void loadLevel(std::queue<std::string> waveFiles, Scene* s);
};
