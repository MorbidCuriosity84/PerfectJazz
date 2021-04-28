#pragma once
#include "../settings/collision_helper.h"
#include "../components/cmp_physics.h"
#include "ecm.h"
#include "../game.h"

using namespace std;

class RadarComponent : public Component
{
protected:
	collisionHelper _colHelp;
	std::shared_ptr<PhysicsComponent> rPhysCMP;
	_entityCategory _cat;
	float _radius;
public:
	void update(double dt) override {}
	void render() {}
	RadarComponent(Entity* p, float radius, _entityCategory cat);
	~RadarComponent() = default;	
	void setRadarFixture();

	/*bool wasTriggered;
	unsigned int contactCount;*/
	
};

