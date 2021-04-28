#pragma once
#include <LevelSystem.h>
#include "engine.h"
#include "../game.h"
#include <queue>
#include "ecm.h"


class Enemies {
public:
	static void createEnemies(std::string _waveFile, Scene*);
	static void setType(_enemyType type, Scene*);
	static void chooseMovement(ls::Tile tile, shared_ptr<Entity> en);
};
