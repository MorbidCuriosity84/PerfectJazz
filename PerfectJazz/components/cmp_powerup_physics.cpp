#include "cmp_powerup_physics.h"
#include "system_physics.h"
#include <LevelSystem.h>
#include <SFML/Window/Keyboard.hpp>

using namespace std;
using namespace sf;
using namespace Physics;

void PowerupPhysicsComponent::update(double dt) {
    const auto pos = _parent->getPosition();
    setVelocity(Vector2f(0.f, 100.f));
    _parent->setPosition(Vector2f(pos.x, pos.y + (float)dt * _Velocity.y));
}


PowerupPhysicsComponent::PowerupPhysicsComponent(Entity* p,
    const Vector2f& size)
    : PhysicsComponent(p, true, size) {
    _size = sv2_to_bv2(size, true);
    _body->SetSleepingAllowed(false);
    _body->SetFixedRotation(true);
}