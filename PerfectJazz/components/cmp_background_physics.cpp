#include "cmp_background_physics.h"
#include "system_physics.h"
#include <LevelSystem.h>
#include <SFML/Window/Keyboard.hpp>

using namespace std;
using namespace sf;
using namespace Physics;

void BackgroundPhysicsComponent::update(double dt) {
    const auto pos = _parent->getPosition();
    _parent->setPosition(Vector2f(pos.x, pos.y + (float)dt * _Velocity.y));
}

void BackgroundPhysicsComponent::ChangeVelocity(sf::Vector2f velocity) {
    _Velocity = velocity;
}

sf::Vector2f BackgroundPhysicsComponent::GetVelocity() {
    return _Velocity;
}
BackgroundPhysicsComponent::BackgroundPhysicsComponent(Entity* p,
    const Vector2f& size)
    : PhysicsComponent(p, true, size) {
    _size = sv2_to_bv2(size, true);
    _Velocity = Vector2f(20.f, 350.f);
}