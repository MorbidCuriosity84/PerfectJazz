#include "weapon_settings.h"

weaponSettings WeaponSettings::LoadSettings(_weaponType type, Scene* scene) {

	weaponSettings settings;

	switch (type) {
	case GUN:
	{
		settings.fireTime = 1.5f;
		settings.fireTimer = settings.fireTime;
		settings.firerateUpgradeCount = 0;
		settings.numBulletsUpgradeCount = 2.f;
		settings.numBullets = settings.numBulletsUpgradeCount;
		settings.scene = scene;
		settings.direction = 1.f;
		break;
	}

	case MACHINE_GUN:
	{
		break;
	}
	case ROCKET_LAUNCHER:
	{
		break;
	}
	default:
		break;
	}
	return settings;
}
