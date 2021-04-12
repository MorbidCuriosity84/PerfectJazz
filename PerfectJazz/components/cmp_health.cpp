#include "cmp_health.h"
#include "cmp_bullet.h"

HealthComponent::HealthComponent(Entity* p) : Component(p), _health(100.0f)
{
}

void HealthComponent::update(double dt)
{
}

void HealthComponent::render()
{
}

HealthComponent::~HealthComponent()
{
}


float HealthComponent::getHealth()
{
    return _health;
}

void HealthComponent::addHealth(float health2add)
{
    _health += health2add;
}

void HealthComponent::handleContact(b2Contact* contact)
{    
    auto* bullet = static_cast<BulletComponent*>(contact->GetFixtureB()->GetBody()->GetUserData());    
    float dam = bullet->getDamage();    
    cout << "Bullet damage = " << dam << endl;
    cout << "Player health before collision = " << getHealth() << endl;
    addHealth(-dam);
    cout << "Player health after collision = " << getHealth() << endl;
    if (_health < 0) 
    {
        _parent->setVisible(false);
        _parent->setAlive(false);
        _parent->setPosition({ -50.f, -50.f });
    }
}
