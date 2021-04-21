#include "cmp_movement.h"
#include "../components/cmp_physics.h"

void MovementComponent::update(double dt)
{	
	parentPhysics->setVelocity(_velocity);
}

void MovementComponent::render() {}

void MovementComponent::setVelocity(sf::Vector2f vel) { _velocity = vel; }

sf::Vector2f MovementComponent::getVelocity() const { return _velocity; }

MovementComponent::MovementComponent(Entity* p, sf::Vector2f velocity) : Component(p), _velocity(velocity) {
	parentPhysics = _parent->GetCompatibleComponent<PhysicsComponent>()[0];
}
