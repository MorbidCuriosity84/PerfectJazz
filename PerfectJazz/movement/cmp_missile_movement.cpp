#include "cmp_missile_movement.h"
#include "../components/cmp_physics.h"

void MissileMovementComponent::update(double dt)
{
	if (_seeking) {

		if (player != NULL && player->isAlive()) {
			_velocity.x = player.get()->getPosition().x - _parent->getPosition().x;
		}

		auto phys = _parent->GetCompatibleComponent<PhysicsComponent>()[0];
		phys.get()->setVelocity(_velocity);
	}
	else {

	}
}

void MissileMovementComponent::setSeeking(bool b) { _seeking = b; }

bool MissileMovementComponent::getSeeking() const { return _seeking; }

MissileMovementComponent::MissileMovementComponent(Entity* p, sf::Vector2f vel, bool seek) : MovementComponent(p, vel), _seeking(seek) {}
