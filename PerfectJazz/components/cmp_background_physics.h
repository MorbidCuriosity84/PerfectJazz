#pragma once

#include "cmp_physics.h"

class BackgroundPhysicsComponent : public PhysicsComponent {
protected:
	b2Vec2 _size;
	sf::Vector2f _Velocity;

public:
	void update(double dt) override;
	explicit BackgroundPhysicsComponent(Entity* p, const sf::Vector2f& size);

	BackgroundPhysicsComponent() = delete;
};