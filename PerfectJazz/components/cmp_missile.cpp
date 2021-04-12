#include "cmp_missile.h"
#include "maths.h"
#include "Box2D/Collision/Shapes/b2CircleShape.h"
#include "cmp_physics.h"

void MissileComponent::update(double dt)
{
	auto pl = player.get();

	if (_seeking) {
		//seek behaviour		
	}
	else {
		//dumb behaviour
	}

	if (length(pl->getPosition() - _parent->getPosition()) < 25.0) {
		pl->setVisible(false);
		pl->setAlive(false);
		pl->setPosition({ -50.f, -50.f });
		_parent->setVisible(false);
		_parent->setAlive(false);
		_parent->setPosition({ -50.f, -50.f });
	}
}

MissileComponent::MissileComponent(Entity* p, bool seek, double range, _entityCategory category) : Component(p), _seeking(seek), _seekRange(range) 
{
	auto phys = _parent->GetCompatibleComponent<PhysicsComponent>()[0];
	_body = phys.get()->getBody();	
	b2CircleShape circleShape;
	circleShape.m_radius = _seekRange;
	b2FixtureDef mFixtureDef;
	mFixtureDef.shape = &circleShape;
	mFixtureDef.isSensor = true;	
	if (category == PLAYER) {
		mFixtureDef.filter.categoryBits = PLAYER; //belongs to player group
		mFixtureDef.filter.maskBits = ENEMY; //only collides with enemy group
	}
	else {
		mFixtureDef.filter.categoryBits = ENEMY;
		mFixtureDef.filter.maskBits = PLAYER;
	}
	auto f = _body->CreateFixture(&mFixtureDef);
	_fixture = f;
}

b2Fixture* MissileComponent::getFixture()
{
	return _fixture;
}

b2Body* MissileComponent::getBody()
{
	return _body;
}

void MissileComponent::setSenors(bool sensor)
{	
	_fixture->SetSensor(sensor);
}
