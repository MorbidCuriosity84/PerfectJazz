#include "cmp_missile_movement.h"
#include "Box2D/Box2D.h"
#include <cmath>
#include <iostream>
#include <SFML/Graphics/CircleShape.hpp>
#include <system_physics.h>
#include "cmp_radar.h"

using namespace Physics;

void MissileMovementComponent::update(double dt) {
	if (_seeking) {

		if (player != NULL && player->isAlive()) {

			//This needs some work to make the impulse smoother
			_velocity = normalize(player.get()->getPosition() - _parent->getPosition()) / (float)length(player.get()->getPosition() - _parent->getPosition()) * 45.f;
			//_velocity.x = player.get()->getPosition().x - _parent->getPosition().x;
		}

		Vector2f bul_pl_dif = _parent->getPosition() - player->getPosition();
		bul_pl_dif = Vector2f(fabs(bul_pl_dif.x), fabs(bul_pl_dif.y));

		//This is my attempt to keep the missile pointing at the target, it's not perfect, especially if the player moves from one 
		//quadrant to the next (ie NE -> SE or SW -> NW as the missile starts rotating in the opposite direction than it had been.
		//I'll have a think and see if i can come up with something better, maybe adding a vector will help, or using parent position
		//vector maths and trig is always fun, apart from at 3am.
		if (_parent->getPosition().y < player->getPosition().y) { // missile below 
			if (_parent->getPosition().x > player->getPosition().x) {  //target to the left of weapon
				_parentSprite->getSprite().setRotation(_parentSprite->getSprite().getRotation() - (180.f - atan(bul_pl_dif.x / bul_pl_dif.y)));
			}
			else {
				_parentSprite->getSprite().setRotation(_parentSprite->getSprite().getRotation() + (180.f - atan(bul_pl_dif.x / bul_pl_dif.y)));
			}
		}
		else { //missile above
			if (_parent->getPosition().x > player->getPosition().x) {  //target to the left of weapon
				_parentSprite->getSprite().setRotation(_parentSprite->getSprite().getRotation() - atan(bul_pl_dif.x / bul_pl_dif.y));
			}
			else {
				_parentSprite->getSprite().setRotation(_parentSprite->getSprite().getRotation() + atan(bul_pl_dif.x / bul_pl_dif.y));
			}
		}

		parentPhysics.get()->impulse(_velocity);
		//parentPhysics.get()->setVelocity(_velocity);
	}
}

void MissileMovementComponent::setSeeking(bool b) { _seeking = b; }

bool MissileMovementComponent::getSeeking() const { return _seeking; }

void MissileMovementComponent::setPhysics(shared_ptr<PhysicsComponent> phys) { _parentPhysics = phys; }

shared_ptr<PhysicsComponent> MissileMovementComponent::getPhysics() const { return _parentPhysics; }

<<<<<<< Updated upstream
MissileMovementComponent::MissileMovementComponent(Entity* p, sf::Vector2f vel, bool seek, _entityCategory cat) : MovementComponent(p, vel), _seeking(seek), cat(cat) {	
	_parentSprite = _parent->GetCompatibleComponent<SpriteComponent>()[0];
}
=======
MissileMovementComponent::MissileMovementComponent(Entity* p, sf::Vector2f vel, bool seek, _entityCategory cat) : MovementComponent(p, vel), _seeking(seek), cat(cat), contactCount(0) {
	_parentPhysics = _parent->GetCompatibleComponent<PhysicsComponent>()[0];
	_parentSprite = _parent->GetCompatibleComponent<SpriteComponent>()[0];
	b2FixtureDef missileRadar;
	b2CircleShape circleShape;
	auto shape = _parent->addComponent<ShapeComponent>();
	shape->setShape<CircleShape>(240.f);
	shape->getShape().setOrigin({ 240.f,240.f });
	shape->getShape().setFillColor(sf::Color(0, 0, 0, 45));
	circleShape.m_radius = 8;
	missileRadar.shape = &circleShape;
	missileRadar.isSensor = true;
	if (cat == ENEMY_MISSILE) {
		missileRadar.filter.categoryBits = ENEMY_MISSILE_RADAR;
		missileRadar.filter.maskBits = PLAYER_BODY;
	}
	else {
		missileRadar.filter.categoryBits = FRIENDLY_MISSILE_RADAR;
		missileRadar.filter.maskBits = ENEMY_BODY;
	}
	_parentPhysics.get()->getBody()->CreateFixture(&missileRadar);
}
>>>>>>> Stashed changes
