#include "cmp_bullet.h"
using namespace std;
using namespace sf;

void BulletComponent::update(double dt) {
  _lifetime -= dt;
  if (_lifetime <= 0.f) {
    _parent->setForDelete();
  }
}

BulletComponent::BulletComponent(Entity* p, uint16 damage, float lifetime)
    : Component(p), _lifetime(lifetime), _damage(damage) {}

void BulletComponent::setDamage(uint16 damage)
{
    _damage = damage;
}

uint16 BulletComponent::getDamage() const {
    return _damage;
}