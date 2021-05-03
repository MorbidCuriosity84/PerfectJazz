#pragma once
#include "cmp_movement.h"
class BossMovement : public MovementComponent
{
protected:
	double accumulation;
	bool stopped;
public:
	BossMovement(Entity* p, sf::Vector2f vel, Vector2f initPos, bool l);
	~BossMovement() = default;

	void update(double dt) override;
	void render() {}
};

