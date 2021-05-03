#pragma once
#include "cmp_enemy.h"
#include <ecm.h>
#include <engine.h>
#include "../settings/texture_helper_settings.h"
#include "../settings/enemy_settings.h"
#include "../settings/weapon_settings.h"
#include "../settings/bullet_settings.h"

class Beserker : public EnemyComponent
{
protected:
	bool goneBeserk;
	float beserkTime;
	float lifetime;
	bool seeking;
public:
	std::shared_ptr<WeaponComponent> weapon2;
	std::shared_ptr<WeaponComponent> weapon3;
	std::shared_ptr<MovementComponent> moveCMP;

	Beserker(Entity* p, textureSettings enemyTextureHelper, textureSettings bulletTextureHelper, enemySettings enemySettings, weaponSettings weaponSettings, bulletSettings bulletSettings, int index);
	~Beserker() = default;
	void update(double dt);
	void render() {};

	void goBeserk();
};

