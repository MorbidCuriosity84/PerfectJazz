#pragma once
#include <ecm.h>
#include "../game.h"

struct weaponSettings {
	Scene* scene;
	double fireTime;
	double fireTimer;
	int damage;
	int numBullets;
	float direction;

	weaponSettings() {}
	weaponSettings(double _fireTime, int _numBullets, Scene* _scene, float _direction)
		: fireTime(_fireTime), fireTimer(_fireTime), numBullets(_numBullets), scene(_scene), direction(_direction) {
	}
};
class WeaponSettings {
public:
	static weaponSettings LoadSettings(_weaponType type, Scene* scene);
};

