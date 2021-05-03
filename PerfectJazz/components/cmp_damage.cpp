#include "cmp_damage.h"

// Updates the damage component
void DamageComponent::update(double dt) {}

// Renders the damage component
void DamageComponent::render() {}

// Constructor for the damage component
DamageComponent::DamageComponent(Entity* p, uint16_t damage) : Component(p), _damage(damage) {}

// Sets the current damage
void DamageComponent::setDamage(uint16_t damage) { _damage = damage; }

// Gets the damage
uint16_t DamageComponent::getDamage() const { return uint16_t(); }

// Applies damage to the HP component 
void DamageComponent::applyDamage(HPComponent* hp) { hp->setHP(hp->getHP() - _damage); }
