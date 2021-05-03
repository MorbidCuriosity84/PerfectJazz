#pragma once
#include <list>
#include <ecm.h>
#include "engine.h"

using namespace std;
//Powerup class pool.
//256 entities are created on load to avoid loading them middle game
//increasing the performance. Entities are used from the pool, destroyed,
//and a new one will be created
class PowerupPool {
public:
	static unsigned char pwp_poolPointer;
	static std::shared_ptr<Entity> pwp_pool[256];
	PowerupPool() = default;
	~PowerupPool() = default;
	static void init(Scene* s);
};


