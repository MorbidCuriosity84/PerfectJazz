#pragma once
#include <ecm.h>
#include <SFML/Graphics.hpp>
#include "../components/cmp_sprite.h"
#include "../components/cmp_weapon.h"
#include "../components/cmp_bullet.h"
#include "../game.h"
#include "../settings/player_settings.h"
using namespace sf;

class PlayerComponent : public Component {
protected:
	textureSettings _playerTextureHelper;
	textureSettings _bulletTextureHelper;
	weaponSettings _weaponSettings;
	bulletSettings _bulletSettings;
	bool _playerAlive;

public:
	void Load();
	void revive();
	void render() override {};
	void update(double dt);
	void setPlayerAlive(bool b);
	bool isAlive();
	void setAlive(bool b);
	playerSettings _playerSettings;

	PlayerComponent() = delete;
	explicit PlayerComponent(Entity* p, textureSettings playerTextureHelper, textureSettings bulletTextureHelper, playerSettings playerSettings, weaponSettings weaponSettings, bulletSettings bulletSettings);
};