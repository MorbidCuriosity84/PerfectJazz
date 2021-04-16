#pragma once
#include "cmp_damage.h"
#include "cmp_sprite.h"
#include "../game.h"
#include <ecm.h>
#include "cmp_physics.h"
#include <system_renderer.h>

using namespace sf;
using namespace std;

struct wepSettings {
	Scene* scene;
	double fireTime;
	double fireTimer;
	int damage;
	int numBullets;

	wepSettings() {}
	wepSettings(double _fireTime, int _numBullets, Scene* _scene)
		: fireTime(_fireTime), fireTimer(_fireTime), numBullets(_numBullets), scene(_scene) {
	}
};

class WeaponComponent : public Component {
protected:
	wepSettings _settings;
public:
	void update(double dt) override;
	void render() override {};
	void fire();
	void setDamage(uint16_t damage);
	uint16_t getDamage() const;
	explicit WeaponComponent(Entity* p, wepSettings settings);
	WeaponComponent() = delete;
};


