#pragma once
//#include <Box2D/Box2D.h>
#include <vector>
#include <Box2D/Dynamics/b2Fixture.h>
#include <Box2D/Dynamics/Contacts/b2Contact.h>
#include <Box2D/Dynamics/b2WorldCallbacks.h>

using namespace std;

struct myContact {
    b2Fixture* fixtureA;
    b2Fixture* fixtureB;
    bool operator==(const myContact& other) const
    {
        return (fixtureA == other.fixtureA) && (fixtureB == other.fixtureB);
    }
};

class myContactListener : public b2ContactListener {

public:
    std::vector<std::shared_ptr<myContact>> _contacts;

    /*myContactListener();
    ~myContactListener();*/

    void BeginContact(b2Contact* contact) override;
    void EndContact(b2Contact* contact) override;    
};

