#include "entityPool.h"

unsigned char  EntityPool::poolPointer;
std::shared_ptr<Entity> EntityPool::pool[256];

using namespace sf;

//Initialises the pool, setting the entity not alive and outside the boundaries of the view
void EntityPool::init(Scene* s) {
    for (int i = 0; i < 256; i++) {
        auto bullet = s->makeEntity();
        bullet->setAlive(false);
        bullet->setPosition(Vector2f(-500.f, -500.f));
        EntityPool::pool[i] = bullet;
    }
}