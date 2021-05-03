#include "cmp_movement.h"
#include "../components/cmp_physics.h"

//Allows the entity to linger accross the screen during a certaing time
void MovementComponent::update(double dt) {
	if (active) {
		if (linger) {
			if (_parent->getPosition().y > initPosition.y - Engine::getWindowSize().y / 1.5) {
				if (lingerTime > 0) {
					_velocity = Vector2f(parentPhysics->getVelocity().x, 0.f);
					parentPhysics->setVelocity(_velocity);
					lingerTime = lingerTime - dt;
				}
				else {
					_velocity = parentInitVelocity;
					linger = false;
				}
			}
		}				

		if (_parent->getPosition().x < 0 || _parent->getPosition().x > mainView.getSize().x) {
			Vector2f v2c = _parent->getPosition() - mainView.getCenter();
			v2c.y = 0.f;
			auto a = normalize(v2c);
			auto b = b2Vec2(a.x * 0.1f, a.y * 0.1f);
			parentPhysics->getBody()->ApplyLinearImpulseToCenter(b, true);
		}
	}	
}
//Renders the component
void MovementComponent::render() {}
//Sets the velocity of the movement
void MovementComponent::setVelocity(sf::Vector2f vel) { _velocity = vel; }
//Gets the current velocity
sf::Vector2f MovementComponent::getVelocity() const { return _velocity; }
//Sets the linger timer value
void MovementComponent::setLingerTime(float t) { lingerTime = t; }
//Returns if the entity is lingering
void MovementComponent::isLinger(bool b) { linger = b; }
//Returns if the movement component is active or not
void MovementComponent::isActive(bool b) { active = b; }

//Constructor for the MovementComponent.
//Sets the lingerTime and adds a physics component to the parent entity
MovementComponent::MovementComponent(Entity* p, sf::Vector2f velocity, Vector2f initPos, bool l) : Component(p), _velocity(velocity), initPosition(initPos), linger(false), active(true) {
	parentPhysics = _parent->GetCompatibleComponent<PhysicsComponent>()[0];
	parentInitVelocity = parentPhysics->getVelocity();
	linger ? lingerTime = 15.f : lingerTime = 0.f;
	auto a = normalize(_velocity);
	auto b = b2Vec2(a.x * 1.f, a.y * 1.f);
	parentPhysics->getBody()->ApplyLinearImpulseToCenter(b, true);
	//parentPhysics->setVelocity(_velocity);
}
