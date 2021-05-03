#include "weapon_settings.h"

//Loads settings for different types of weapon, depending on the type
weaponSettings WeaponSettings::LoadSettings(_weaponType type, Scene* scene) {

	weaponSettings settings;

	//Switches between different settings for different cases of weapon types
	switch (type) {
	case GUN:
	{
		settings.fireTime = 1.75f;			// Sets the fire rate the weapon will shoot
		settings.fireTimer = 0;				// Sets the timer for the fire rate
		settings.firerateUpgradeCount = 0;	// Sets the current upgrade status
		settings.numBulletsUpgradeCount = 0;// Sets the current upgrade status
		settings.numBullets = 0;			// Sets the number of bullets
		settings.scene = scene;				// Sets the scene
		settings.direction = 1.f;			// Sets the direction of the weapon
		settings.sound = MISSILE_FIRE_2;	// Sets the sound for the weapon
		settings.volume = 0.15f;			// Sets the volume for the weapon sound
		settings.pitch = 1.f;				// Sets the pitch for the weapon sound
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
	//Return the settings 
	return settings;
}
