#pragma once
#include "ecm.h"

using namespace sf;
using namespace std;

class MovementComponent : public Component
{
protected:
	sf::Vector2f _velocity;
public:
	void update(double dt) override;
	void render() override;

	std::shared_ptr<PhysicsComponent> parentPhysics;

	void setVelocity(sf::Vector2f vel);
	sf::Vector2f getVelocity() const;

	MovementComponent(Entity* p, sf::Vector2f velocity);
};

