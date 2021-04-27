#include "powerupPool.h"

unsigned char  PowerupPool::pwp_poolPointer;
std::shared_ptr<Entity> PowerupPool::pwp_pool[256];

using namespace sf;

void PowerupPool::init(Scene* s)
{
    for (int i = 0; i < 256; i++) {
        auto bullet = s->makeEntity();
        bullet->setAlive(false);
        bullet->setPosition(Vector2f(-50.f, -50.f));
        PowerupPool::pwp_pool[i] = bullet;
    }
}

