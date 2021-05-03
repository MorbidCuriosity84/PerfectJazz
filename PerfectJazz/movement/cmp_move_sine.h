#pragma once
#include "cmp_movement.h"
#include <cmath>

using namespace sf;
//Creates a sine wave movement
class SineMovementComponent : public MovementComponent
{
protected:
	float _maxAngle;
	double _accumulation;
	float _multiplier;	
	
public:
	void update(double dt) override;	
	void setMaxAngle(float ang);
	float getMaxAngle() const;
	void setMultiplier(float multi);
	
	SineMovementComponent(Entity* p, sf::Vector2f vel, float maxAngle, Vector2f initPos, bool l);
};

