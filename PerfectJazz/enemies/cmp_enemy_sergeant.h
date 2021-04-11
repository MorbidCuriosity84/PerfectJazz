#pragma once
#include "../components/cmp_physics.h"
#include <ecm.h>

class SergeantEnemyComponent : public Component {
protected:
	void fire() const;
	float _firetime;

public:
	void Load(int _index);
	void update(double dt) override;
	void render() override {}
	explicit SergeantEnemyComponent(Entity* p);
	SergeantEnemyComponent() = delete;
};
