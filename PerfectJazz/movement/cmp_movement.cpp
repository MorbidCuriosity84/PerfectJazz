#include "cmp_movement.h"
#include "../components/cmp_physics.h"

void MovementComponent::update(double dt)
{		
	if (linger) {
		if (_parent->getPosition().y > initPosition.y - Engine::getWindowSize().y / 1.5) {			
			if (lingerTime > 0) {
				_velocity = Vector2f(parentPhysics->getVelocity().x, 0.f);
				parentPhysics->setVelocity(_velocity);
				cout << "parent y velocity inside if = " << parentPhysics->getVelocity().y;
				lingerTime = lingerTime - dt;
			}
			else {
				parentPhysics->setVelocity(parentInitVelocity);
			}
		}		
	}
	//check if off the side of view, then move to center
	if (_parent->getPosition().x < 0 || _parent->getPosition().x > mainView.getSize().x) {
		_velocity.x = _velocity.x - mainView.getCenter().x;
	}
	parentPhysics->setVelocity(_velocity);
	//cout << "parent y velocity after update = " << parentPhysics->getVelocity().y << endl;
}

void MovementComponent::render() {}

void MovementComponent::setVelocity(sf::Vector2f vel) { _velocity = vel; }

sf::Vector2f MovementComponent::getVelocity() const { return _velocity; }

void MovementComponent::setLingerTime(float t) { lingerTime = t; }

void MovementComponent::isLinger(bool b) { linger = b; }

MovementComponent::MovementComponent(Entity* p, sf::Vector2f velocity, Vector2f initPos, bool l) : Component(p), _velocity(velocity), initPosition(initPos), linger(l) {
	auto phys = _parent->GetCompatibleComponent<PhysicsComponent>();
	parentPhysics = phys[0];
	parentInitVelocity = parentPhysics->getVelocity();
	linger ? lingerTime = 15.f : lingerTime = 0.f;
	cout << "lingering = " << linger << endl;
	cout << "linger time = " << lingerTime << endl;
}
