#pragma once
#include "cmp_enemy.h"

//Adds a specific behaviour for the players type boss
class Boss : public EnemyComponent
{
protected:
	bool invincible = false;
	float invTimer = 5.f;
	int numKamikazes = 4;		
	float trigger = 0.f;
	bool inv1;
	bool inv2;
	bool inv3;
public:
	std::shared_ptr<MovementComponent> moveCMP;

	void update(double dt) override;
	void render() {};
	void spawnKamikazes(int i);
	Boss(Entity* p, textureSettings enemyTextureHelper, textureSettings bulletTextureHelper, enemySettings enemySettings, weaponSettings weaponSettings, bulletSettings bulletSettings, int index);
	~Boss() = default;
};

