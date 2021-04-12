#include "myContactListener.h"
#include <iostream>

myContactListener::myContactListener() : b2ContactListener(), _contacts()
{
}

myContactListener::~myContactListener()
{
}

void myContactListener::BeginContact(b2Contact* contact) {

    cout << contact->GetFixtureA()->GetFilterData().categoryBits << endl;
    cout << contact->GetFixtureB()->GetFilterData().categoryBits << endl;
    /*auto cont = make_shared<myContact>();
    cont.get()->fixtureA = contact->GetFixtureA();
    cont.get()->fixtureB = contact->GetFixtureB();
    _contacts.push_back(cont);*/
}

void myContactListener::EndContact(b2Contact* contact) {
    /*myContact my_contact = { contact->GetFixtureA(), contact->GetFixtureB() };
    std::vector<shared_ptr<myContact>>::iterator pos;
    pos = std::find(_contacts.begin(), _contacts.end(), my_contact);
    if (pos != _contacts.end()) {
        _contacts.erase(pos);
    }*/
}
