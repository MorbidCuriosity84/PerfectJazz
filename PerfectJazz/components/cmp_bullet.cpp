#include "cmp_bullet.h"
using namespace std;
using namespace sf;

void BulletComponent::update(double dt) {
  _lifetime -= dt;
  if (_lifetime <= 0.f) {
    _parent->setForDelete();
  }
}

BulletComponent::BulletComponent(Entity* p, shared_ptr<DamageComponent>damage, float lifetime)
    : Component(p), _lifetime(lifetime), _damage(damage) {}

void BulletComponent::setDamage(shared_ptr<DamageComponent> damage)
{
    _damage = damage;
}

shared_ptr<DamageComponent> BulletComponent::getDamage() const {
    return _damage;
}