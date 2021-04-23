#pragma once
#include <ecm.h>
#include "../game.h"

struct weaponSettings {
	Scene* scene;
	double fireTime;
	double fireTimer;
	int numBullets;
	int firerateUpgradeCount;
	int numBulletsUpgradeCount;
	float direction;

	weaponSettings() {}
	weaponSettings(double _fireTime, int _numBullets, Scene* _scene, float _direction, int _firerateUpgradeCount, int _numBulletsUpgradeCount)
		: fireTime(_fireTime), numBullets(_numBullets), scene(_scene), direction(_direction), firerateUpgradeCount(_firerateUpgradeCount), numBulletsUpgradeCount(_numBulletsUpgradeCount){
	}
};
class WeaponSettings {
public:
	static weaponSettings LoadSettings(_weaponType type, Scene* scene);
};

