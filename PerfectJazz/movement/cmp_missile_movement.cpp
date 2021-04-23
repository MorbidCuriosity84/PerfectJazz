#include "cmp_missile_movement.h"
#include "Box2D/Box2D.h"

void MissileMovementComponent::update(double dt)
{
	if (_seeking) {

		if (player != NULL && player->isAlive()) {
			_velocity.x = player.get()->getPosition().x - _parent->getPosition().x;
		}

		//parentPhysics = _parent->GetCompatibleComponent<PhysicsComponent>()[0];
		parentPhysics.get()->setVelocity(_velocity);
	}
	else {

	}
}

void MissileMovementComponent::setSeeking(bool b) { _seeking = b; }

bool MissileMovementComponent::getSeeking() const { return _seeking; }

void MissileMovementComponent::setPhysics(shared_ptr<PhysicsComponent> phys) { _parentPhysics = phys; }

shared_ptr<PhysicsComponent> MissileMovementComponent::getPhysics() const { return _parentPhysics; }

MissileMovementComponent::MissileMovementComponent(Entity* p, sf::Vector2f vel, bool seek) : MovementComponent(p, vel), _seeking(seek) {	
	_parentPhysics = _parent->GetCompatibleComponent<PhysicsComponent>()[0];
	b2FixtureDef missileRadar;
	b2CircleShape circleShape;
	circleShape.m_radius = 8;	
	missileRadar.shape = &circleShape;
	missileRadar.isSensor = true;		
	missileRadar.filter.categoryBits = ENEMY_MISSILE_RADAR;
	missileRadar.filter.maskBits = PLAYER_BODY;		
	_parentPhysics.get()->getBody()->CreateFixture(&missileRadar);	
}
