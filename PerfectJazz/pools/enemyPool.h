#pragma once
#include <list>
#include <ecm.h>
#include "engine.h"

using namespace std;

class EnemyPool
{
public:
    static unsigned char en_poolPointer;
    static std::shared_ptr<Entity> en_pool[256];
    EnemyPool() = default;
    ~EnemyPool() = default;
    static void init(Scene* s);
};