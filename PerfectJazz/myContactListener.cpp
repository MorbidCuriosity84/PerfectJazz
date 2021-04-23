#include "myContactListener.h"
#include <iostream>
#include <ecm.h>
#include "components/cmp_bullet.h"
#include "components/cmp_hp.h"
#include "settings/collision_helper.h"


void myContactListener::BeginContact(b2Contact* contact) {

    collisionHelper* helper1 = static_cast<collisionHelper*>(contact->GetFixtureA()->GetBody()->GetUserData()); //Fixture A collision helper
    collisionHelper* helper2 = static_cast<collisionHelper*>(contact->GetFixtureB()->GetBody()->GetUserData()); //Fixture B collision helper
    
    cout << contact->GetFixtureA()->GetFilterData().categoryBits << endl;
    cout << contact->GetFixtureB()->GetFilterData().categoryBits << endl;

    if (helper2->isMissile){
        helper2->missileCMP->setSeeking(true);        
        helper2->isMissile = false;
        return;
    }
    if (helper1->isMissile) {
        helper1->missileCMP->setSeeking(true);        
        helper1->isMissile = false;
        return;
    }

    helper1->damageCMP->applyDamage(helper2->hpCMP);
    helper2->damageCMP->applyDamage(helper1->hpCMP);
    
}

void myContactListener::EndContact(b2Contact* contact) {
   
}
