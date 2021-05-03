#pragma once
#include "../components/cmp_hp.h"
#include "../components/cmp_damage.h"
#include "../movement/cmp_missile_movement.h"

/*
* @param shared_ptr<HPComponent hpCMP, shared_ptr<damageCMP>, shared_ptr<MissileMovementComponent>, bool isMissileRadar
*
* Helper to allow collision between multiple different object types. Gets attached to physics body user data
* and then used within begin contact to determine how to handle the contact. Missiles will trigger on contact with radar body
* and then set target as closest valid target
*/
//Defines all the fields for the collision helper
struct collisionHelper {
    HPComponent* hpCMP;
    DamageComponent* damageCMP;
    MissileMovementComponent* missileCMP;
    bool isMissileRadar;
    bool isPowerup;

    //Sets all the bools to false and the components to null
    void nullify() {
        isMissileRadar = false;
        isPowerup = false;
        hpCMP = nullptr;
        damageCMP = nullptr;
        missileCMP = nullptr;
    }

    //Constructor with parameters
    collisionHelper() : isMissileRadar(false), isPowerup(false), hpCMP(nullptr), damageCMP(nullptr), missileCMP(nullptr) {};
};
