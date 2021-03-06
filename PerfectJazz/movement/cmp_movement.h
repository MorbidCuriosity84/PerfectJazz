#pragma once
#include "ecm.h"
#include "../components/cmp_physics.h"

using namespace sf;
using namespace std;
//Adds movement, allowing the entity to move accross the screen
class MovementComponent : public Component
{
protected:
	sf::Vector2f _velocity;
	bool linger;
	float lingerTime;
	bool active;
	Vector2f parentInitVelocity;
	Vector2f initPosition;
public:
	void update(double dt) override;
	void render() override;

	std::shared_ptr<PhysicsComponent> parentPhysics;

	void setVelocity(sf::Vector2f vel);
	sf::Vector2f getVelocity() const;

	void setLingerTime(float t);
	void isLinger(bool b);	
	void isActive(bool b);

	MovementComponent(Entity* p, sf::Vector2f velocity, Vector2f initPos, bool linger);
};

