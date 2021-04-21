#pragma once
#include "ecm.h"
#include "cmp_movement.h"
#include "../game.h"

using namespace sf;

class MissileMovementComponent : public MovementComponent
{
protected:
	bool _seeking;
public:
	void update(double dt) override;	

	void setSeeking(bool b);
	bool getSeeking() const;

	MissileMovementComponent(Entity* p, sf::Vector2f vel, bool seek);
};

