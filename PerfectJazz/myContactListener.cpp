#include "myContactListener.h"
#include <iostream>
#include <ecm.h>
#include "components/cmp_bullet.h"
#include "components/cmp_hp.h"


void myContactListener::BeginContact(b2Contact* contact) {

    cout << contact->GetFixtureA()->GetFilterData().categoryBits << endl;
    cout << contact->GetFixtureB()->GetFilterData().categoryBits << endl;

    HPComponent* entContact1;    
    
    entContact1 = static_cast<HPComponent*>(contact->GetFixtureA()->GetBody()->GetUserData());
    entContact1->handleContact(contact);    
}

void myContactListener::EndContact(b2Contact* contact) {
   
}
