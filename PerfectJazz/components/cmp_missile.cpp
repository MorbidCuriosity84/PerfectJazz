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
	phys.get()->setCategory(category);
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
