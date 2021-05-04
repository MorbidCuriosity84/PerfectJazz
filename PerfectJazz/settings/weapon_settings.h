#pragma once
#include <ecm.h>
#include "../game.h"


//Defines all the fields for the weapon component
struct weaponSettings {
	Scene* scene;
	double fireTime;
	double fireTimer;
	int numBullets;
	int firerateUpgradeCount;
	int numBulletsUpgradeCount;
	float direction;
	SOUNDS sound;
	float volume;
	float pitch;

	//Default constructor
	weaponSettings() {}
	//Constructor with parameters
	weaponSettings(double _fireTime, int _numBullets, Scene* _scene, float _direction, int _firerateUpgradeCount, int _numBulletsUpgradeCount, SOUNDS snd, float vol, float pit)
		: fireTime(_fireTime), numBullets(_numBullets), scene(_scene), direction(_direction), firerateUpgradeCount(_firerateUpgradeCount), numBulletsUpgradeCount(_numBulletsUpgradeCount), sound(snd), volume(vol), pitch(pit) {
	}
};

class WeaponSettings {
public:
	//Creates an instance of the struct weaponSettings depending of the type of weapon
	static weaponSettings LoadSettings(_weaponType type, Scene* scene);
};

