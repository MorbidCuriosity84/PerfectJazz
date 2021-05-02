#pragma once

#include "cmp_sprite.h"
#include "ecm.h"
#include "../game.h"
#include <Box2D/Dynamics/b2Body.h>

class PhysicsComponent : public Component {
protected:
	b2Body* _body;
	const bool _dynamic;
	b2Fixture* _fixture;
	double timer;

public:
	PhysicsComponent(Entity* p, bool dyn, const sf::Vector2f& size);

	b2Fixture* const getFixture() const;
	b2Body* getBody();
	const sf::Vector2f getVelocity() const;
	void setFriction(float r);
	void setMass(float m);
	void update(double dt) override;
	void render() override;
	void impulse(const sf::Vector2f& i);
	void dampen(const sf::Vector2f& s);
	void setVelocity(const sf::Vector2f& v);
	void teleport(const sf::Vector2f& v);
	void setSensor(bool b);
	void setCategory(_entityCategory cat);
	~PhysicsComponent() override;
};