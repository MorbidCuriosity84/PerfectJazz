#include "cmp_missile_movement.h"
#include "Box2D/Box2D.h"
#include <cmath>
#include <iostream>
#include <SFML/Graphics/CircleShape.hpp>
#include <system_physics.h>
#include "cmp_radar.h"

using namespace Physics;
//Sets the missile movement
void MissileMovementComponent::update(double dt) {

	if (_seeking) {

		if (player != NULL && player->isAlive()) {

			//This needs some work to make the impulse smoother
			_velocity = normalize(player.get()->getPosition() - _parent->getPosition()) / (float)length(player.get()->getPosition() - _parent->getPosition()) * 95.f;
			//_velocity.x = player.get()->getPosition().x - _parent->getPosition().x;
		}

		Vector2f bul_pl_dif = _parent->getPosition() - player->getPosition();
		bul_pl_dif = Vector2f(fabs(bul_pl_dif.x), fabs(bul_pl_dif.y));

		//Better way using dot product and not atan calls, still getting weirdness when the missile moves away though	
		Vector2f a = parentPhysics->getVelocity();
		Vector2f b = player->getPosition() - _parent->getPosition();

		if ((a.x * b.y) - (a.y * b.x) < 0) { //if left
			_parentSprite->getSprite().rotate(2.f);
		}
		else if ((a.x * b.y) - (a.y * b.x) > 0) {
			_parentSprite->getSprite().rotate(-2.f);
		}
		else { //if moving away
			if ((a.x * b.x) + (a.y * b.y) < 0) {
				_parentSprite->getSprite().rotate(2.f);
			}
			else {
				_parentSprite->getSprite().rotate(-2.f);
			}
		}
		parentPhysics.get()->impulse(_velocity);
	}
}

//Sets the boolean seeking
void MissileMovementComponent::setSeeking(bool b) { _seeking = b; }
//Gets the values of the boolean seeking
bool MissileMovementComponent::getSeeking() const { return _seeking; }
//Passes a PhysicsComponent
void MissileMovementComponent::setPhysics(shared_ptr<PhysicsComponent> phys) { _parentPhysics = phys; }
//Gets the current PhysicsComponent
shared_ptr<PhysicsComponent> MissileMovementComponent::getPhysics() const { return _parentPhysics; }

//Constructor for the MissileMovementComponent.
//Creates a reference to the parent's SpriteComponent
MissileMovementComponent::MissileMovementComponent(Entity* p, sf::Vector2f vel, bool seek, _entityCategory cat) : MovementComponent(p, vel, { 0.f,0.f }, false), _seeking(seek), cat(cat) {
	_parentSprite = _parent->GetCompatibleComponent<SpriteComponent>()[0];
}
