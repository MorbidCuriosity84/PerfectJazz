#pragma once

#include <ecm.h>
#include "Box2D/Dynamics/Contacts/b2Contact.h"

class HealthComponent : public Component {
protected:
	float _health;

public:
	//HealthComponent();	
	HealthComponent(Entity* p);

	void update(double dt) override;

	void render() override ;

	~HealthComponent();

	float getHealth();
	void addHealth(float health2add);

	void handleContact(b2Contact* contact);
};