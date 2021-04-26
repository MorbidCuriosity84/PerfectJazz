#include "cmp_missile_movement.h"
#include "Box2D/Box2D.h"
#include "math.h"
#include <iostream>

void MissileMovementComponent::update(double dt)
{
	if (_seeking) {

		if (player != NULL && player->isAlive()) {
			_velocity = normalize(player.get()->getPosition() - _parent->getPosition()) / (float)length(player.get()->getPosition() - _parent->getPosition()) * 45.f;
			//_velocity.x = player.get()->getPosition().x - _parent->getPosition().x;
		}
		
		Vector2f bul_pl_dif = _parent->getPosition() - player->getPosition();
		bul_pl_dif = Vector2f(fabs(bul_pl_dif.x), fabs(bul_pl_dif.y));
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
	else {

	}
}

void MissileMovementComponent::setSeeking(bool b) { _seeking = b; }

bool MissileMovementComponent::getSeeking() const { return _seeking; }

void MissileMovementComponent::setPhysics(shared_ptr<PhysicsComponent> phys) { _parentPhysics = phys; }

shared_ptr<PhysicsComponent> MissileMovementComponent::getPhysics() const { return _parentPhysics; }

MissileMovementComponent::MissileMovementComponent(Entity* p, sf::Vector2f vel, bool seek, _entityCategory cat) : MovementComponent(p, vel), _seeking(seek), cat(cat) {	
	_parentPhysics = _parent->GetCompatibleComponent<PhysicsComponent>()[0];
	_parentSprite = _parent->GetCompatibleComponent<SpriteComponent>()[0];
	b2FixtureDef missileRadar;
	b2CircleShape circleShape;
	circleShape.m_radius = 64;	
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
