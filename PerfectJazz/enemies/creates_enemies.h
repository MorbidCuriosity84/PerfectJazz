#pragma once
#include "engine.h"
#include "../game.h"


class Enemies {
public:
	static void createEnemies(std::string _waveFile, Scene*);
	static void setType(_enemyType type, Scene*);
};
