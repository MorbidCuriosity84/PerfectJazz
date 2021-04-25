#pragma once
#include <list>
#include <ecm.h>
#include "engine.h"

using namespace std;

class EntityPool
{
public:
    static unsigned char poolPointer;
    static std::shared_ptr<Entity> pool[256];
    EntityPool();
    ~EntityPool();
    static void init(Scene* s);           
};
