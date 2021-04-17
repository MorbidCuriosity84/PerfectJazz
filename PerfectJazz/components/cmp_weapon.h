#pragma once
#include "../game.h"
#include "cmp_damage.h"
#include "cmp_bullet.h"
#include "cmp_sprite.h"
#include "cmp_physics.h"
#include <ecm.h>
#include <system_renderer.h>

using namespace sf;
using namespace std;

struct wepSettings {
	Scene* scene;
	double fireTime;
	double fireTimer;
	int damage;
	int numBullets;
	float direction;

	wepSettings() {}
	wepSettings(double _fireTime, int _numBullets, Scene* _scene, float _direction)
		: fireTime(_fireTime), fireTimer(_fireTime), numBullets(_numBullets), scene(_scene), direction(_direction) {
	}
};

class WeaponComponent : public Component {
protected:
	wepSettings _wSettings;
	bulletSettings _bSettings;
	textureHelper _bulletTextureHelper;
public:
	void update(double dt) override;
	void render() override {};
	void fire();
	void setDamage(uint16_t damage);
	uint16_t getDamage() const;
	explicit WeaponComponent(Entity* p, wepSettings settings, bulletSettings bSettings, textureHelper bTextureHelper);
	WeaponComponent() = delete;
};


