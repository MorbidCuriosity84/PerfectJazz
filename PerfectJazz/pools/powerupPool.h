#pragma once
#include <list>
#include <ecm.h>
#include "engine.h"

using namespace std;

class PowerupPool
{
public:
    static unsigned char pwp_poolPointer;
    static std::shared_ptr<Entity> pwp_pool[256];
    PowerupPool() = default;
    ~PowerupPool() = default;
    static void init(Scene* s);
};


