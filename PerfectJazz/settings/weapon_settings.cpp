#include "weapon_settings.h"

weaponSettings WeaponSettings::LoadSettings(_weaponType type, Scene* scene) {

	weaponSettings settings;

	switch (type) {
	case GUN:
	{
		settings.fireTime = 1.5f;
		settings.fireTimer = 0;
		settings.firerateUpgradeCount = 0;
		settings.numBulletsUpgradeCount = 1;
		settings.numBullets = 1;
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
