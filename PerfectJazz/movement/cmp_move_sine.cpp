#include "cmp_move_sine.h"

void SineMovementComponent::update(double dt)
{
	_accumulation += dt * _multiplier;
	float rotation = sin(_accumulation) * _maxAngle;		
	_parent->setRotation(rotation);
	_parent->setPosition(Vector2f(_parent->getPosition().x + rotation, _parent->getPosition().y));
}

void SineMovementComponent::setMaxAngle(float ang) { _maxAngle = ang; }

float SineMovementComponent::getMaxAngle() const { return _maxAngle; }

void SineMovementComponent::setMultiplier(float multi) { _multiplier = multi; }

SineMovementComponent::SineMovementComponent(Entity* p, sf::Vector2f vel, float maxAngle) : MovementComponent(p, vel), _maxAngle(maxAngle), _accumulation(0.f), _multiplier(1.f) {}
