#include "myContactListener.h"
#include <iostream>
#include <ecm.h>
#include "../components/cmp_bullet.h"
#include "../components/cmp_hp.h"
#include "../settings/collision_helper.h"

//Checks for intial contact betwee two bodies
void myContactListener::BeginContact(b2Contact* contact) {

	//Creates a pointer to  the different fixtures in collision
	collisionHelper* helper1 = static_cast<collisionHelper*>(contact->GetFixtureA()->GetBody()->GetUserData()); //Fixture A collision helper
	collisionHelper* helper2 = static_cast<collisionHelper*>(contact->GetFixtureB()->GetBody()->GetUserData()); //Fixture B collision helper
	
	//Checks if the second fixture is a missile and sets it to seek
	if (contact->GetFixtureB()->GetFilterData().categoryBits == 256) {
		helper2->missileCMP->setSeeking(true);
		helper2->isMissileRadar = false;
		return;
	}
	//Checks if the first fixture is a missile and sets it to seek
	if (contact->GetFixtureA()->GetFilterData().categoryBits == 256) {
		helper1->missileCMP->setSeeking(true);						
		helper1->isMissileRadar = false;
		return;
	}	
	//If missile contacts the other body, damage is applied
	if (!(helper1->isMissileRadar || helper2->isMissileRadar)) {
		helper1->damageCMP->applyDamage(helper2->hpCMP);
		helper2->damageCMP->applyDamage(helper1->hpCMP);
	}			
}