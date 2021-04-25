#pragma once
#include "engine.h"
#include "../game.h"
#include "ecm.h"
#include "../settings/collision_helper.h"

class Powerups {
public:
	static void deployPowerups();
	static void createPowerups(Scene* _scene);
	static void update(double dt);
};

