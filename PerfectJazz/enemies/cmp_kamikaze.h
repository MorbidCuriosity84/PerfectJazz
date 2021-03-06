#pragma once
#include "cmp_enemy.h"
#include "ecm.h"
#include "../movement/cmp_missile_movement.h"
#include "../movement/cmp_radar.h"

using namespace std;

//Adds the necessary components for the kamikaze enemy to act like one
class Kamikaze : public EnemyComponent
{
protected:
	std::shared_ptr<MissileMovementComponent> missileCMP;
	std::shared_ptr<RadarComponent> radarCMP;
	bool isLoaded;
public:	
	Kamikaze(Entity* p, textureSettings enemyTextureHelper, textureSettings bulletTextureHelper, enemySettings enemySettings, weaponSettings weaponSettings, bulletSettings bulletSettings, int index);
	~Kamikaze() = default;
	void update(double dt);
	void render() {};

};