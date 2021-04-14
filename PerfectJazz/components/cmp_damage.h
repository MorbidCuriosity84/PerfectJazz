#pragma once

#include <ecm.h>
#include "cmp_hp.h"

using namespace std;

class DamageComponent : public Component
{
protected:
	uint16_t _damage;

public:
	void update(double dt) override;
	void render() override;

	DamageComponent() = delete;
	explicit DamageComponent(Entity* p, uint16_t damage);

	void setDamage(uint16_t);
	uint16_t getDamage() const;
	void applyDamage(HPComponent* hp);
};

