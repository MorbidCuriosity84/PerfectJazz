#include "powerup_settings.h"

powerupSettings PowerupSettings::LoadSettings(_powerUpsType type, Scene* scene) {

	powerupSettings settings;	

	switch (type) {
	case ALL_POWERUPS:
	{
		settings.damage = 0;
		settings.damageUpgradeCount = 0;
		settings.hp = 1;
		settings.lifetime = 100.f;
		settings.scene = scene;
		settings.angle = 0.f;
		settings.category = POWERUP;
		settings.direction = -1.f;
		settings.velocity = Vector2f(0.f, 100.f);
		settings.spriteScale = Vector2f(1.f, 1.f);
		settings.sound = PICKUP_4;
		break;
	}	
	case HP_PWU:
		settings.damage = 0;
		settings.damageUpgradeCount = 0;
		settings.hp = 1;
		settings.lifetime = 100.f;
		settings.scene = scene;
		settings.angle = 0.f;
		settings.category = POWERUP;
		settings.direction = -1.f;
		settings.velocity = Vector2f(0.f, 100.f);
		settings.spriteScale = Vector2f(1.f, 1.f);
		settings.sound = PICKUP_1;
		break;
	case DAMAGE_PWU:
		settings.damage = 0;
		settings.damageUpgradeCount = 0;
		settings.hp = 1;
		settings.lifetime = 100.f;
		settings.scene = scene;
		settings.angle = 0.f;
		settings.category = POWERUP;
		settings.direction = -1.f;
		settings.velocity = Vector2f(0.f, 100.f);
		settings.spriteScale = Vector2f(1.f, 1.f);
		settings.sound = PICKUP_1;
		break;
	case FIRERATE_PWU:
		settings.damage = 0;
		settings.damageUpgradeCount = 0;
		settings.hp = 1;
		settings.lifetime = 100.f;
		settings.scene = scene;
		settings.angle = 0.f;
		settings.category = POWERUP;
		settings.direction = -1.f;
		settings.velocity = Vector2f(0.f, 100.f);
		settings.spriteScale = Vector2f(1.f, 1.f);
		settings.sound = PICKUP_2;
		break;
	case PLAYER_MOVEMENT_PWU:
		settings.damage = 0;
		settings.damageUpgradeCount = 0;
		settings.hp = 1;
		settings.lifetime = 100.f;
		settings.scene = scene;
		settings.angle = 0.f;
		settings.category = POWERUP;
		settings.direction = -1.f;
		settings.velocity = Vector2f(0.f, 100.f);
		settings.spriteScale = Vector2f(1.f, 1.f);
		settings.sound = PICKUP_2;
		break;
	case BULLET_NUM_PWU:
		settings.damage = 0;
		settings.damageUpgradeCount = 0;
		settings.hp = 1;
		settings.lifetime = 100.f;
		settings.scene = scene;
		settings.angle = 0.f;
		settings.category = POWERUP;
		settings.direction = -1.f;
		settings.velocity = Vector2f(0.f, 100.f);
		settings.spriteScale = Vector2f(1.f, 1.f);
		settings.sound = PICKUP_3;
		break;
	case COIN_PWU:
		settings.damage = 0;
		settings.damageUpgradeCount = 0;
		settings.hp = 1;
		settings.lifetime = 100.f;
		settings.scene = scene;
		settings.angle = 0.f;
		settings.category = POWERUP;
		settings.direction = -1.f;
		settings.velocity = Vector2f(0.f, 100.f);
		settings.spriteScale = Vector2f(1.f, 1.f);
		settings.sound = PICKUP_4;
		break;
	default:
		break;
	}
	return settings;
}
