#pragma once
#include <SFML/Graphics.hpp>
#include "../components/cmp_sprite.h"
#include "../components/cmp_weapon.h"
#include "../components/cmp_bullet.h"
#include "../game.h"
#include "../settings/enemy_settings.h"
#include "../settings/weapon_settings.h"
#include <LevelSystem.h>

using namespace sf;

class EnemyComponent : public Component {
protected:
	textureSettings _enemyTextureHelper;
	textureSettings _bulletTextureHelper;
	enemySettings _enemySettings;
	weaponSettings _weaponSettings;
	bulletSettings _bulletSettings;

public:
	void Load(int index);
	void render() override {};
	void update(double dt);

	EnemyComponent() = delete;
	explicit EnemyComponent(Entity* p, textureSettings enemyTextureHelper, textureSettings bulletTextureHelper, enemySettings enemySettings, weaponSettings weaponSettings, bulletSettings bulletSettings);
};

