#include "cmp_bullet.h"
using namespace std;
using namespace sf;

void BulletComponent::update(double dt) {
  _lifetime -= dt;
  if (_lifetime <= 0.f) {
    _parent->setForDelete();
  }
}

BulletComponent::BulletComponent(Entity* p, float damage, float lifetime)
    : Component(p), _lifetime(lifetime), _damage(damage) {}

void BulletComponent::setDamage(float damage)
{
    _damage = damage;
}

float BulletComponent::getDamage() const {
    return _damage;
}