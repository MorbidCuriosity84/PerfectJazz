#include "cmp_weapon.h"

void WeaponComponent::fire() {}

void WeaponComponent::update(double dt) {} 

void WeaponComponent::render()  {} 

WeaponComponent::WeaponComponent(Entity* const p, wepSettings w) : Component(p), _category(w.wepCat), _firetime(w.firetime), _spread(w.spread) {}

WeaponComponent::~WeaponComponent() {}

//std::shared_ptr<DamageComponent> WeaponComponent::getDamage() const { return _damage; }
//
//void WeaponComponent::setDamage(std::shared_ptr<DamageComponent> d) { _damage = d; }
//
//std::shared_ptr<SpriteComponent> WeaponComponent::getSprite() const { return _sprite; }
//
//void WeaponComponent::setSprite(std::shared_ptr<SpriteComponent> s) { _sprite = s; }

_entityCategory WeaponComponent::getCategory() const { return _category; }

void WeaponComponent::setCategory(_entityCategory cat) { _category = cat; }

double WeaponComponent::getFiretime() const { return _firetime; }

void WeaponComponent::setFiretime(double ft) { _firetime = ft; }

uint16_t WeaponComponent::getSpread() const { return _spread; }

void WeaponComponent::setSpread(uint16_t sp) { _spread = sp; }

Vector2f WeaponComponent::getDirection() const { return _direction; }

void WeaponComponent::setDirection(Vector2f dir) { _direction = dir; }

wepSettings WeaponComponent::getSettings() const { return _wepSettings; }
