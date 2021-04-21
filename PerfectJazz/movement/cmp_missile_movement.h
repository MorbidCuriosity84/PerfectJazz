#pragma once
#include "ecm.h"
#include "cmp_movement.h"
#include "../components/cmp_physics.h"
#include "../game.h"

using namespace sf;
using namespace std;

class MissileMovementComponent : public MovementComponent
{
protected:
	bool _seeking;
	std::shared_ptr<PhysicsComponent> _parentPhysics;
public:
	void update(double dt) override;	

	void setSeeking(bool b);
	bool getSeeking() const;
	void setPhysics(std::vector<PhysicsComponent> phys);
	std::vector<PhysicsComponent> getPhysics() const;

	MissileMovementComponent(Entity* p, sf::Vector2f vel, bool seek);
};

