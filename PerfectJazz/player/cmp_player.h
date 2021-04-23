#pragma once
#include "ecm.h"
#include "../components/cmp_sprite.h"
#include "../components/cmp_weapon.h"
#include "../components/cmp_bullet.h"
#include "../components/cmp_player_physics.h"
#include "../components/cmp_damage.h"
#include "../components/cmp_hp.h"
#include "../settings/player_settings.h"
#include "../settings/collision_helper.h"

using namespace sf;
using namespace std;

class PlayerComponent : public Component {
protected:
	bool _gracePeriod;
	float _gracePeriodTimer;
	float _visibilityTimer;
	int _maxUpdate;

public:
	PlayerComponent() = delete;
	explicit PlayerComponent(Entity* p, textureSettings playerTextureHelper, textureSettings bulletTextureHelper, playerSettings playerSettings, weaponSettings weaponSettings, bulletSettings bulletSettings);
	void Load();
	void revive();
	void render() override {};
	void update(double dt);
	void setPlayerAlive(bool b);
	void setPlayerLifes(int life);
	void setFlySpeedUpgradeState(int state);
	void setDamageUpgradeState(int state);
	void setFireRateUpgradeState(int state);
	void setBulletNumberUpgradeState(int state);
	void setMaxUpdate(int max);
	void setMaxLifes(int max);
	int getFlySpeedUpgradeState();
	int getDamageUpgradeState();
	int getFireRateUpgradeState();
	int getBulletNumberUpgradeState();
	int getPlayerLifes();
	int getMaxUpdate();
	int getMaxLifes();
	textureSettings _playerTextureHelper;
	textureSettings _bulletTextureHelper;
	weaponSettings _weaponSettings;
	bulletSettings _bulletSettings;
	std::shared_ptr<SpriteComponent> spriteCMP;
	std::shared_ptr<DamageComponent> damageCMP;
	std::shared_ptr<HPComponent> hpCMP;
	std::shared_ptr<PlayerPhysicsComponent> physicsCMP;
	std::shared_ptr<WeaponComponent> weaponCMP;
	playerSettings _playerSettings;
	collisionHelper colHelp;

};