#pragma once
#include "cmp_enemy.h"
class Boss : public EnemyComponent
{
protected:
	bool invincible = false;
	float invTimer = 5.f;
	int numKamikazes = 4;		
	float trigger = 0.f;
public:
	std::shared_ptr<MovementComponent> moveCMP;

	void update(double dt) override;
	void render() {};
	void spawnKamikazes(int i);
	void switchSprite(double dt);
	Boss(Entity* p, textureSettings enemyTextureHelper, textureSettings bulletTextureHelper, enemySettings enemySettings, weaponSettings weaponSettings, bulletSettings bulletSettings, int index);
	~Boss() = default;
};

