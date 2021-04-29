#include "weapon_settings.h"

weaponSettings WeaponSettings::LoadSettings(_weaponType type, Scene* scene) {

	weaponSettings settings;

	switch (type) {
	case GUN:
	{
		settings.fireTime = 1.5f;
		settings.fireTimer = 0;
		settings.firerateUpgradeCount = 0;
		settings.numBulletsUpgradeCount = 0;
		settings.numBullets = 0;
		settings.scene = scene;
		settings.direction = 1.f;
		settings.sound = BULLET_FIRE_1;
		break;
	}

	case MACHINE_GUN:
	{
		settings.fireTime = .2f;
		settings.fireTimer = 0;
		settings.firerateUpgradeCount = 0;
		settings.numBulletsUpgradeCount = 0;
		settings.numBullets = 0;
		settings.scene = scene;
		settings.direction = 1.f;
		settings.sound = BULLET_FIRE_2;
		break;
	}
	case ROCKET_LAUNCHER:
	{
		settings.fireTime = 1.5f;
		settings.fireTimer = 0;
		settings.firerateUpgradeCount = 0;
		settings.numBulletsUpgradeCount = 0;
		settings.numBullets = 0;
		settings.scene = scene;
		settings.direction = 1.f;
		settings.sound = MISSILE_FIRE_1;
		break;
	}
	default:
		break;
	}
	return settings;
}
