#include "powerup_settings.h"

powerupSettings PowerupSettings::LoadSettings(_powerUpsType type, Scene* scene) {

	powerupSettings settings;

	switch (type) {
	case ALL_POWERUPS:
	{
		settings.damage = 0;
		settings.damageUpgradeCount = 0;
		settings.hp = 1;
		settings.lifetime = 10.f;
		settings.scene = scene;
		settings.angle = 0.f;
		settings.category = POWERUP;
		settings.direction = -1.f;
		settings.velocity = Vector2f(0.f, 100.f);
		settings.spriteScale = Vector2f(1.f, 1.f);
		break;
	}	
	default:
		break;
	}
	return settings;
}
