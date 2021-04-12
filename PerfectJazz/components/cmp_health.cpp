#include "cmp_health.h"

HealthComponent::HealthComponent(Entity* p) : Component(p)
{
}

double HealthComponent::getHealth()
{
    return _health;
}

void HealthComponent::addHealth(double health2add)
{
    _health += health2add;
}

void HealthComponent::handleContact(b2Contact* contact)
{
    auto ent = contact->GetFixtureA()->GetBody()->GetUserData();

}
