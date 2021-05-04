#pragma once
#include "engine.h"
#include "../game.h"
#include "ecm.h"
#include "../settings/collision_helper.h"

//Creates powerups that the player can pick up in order to update its stats
class Powerups {
public:
	static void deployPowerups();
	static void createPowerups(Scene* _scene);
	static void update(double dt);
};

