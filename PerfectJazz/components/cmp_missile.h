#pragma once

#include <ecm.h>
#include <Box2D/Dynamics/b2Body.h>
#include <Box2D/Dynamics/b2Fixture.h>
#include "../game.h"
#include "cmp_weapon.h"

class MissileComponent : public WeaponComponent {
protected:	
	bool _seeking;
	double _seekRange;

public:
	void update(double dt) override;
	void render() override;
	void fire() override;
	explicit MissileComponent(Entity* p, bool seek, double range, _entityCategory category, textureHelper texHelper, wepSettings settings);
	MissileComponent() = delete;	

};