#pragma once
#include "engine.h"
#include "cmp_enemy.h"
#include "../components/cmp_sprite.h"
#include "../game.h"

class CreateEnemies {
public:
	static void initiliseEnemies(std::string _waveFile, Scene*);
	static void setType(_enemyType type, Scene*);
};
