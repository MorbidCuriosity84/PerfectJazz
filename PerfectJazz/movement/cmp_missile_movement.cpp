#include "cmp_missile_movement.h"
#include "Box2D/Box2D.h"

void MissileMovementComponent::update(double dt)
{
	if (_seeking) {

		if (player != NULL && player->isAlive()) {
			_velocity.x = player.get()->getPosition().x - _parent->getPosition().x;
		}
		
		parentPhysics)->setVelocity(_velocity);
	}
	else {

	}
}

void MissileMovementComponent::setSeeking(bool b) { _seeking = b; }

bool MissileMovementComponent::getSeeking() const { return _seeking; }

void MissileMovementComponent::setPhysics(std::vector<PhysicsComponent> phys)
{
}

std::vector<PhysicsComponent> MissileMovementComponent::getPhysics() const
{
	return std::vector<PhysicsComponent>();
}

MissileMovementComponent::MissileMovementComponent(Entity* p, sf::Vector2f vel, bool seek) : MovementComponent(p, vel), _seeking(seek) {	
	_parentPhysics = _parent->GetCompatibleComponent<PhysicsComponent>()[0];
	b2FixtureDef missileRadar;
	b2CircleShape circleShape;
	circleShape.m_radius = 8;
	missileRadar.shape = &circleShape;
	missileRadar.isSensor = true;
	//missileRadar.filter.categoryBits = MISSILE_RADAR;
	//missileRadar.filter.maskBits = ENEMY_AIRCRAFT;//radar only collides with aircraft
	_parentPhysics.get()->getBody()->CreateFixture(&missileRadar);
}
