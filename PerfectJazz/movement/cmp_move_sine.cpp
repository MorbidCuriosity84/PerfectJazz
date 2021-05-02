#include "cmp_move_sine.h"

void SineMovementComponent::update(double dt)
{
	_accumulation += dt;
	float rotation = cosf(_accumulation * _multiplier) * _maxAngle;
	float moveRotation = cosf(_accumulation);
	_velocity = Vector2f(moveRotation, _velocity.y);
	_parent->setRotation(rotation);	
	MovementComponent::update(dt);
}

void SineMovementComponent::setMaxAngle(float ang) { _maxAngle = ang; }

float SineMovementComponent::getMaxAngle() const { return _maxAngle; }

void SineMovementComponent::setMultiplier(float multi) { _multiplier = multi; }

SineMovementComponent::SineMovementComponent(Entity* p, sf::Vector2f vel, float maxAngle, Vector2f initPos, bool l) : MovementComponent(p, vel, initPos, l), _maxAngle(maxAngle), _accumulation(10.f), _multiplier(5.f) {}
