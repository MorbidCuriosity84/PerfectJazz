#pragma once
#include "cmp_physics.h"

class PlayerPhysicsComponent : public PhysicsComponent {
protected:
	b2Vec2 _size;
	sf::Vector2f _maxVelocity;
	float _groundspeed;
	std::string _direction;

public:
	void update(double dt) override;
	std::string GetDirection();
	explicit PlayerPhysicsComponent(Entity* p, const sf::Vector2f& size);
	PlayerPhysicsComponent() = delete;
};
