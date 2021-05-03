#pragma once
#include "ecm.h"
#include "cmp_movement.h"
#include "../components/cmp_physics.h"
#include "../game.h"

using namespace sf;
using namespace std;

//Movement for the missiles. It uses the seeking method to find
//and target and entity
class MissileMovementComponent : public MovementComponent {
protected:
	bool _seeking;
	std::shared_ptr<PhysicsComponent> _parentPhysics;
	std::shared_ptr<SpriteComponent> _parentSprite;
	_entityCategory cat;
public:
	void update(double dt) override;
	void setSeeking(bool b);
	bool getSeeking() const;
	void setPhysics(std::shared_ptr<PhysicsComponent> phys);	
	std::shared_ptr<PhysicsComponent> getPhysics() const;

	int contactCount;

	MissileMovementComponent(Entity* p, sf::Vector2f vel, bool seek, _entityCategory cat);
};