#include "entityPool.h"

unsigned char  EntityPool::poolPointer;
std::shared_ptr<Entity> EntityPool::pool[256];

using namespace sf;

void EntityPool::init(Scene* s)
{
    for (int i = 0; i < 256; i++) {
        auto bullet = s->makeEntity(); 
        bullet->setAlive(false);        
        bullet->setPosition(Vector2f(-50.f, -50.f));                    
        EntityPool::pool[i] = bullet;
    }
}
