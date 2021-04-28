#include "myContactListener.h"
#include <iostream>
#include <ecm.h>
#include "components/cmp_bullet.h"
#include "components/cmp_hp.h"
#include "settings/collision_helper.h"


void myContactListener::BeginContact(b2Contact* contact) {

	collisionHelper* helper1 = static_cast<collisionHelper*>(contact->GetFixtureA()->GetBody()->GetUserData()); //Fixture A collision helper
	collisionHelper* helper2 = static_cast<collisionHelper*>(contact->GetFixtureB()->GetBody()->GetUserData()); //Fixture B collision helper

	/*auto fix = contact->GetFixtureA()->GetBody()->GetFixtureList();
	auto fix2 = contact->GetFixtureB()->GetBody()->GetFixtureList();
	cout << "Is 1 sensor = " << fix->IsSensor() << endl;
	cout << "Is 2 sensor = " << fix2->IsSensor() << endl;*/
	
	cout << contact->GetFixtureA()->GetFilterData().categoryBits << endl;
	cout << contact->GetFixtureB()->GetFilterData().categoryBits << endl;

	/*if (helper2->isMissileRadar) {
		cout << "Radar contact" << endl;
		helper2->missileCMP->setSeeking(true);
		helper2->isMissileRadar = false;
		return;
	}
	if (helper1->isMissileRadar) {
		cout << "Radar contact" << endl;
		helper1->missileCMP->setSeeking(true);
		helper1->isMissileRadar = false;
		return;
	}*/

	if (contact->GetFixtureB()->GetFilterData().categoryBits == 256) {
		cout << "Radar contact" << endl;
		helper2->missileCMP->setSeeking(true);
		helper2->isMissileRadar = false;
		return;
	}
	if (contact->GetFixtureA()->GetFilterData().categoryBits == 256) {
		cout << "Radar contact" << endl;
		helper1->missileCMP->setSeeking(true);						
		helper1->isMissileRadar = false;
		return;
	}
	
	if (!(helper1->isMissileRadar || helper2->isMissileRadar)) {
		helper1->damageCMP->applyDamage(helper2->hpCMP);
		helper2->damageCMP->applyDamage(helper1->hpCMP);
	}			
}

void myContactListener::EndContact(b2Contact* contact) {

	collisionHelper* helper1 = static_cast<collisionHelper*>(contact->GetFixtureA()->GetBody()->GetUserData()); //Fixture A collision helper
	collisionHelper* helper2 = static_cast<collisionHelper*>(contact->GetFixtureB()->GetBody()->GetUserData()); //Fixture B collision helper

	/*if (helper2->isMissileRadar) {
		cout << "Radar end contact" << endl;
		helper2->missileCMP->contactCount > 1 ? helper2->missileCMP->setSeeking(false) : helper2->missileCMP->setSeeking(true);		
	}
	if (helper1->isMissileRadar) {
		cout << "Radar end contact" << endl;		
		helper1->missileCMP->contactCount > 1 ? helper2->missileCMP->setSeeking(false) : helper2->missileCMP->setSeeking(true);
	}*/
}
