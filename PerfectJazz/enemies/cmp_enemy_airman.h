#pragma once
#include "../components/cmp_physics.h"
#include <ecm.h>

class AirManEnemyComponent : public Component {
protected:
	void fire() const;
	float _firetime;

public:
	void Load(int _index);
	void update(double dt) override;
	void render() override {}
	explicit AirManEnemyComponent(Entity* p);
	AirManEnemyComponent() = delete;
};
