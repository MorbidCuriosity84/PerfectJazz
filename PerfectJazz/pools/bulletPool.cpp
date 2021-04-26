#include "bulletPool.h"

unsigned char  BulletPool::bulPointer;
std::shared_ptr<Entity> BulletPool::bulPool[256];

using namespace sf;

void BulletPool::init(Scene* s)
{
    for (int i = 0; i < 256; i++) {
        auto bullet = s->makeEntity();
        bullet->setAlive(false);
        bullet->setPosition(Vector2f(-50.f, -50.f));
        EntityPool::pool[i] = bullet;
    }
}

