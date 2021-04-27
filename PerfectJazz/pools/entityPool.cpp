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







//template<typename T>
//unsigned char  EntityPool<T>::poolPointer;
//template<typename T>
//std::shared_ptr<Entity> EntityPool<T>::pool[256];
//
//using namespace sf;
//
//template<typename T>
//void EntityPool<T>::init(Scene* s)
//{
//    for (int i = 0; i < 256; i++) {
//        auto bullet = s->makeEntity(); 
//        bullet->setAlive(false);        
//        bullet->setPosition(Vector2f(-50.f, -50.f));                    
//        EntityPool<T>::pool[i] = bullet;
//    }
//}
