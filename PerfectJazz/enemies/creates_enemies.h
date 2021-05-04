#pragma once
#include <LevelSystem.h>
#include "engine.h"
#include "../game.h"
#include <queue>
#include "ecm.h"
#include "../movement/cmp_movement.h"

using namespace std;

//Creates enemies, assigning them a type and a movement
class Enemies {
public:
	static void createEnemies(std::string _waveFile, Scene*);
	static void setType(_enemyType type, Scene*);
	static std::shared_ptr<MovementComponent> chooseMovement(ls::Tile tile, shared_ptr<Entity> en, Vector2f initPos);
};
