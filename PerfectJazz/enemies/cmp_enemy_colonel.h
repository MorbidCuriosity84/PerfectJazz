#pragma once
#include "../components/cmp_physics.h"
#include <ecm.h>

class ColonelEnemyComponent : public Component {
protected:
	void fire() const;
	float _firetime;

public:
	void Load(int _index);
	void update(double dt) override;
	void render() override {}
	explicit ColonelEnemyComponent(Entity* p);
	ColonelEnemyComponent() = delete;
};
