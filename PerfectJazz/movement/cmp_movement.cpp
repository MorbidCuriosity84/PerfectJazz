#include "cmp_movement.h"
#include "../components/cmp_physics.h"

void MovementComponent::update(double dt)
{		
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
		auto a = normalize(_velocity);
		auto b = b2Vec2(a.x * 0.01f, a.y * 0.01f) ;
		parentPhysics->getBody()->ApplyLinearImpulseToCenter(b, true);
		//parentPhysics->setVelocity(_velocity);
	}	
}

void MovementComponent::render() {}

void MovementComponent::setVelocity(sf::Vector2f vel) { _velocity = vel; }

sf::Vector2f MovementComponent::getVelocity() const { return _velocity; }

void MovementComponent::setLingerTime(float t) { lingerTime = t; }

void MovementComponent::isLinger(bool b) { linger = b; }

void MovementComponent::isActive(bool b) { active = b; }

MovementComponent::MovementComponent(Entity* p, sf::Vector2f velocity, Vector2f initPos, bool l) : Component(p), _velocity(velocity), initPosition(initPos), linger(false), active(true) {	
	parentPhysics = _parent->GetCompatibleComponent<PhysicsComponent>()[0];
	parentInitVelocity = parentPhysics->getVelocity();
	linger ? lingerTime = 15.f : lingerTime = 0.f;
}
