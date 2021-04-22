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
	int _flySpeedUpdateState;
	int _damageUpdateState;
	int _fireRateUpdateState;
	int _bulletNumberUpdateState;
	int _maxUpdate;

public:
	PlayerComponent() = delete;
	void Load();
	void revive();
	void render() override {};
	void update(double dt);
	void setPlayerAlive(bool b);
	void setFlySpeed(int speed);
	int getFlySpeedUpdateState();
	int getDamageUpdateState();
	int getFireRateUpdateState();
	int getBulletNumberUpdateState();
	int getPlayerLifes();
	void setPlayerLifes(int life);
	void setFlySpeedUpdateState(int state);
	void setDamageUpdateState(int state);
	void setFireRateUpdateState(int state);
	void setBulletNumberUpdateState(int state);
	void setMaxUpdate(int max);
	int getMaxUpdate();
	void setMaxLifes(int max);
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

	explicit PlayerComponent(Entity* p, textureSettings playerTextureHelper, textureSettings bulletTextureHelper, playerSettings playerSettings, weaponSettings weaponSettings, bulletSettings bulletSettings);
};