#include "weapon_settings.h"

weaponSettings WeaponSettings::LoadSettings(_weaponType type, Scene* scene) {

	weaponSettings settings;

	switch (type) {
	case GUN:
	{
		settings.fireTime = 1.75f;
		settings.fireTimer = 0;
		settings.firerateUpgradeCount = 0;
		settings.numBulletsUpgradeCount = 0;
		settings.numBullets = 0;
		settings.scene = scene;
		settings.direction = 1.f;
		settings.sound = MISSILE_FIRE_2;
		settings.volume = 0.15f;
		settings.pitch = 1.f;
		break;
	}

	case MACHINE_GUN:
	{
		settings.fireTime = 1.2f;
		settings.fireTimer = 0;
		settings.firerateUpgradeCount = 0;
		settings.numBulletsUpgradeCount = 0;
		settings.numBullets = 0;
		settings.scene = scene;
		settings.direction = 1.f;
		settings.sound = BULLET_FIRE_2;
		settings.volume = 0.15f;
		settings.pitch = 1.f;
		break;
	}
	case ROCKET_LAUNCHER:
	{
		settings.fireTime = 2.5f;
		settings.fireTimer = 0;
		settings.firerateUpgradeCount = 0;
		settings.numBulletsUpgradeCount = 0;
		settings.numBullets = 0;
		settings.scene = scene;
		settings.direction = 1.f;
		settings.sound = MISSILE_FIRE_1;
		settings.volume = 0.15f;
		settings.pitch = 1.f;
		break;
	}
	case NONE:
		settings.fireTime = 1000000.f;
		settings.fireTimer = 0;
		settings.firerateUpgradeCount = 0;
		settings.numBulletsUpgradeCount = 0;
		settings.numBullets = 0;
		settings.scene = scene;
		settings.direction = 1.f;
		settings.sound = MISSILE_FIRE_2;
		settings.volume = 0.15f;
		settings.pitch = 1.f;
		break;
	case PLAYER_GUN:
	{
		settings.fireTime = .2f;
		settings.fireTimer = 0;
		settings.firerateUpgradeCount = 0;
		settings.numBulletsUpgradeCount = 0;
		settings.numBullets = 0;
		settings.scene = scene;
		settings.direction = -1.f;
		settings.sound = MISSILE_FIRE_2;
		settings.volume = 0.35f;
		settings.pitch = 1.f;
		break;
	}
	default:
		break;
	}
	return settings;
}
