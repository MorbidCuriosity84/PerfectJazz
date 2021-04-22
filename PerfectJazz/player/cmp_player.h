#pragma once
#include <ecm.h>
#include <SFML/Graphics.hpp>
#include "../components/cmp_sprite.h"
#include "../components/cmp_weapon.h"
#include "../components/cmp_bullet.h"
#include "../components/cmp_player_physics.h"
#include "../components/cmp_physics.h"
#include "../components/cmp_damage.h"
#include "../components/cmp_hp.h"
#include "../settings/player_settings.h"

using namespace sf;

class PlayerComponent : public Component {
protected:
	textureSettings _playerTextureHelper;
	textureSettings _bulletTextureHelper;
	weaponSettings _weaponSettings;
	bulletSettings _bulletSettings;
	bool _gracePeriod;
	float _gracePeriodTimer;
	float _visibilityTimer;

public:
	void Load();
	void revive();
	void render() override {};
	void update(double dt);
	void setPlayerAlive(bool b);
	playerSettings _playerSettings;
	std::shared_ptr<SpriteComponent> spriteCMP;
	std::shared_ptr<DamageComponent> damageCMP;
	std::shared_ptr<HPComponent> hpCMP;
	std::shared_ptr<PlayerPhysicsComponent> physicsCMP;
	std::shared_ptr<WeaponComponent> weaponCMP;

	PlayerComponent() = delete;
	explicit PlayerComponent(Entity* p, textureSettings playerTextureHelper, textureSettings bulletTextureHelper, playerSettings playerSettings, weaponSettings weaponSettings, bulletSettings bulletSettings);
};