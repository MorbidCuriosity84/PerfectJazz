#pragma once
#include "cmp_physics.h"

// Player physics component that will add the necessary settings and behaviours
// for the player entity
class PlayerPhysicsComponent : public PhysicsComponent {
protected:
	b2Vec2 _size;
	sf::Vector2f _maxVelocity;
	std::string _direction;
	shared_ptr<SpriteComponent> playerSpriteCMP;

public:
	void update(double dt) override;
	std::string GetDirection();
	void setFlySpeed(int speed);
	explicit PlayerPhysicsComponent(Entity* p, const sf::Vector2f& size);
	PlayerPhysicsComponent() = delete;
};
