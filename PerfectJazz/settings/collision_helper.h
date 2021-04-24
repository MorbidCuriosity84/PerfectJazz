#pragma once
#include "../components/cmp_hp.h"
#include "../components/cmp_damage.h"
#include "../movement/cmp_missile_movement.h"

/*
* @param shared_ptr<HPComponent hpCMP, shared_ptr<damageCMP>, shared_ptr<MissileMovementComponent>, bool isMissile
*
* Helper to allow collision between multiple different object types. Gets attached to physics body user data
* and then used within begin contact to determine how to handle the contact. Missiles will trigger on contact with radar body
* and then set target as closest valid target
*/
struct collisionHelper {
    HPComponent* hpCMP;
    DamageComponent* damageCMP;
    //PowerupComponent* powerupCMP;
    MissileMovementComponent* missileCMP;
    bool isMissile;
    bool isPowerup;

    collisionHelper() : isMissile(false), isPowerup(false), hpCMP(nullptr), damageCMP(nullptr), missileCMP(nullptr)
    {
        
    }
};
