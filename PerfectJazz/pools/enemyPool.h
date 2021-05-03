#pragma once
#include <list>
#include <ecm.h>
#include "engine.h"

using namespace std;

//Enemy class pool.
//256 entities are created on load to avoid loading them middle game
//increasing the performance. Entities are used from the pool, destroyed,
//and a new one will be created
class EnemyPool
{
public:
    static unsigned char en_poolPointer;
    static std::shared_ptr<Entity> en_pool[256];
    EnemyPool() = default;
    ~EnemyPool() = default;
    static void init(Scene* s);
};