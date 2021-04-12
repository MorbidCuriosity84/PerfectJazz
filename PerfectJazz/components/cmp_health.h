#pragma once

#include <ecm.h>
#include "Box2D/Dynamics/Contacts/b2Contact.h"

class HealthComponent : public Component {
protected:
	double _health;

public:
	HealthComponent() = delete;	
	explicit HealthComponent(Entity* p);

	double getHealth();
	void addHealth(double health2add);

	void handleContact(b2Contact* contact);
};