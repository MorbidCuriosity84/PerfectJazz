#pragma once
#include "../game.h"
#include "../settings/weapon_settings.h"
#include "cmp_damage.h"
#include "cmp_bullet.h"
#include "cmp_sprite.h"
#include "cmp_physics.h"
#include <ecm.h>

using namespace sf;
using namespace std;
// Weapon component that sets the fire rate and the number of bullets shoot
class WeaponComponent : public Component {
protected:
	textureSettings _bulletTextureHelper;
public:
	void update(double dt) override;
	void render() override {};
	void fire();	
	void setDamage(uint16_t damage);
	uint16_t getDamage() const;
	weaponSettings _wSettings;
	bulletSettings _bSettings;
	float accumulation;
	explicit WeaponComponent(Entity* p, weaponSettings settings, bulletSettings bSettings, textureSettings bTextureHelper);
	WeaponComponent() = delete;
};
