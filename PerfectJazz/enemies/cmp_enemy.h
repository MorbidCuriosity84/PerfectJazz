#pragma once

#include <SFML/Graphics.hpp>
#include "../components/cmp_sprite.h"
#include "../components/cmp_weapon.h"
#include "../components/cmp_bullet.h"
#include "../components/cmp_physics.h"
#include "../components/cmp_damage.h"
#include "../components/cmp_hp.h"
#include "../game.h"
#include "../settings/enemy_settings.h"
#include "../settings/weapon_settings.h"
#include <LevelSystem.h>
#include "../settings/collision_helper.h"

using namespace sf;

class EnemyComponent : public Component {
protected:
	textureSettings _enemyTextureHelper;
	textureSettings _bulletTextureHelper;
	enemySettings _enemySettings;
	weaponSettings _weaponSettings;
	bulletSettings _bulletSettings;
	collisionHelper en_colHelp;
	int currentHP;
public:
	std::shared_ptr<SpriteComponent> spriteCMP;
	std::shared_ptr<DamageComponent> damageCMP;
	std::shared_ptr<HPComponent> hpCMP;
	std::shared_ptr<PhysicsComponent> physicsCMP;
	std::shared_ptr<WeaponComponent> weaponCMP;
	SOUNDS sound;
	float accumulation;
	void Load(int index);
	void render() override {};
	void update(double dt);

	EnemyComponent() = delete;
	explicit EnemyComponent(Entity* p, textureSettings enemyTextureHelper, textureSettings bulletTextureHelper, enemySettings enemySettings, weaponSettings weaponSettings, bulletSettings bulletSettings, int index);
};

