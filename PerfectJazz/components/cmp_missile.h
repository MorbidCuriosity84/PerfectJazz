#pragma once

#include <ecm.h>
#include <Box2D/Dynamics/b2Body.h>
#include <Box2D/Dynamics/b2Fixture.h>
#include "../game.h"

class MissileComponent : Component {
protected:
	b2Fixture* _fixture;
	b2Body* _body;
	bool _seeking;
	double _seekRange;

public:
	void update(double dt) override;
	void render() override {}
	explicit MissileComponent(Entity* p, bool seek, double range, _entityCategory category);
	MissileComponent() = delete;

	b2Fixture* getFixture();
	b2Body* getBody();
	void setSenors(bool sensor);

};