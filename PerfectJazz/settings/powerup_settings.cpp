#include "powerup_settings.h"

//Loads settings for the different powerups
powerupSettings PowerupSettings::LoadSettings(_powerUpsType type, Scene* scene) {

	//Creates a reference to the struct powerupSettings
	powerupSettings settings;

	//Switches between different settings for different cases of powerups types
	switch (type) {
	case HP_PWU:
		settings.damage = 0;						// Sets the damage caused by the powerup
		settings.damageUpgradeCount = 0;			// Sets the current upgrade for damage
		settings.hp = 1;							// Sets the hp
		settings.lifetime = 100.f;					// Sets the lifetime
		settings.scene = scene;						// Sets the scene
		settings.angle = 0.f;						// Sets the angle
		settings.category = POWERUP;				// Sets the category
		settings.direction = -1.f;					// Sets the directionp
		settings.velocity = Vector2f(0.f, 100.f);	// Sets the velocity
		settings.spriteScale = Vector2f(0.8f, .8f);	// Sets the sprite scale
		settings.sound = PICKUP_1;					// Sets the current sound
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
		settings.spriteScale = Vector2f(0.8f, .8f);
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
		settings.spriteScale = Vector2f(0.8f, 0.8f);
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
		settings.spriteScale = Vector2f(0.8f, 0.8f);
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
		settings.spriteScale = Vector2f(0.8f, 0.8f);
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
		settings.spriteScale = Vector2f(0.8f, 0.8f);
		settings.sound = PICKUP_4;
		break;
	default:
		break;
	}
	return settings;
}

void PowerupSettings::scale(int factor, powerupSettings& settings)
{
	if (Engine::currentPlayerLevel > 0) {		
		settings.hp *= Engine::currentPlayerLevel * factor;
	}
}
