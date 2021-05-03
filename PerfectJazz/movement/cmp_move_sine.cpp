#include "cmp_move_sine.h"

//Updates the values to create a sine movement
//and updates the MovementComponent
void SineMovementComponent::update(double dt) {
	_accumulation += dt;
	float rotation = cosf(_accumulation * _multiplier) * _maxAngle;
	float moveRotation = cosf(_accumulation);
	_velocity = Vector2f(moveRotation, _velocity.y);
	_parent->setRotation(rotation);
	MovementComponent::update(dt);
}
//Sets the max angle for the sine movement
void SineMovementComponent::setMaxAngle(float ang) { _maxAngle = ang; }
//Gets the max angle for the sine movement
float SineMovementComponent::getMaxAngle() const { return _maxAngle; }
//Sets the multiplier for the sine movement
void SineMovementComponent::setMultiplier(float multi) { _multiplier = multi; }

//Constructor for the SineMovementComponent
SineMovementComponent::SineMovementComponent(Entity* p, sf::Vector2f vel, float maxAngle, Vector2f initPos, bool l) : 
	MovementComponent(p, vel, initPos, l), _maxAngle(maxAngle), _accumulation(10.f), _multiplier(5.f) {}
