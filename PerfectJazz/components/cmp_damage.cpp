#include "cmp_damage.h"

void DamageComponent::update(double dt)
{
}

void DamageComponent::render()
{
}

DamageComponent::DamageComponent(Entity* p, uint16_t damage) : Component(p), _damage(damage)
{
}


void DamageComponent::setDamage(uint16_t damage)
{
	_damage = damage;
}

uint16_t DamageComponent::getDamage() const
{
	return uint16_t();
}

void DamageComponent::applyDamage(HPComponent* hp)
{
	hp->setHP(hp->getHP() - _damage);
}
