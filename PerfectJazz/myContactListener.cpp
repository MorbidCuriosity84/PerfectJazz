#include "myContactListener.h"
#include <iostream>
#include <ecm.h>
#include "components/cmp_bullet.h"
#include "components/cmp_health.h"

HealthComponent* castContact(uint16 categoryBits, b2Body* body)
{
    switch (categoryBits)
    {
        case 1:
        {
            //Boundary
            break;
        }
        case 2:
        {
            //Player        
            return static_cast<HealthComponent*>(body->GetUserData());
            break;
        }
        case 4:
        {
            //Friendly bullet
            return static_cast<HealthComponent*>(body->GetUserData());
            break;
        }
        case 8:
        {
            //Enemy Bullet
            return static_cast<HealthComponent*>(body->GetUserData());
            break;
        }
        case 16:
        {
            //Enemy
            return static_cast<HealthComponent*>(body->GetUserData());
            break;
        }
        case 32:
        {
            //friendly missile
            return static_cast<HealthComponent*>(body->GetUserData());
            break;
        }
        case 64:
        {
            //enemy missile
            return static_cast<HealthComponent*>(body->GetUserData());
            break;
        }

        default:
        {
            break;
        }
    }
}

void myContactListener::BeginContact(b2Contact* contact) {

    cout << contact->GetFixtureA()->GetFilterData().categoryBits << endl;
    cout << contact->GetFixtureB()->GetFilterData().categoryBits << endl;


    HealthComponent* entContact1;
    HealthComponent* entContact2;
    
    entContact1 = castContact(contact->GetFixtureA()->GetFilterData().categoryBits, contact->GetFixtureA()->GetBody());
    entContact2 = castContact(contact->GetFixtureB()->GetFilterData().categoryBits, contact->GetFixtureB()->GetBody());

    entContact1->handleContact(contact);
    entContact2->handleContact(contact);
}

void myContactListener::EndContact(b2Contact* contact) {
    /*myContact my_contact = { contact->GetFixtureA(), contact->GetFixtureB() };
    std::vector<shared_ptr<myContact>>::iterator pos;
    pos = std::find(_contacts.begin(), _contacts.end(), my_contact);
    if (pos != _contacts.end()) {
        _contacts.erase(pos);
    }*/
}
