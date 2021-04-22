#pragma once
#include "cmp_physics.h"

class PlayerPhysicsComponent : public PhysicsComponent {
protected:
	b2Vec2 _size;
	sf::Vector2f _maxVelocity;
	std::string _direction;
	int _flySpeed;

public:
	void update(double dt) override;
	std::string GetDirection();
	void setFlySpeed(int speed);
	explicit PlayerPhysicsComponent(Entity* p, const sf::Vector2f& size, int flySpeed);
	PlayerPhysicsComponent() = delete;
};
