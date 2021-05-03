#pragma once
#include <list>
#include <ecm.h>
#include "engine.h"

using namespace std;

//Entity class pool.
//256 entities are created on load to avoid loading them middle game
//increasing the performance. Entities are used from the pool, destroyed,
//and a new one will be created
class EntityPool {
public:
    static unsigned char poolPointer;
    static std::shared_ptr<Entity> pool[256];
    EntityPool() = default;
    ~EntityPool() = default;
    static void init(Scene* s);
};
