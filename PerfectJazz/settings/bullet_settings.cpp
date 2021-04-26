#include "bullet_settings.h"

bulletSettings BulletSettings::LoadSettings(_bulletType type, Scene* scene) {

	bulletSettings settings;

	switch (type) {
	case TYPE1:
	{
		settings.damage = 100;
		settings.damageUpgradeCount = 0;
		settings.hp = 100;
		settings.lifetime = 10.f;
		settings.scene = scene;
		settings.angle = 90.f;
		settings.category = ENEMY_BULLET;
		settings.direction = -1.f;
		settings.velocity = Vector2f(0.f, 100.f);
		settings.spriteScale = Vector2f(1.f, 1.f);
		settings.soundFile = "res/sounds/weapons/sfx_wpn_laser7.wav";
		break;
	}

	case TYPE2:
	{
		settings.damage = 100;
		settings.damageUpgradeCount = 0;
		settings.hp = 100;
		settings.lifetime = 10.f;
		settings.scene = scene;
		settings.angle = 90.f;
		settings.category = ENEMY_BULLET;
		settings.direction = -1.f;
		settings.velocity = Vector2f(0.f, 200.f);
		settings.spriteScale = Vector2f(1.f, 1.f);
		settings.soundFile = "res/sounds/weapons/sfx_wpn_laser9.wav";
		break;
	}
	case TYPE3:
	{
		settings.damage = 300;
		settings.damageUpgradeCount = 0;
		settings.hp = 100;
		settings.lifetime = 10.f;
		settings.scene = scene;
		settings.angle = 90.f;
		settings.category = ENEMY_MISSILE;
		settings.direction = -1.f;
		settings.velocity = Vector2f(0.f, 200.f);
		settings.spriteScale = Vector2f(3.f, 3.f);
		settings.soundFile = "res/sounds/weapons/sfx_wpn_laser11.wav";
		break;
	}
	default:
		break;
	}
	return settings;
}
