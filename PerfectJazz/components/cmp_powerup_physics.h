#pragma once
#include "cmp_physics.h"

// Powerup physics component gives the entity a body, and updates the powerup position
class PowerupPhysicsComponent : public PhysicsComponent {
protected:
	b2Vec2 _size;
	sf::Vector2f _Velocity;

public:
	void update(double dt) override;
	explicit PowerupPhysicsComponent(Entity* p, const sf::Vector2f& size);
	PowerupPhysicsComponent() = delete;
};