#include "cmp_radar.h"
#include "Box2D/Box2D.h"
#include "../components/cmp_sprite.h"
#include "SFML/Graphics/CircleShape.hpp"

using namespace sf;

RadarComponent::RadarComponent(Entity* p, float radius, _entityCategory cat) : Component(p), _radius(radius), _cat(cat) {	
}

/*
* Function to create radar fixture, this will attach to the parent, so be warned it will give the parent two physics bodies
*/
void RadarComponent::setRadarFixture() {
	auto pPhys = _parent->GetCompatibleComponent<PhysicsComponent>()[0];
	rPhysCMP = _parent->addComponent<PhysicsComponent>(true, Vector2f( 1.f,1.f ));
	rPhysCMP->setAlive(false);
	rPhysCMP->setSensor(true);			
	rPhysCMP->setVelocity(pPhys->getVelocity());
	b2FixtureDef missileRadar;
	b2CircleShape circleShape;

	//Used for debugging radar
	//auto shape = _parent->addComponent<ShapeComponent>();
	//shape->setShape<CircleShape>(240.f);
	//shape->getShape().setOrigin({ 240.f,240.f });
	//shape->getShape().setFillColor(sf::Color(0, 0, 0, 45));
	circleShape.m_radius = 8;
	missileRadar.shape = &circleShape;
	missileRadar.isSensor = true;
	_colHelp.damageCMP = nullptr;
	_colHelp.hpCMP = nullptr;
	_colHelp.isMissileRadar = true;
	if (_cat == ENEMY_MISSILE) {
		rPhysCMP->setCategory(ENEMY_MISSILE_RADAR);
		missileRadar.filter.categoryBits = ENEMY_MISSILE_RADAR;
		missileRadar.filter.maskBits = PLAYER_BODY;
	}
	else {
		rPhysCMP->setCategory(FRIENDLY_MISSILE_RADAR);
		missileRadar.filter.categoryBits = FRIENDLY_MISSILE_RADAR;
		missileRadar.filter.maskBits = ENEMY_BODY;
	}
	_colHelp.missileCMP = _parent->GetCompatibleComponent<MissileMovementComponent>()[0].get();
	rPhysCMP->getBody()->SetUserData(&_colHelp);
	b2Fixture* bFix = rPhysCMP.get()->getBody()->CreateFixture(&missileRadar);	
}
