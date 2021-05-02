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
		settings.velocity = Vector2f(0.f, 300.f);
		settings.spriteScale = Vector2f(1.f, 1.f);
		settings.sound = EXPLOSION_1;
		break;
	}

	case TYPE2:
	{
		settings.damage = 250;
		settings.damageUpgradeCount = 0;
		settings.hp = 100;
		settings.lifetime = 10.f;
		settings.scene = scene;
		settings.angle = 90.f;
		settings.category = ENEMY_BULLET;
		settings.direction = -1.f;
		settings.velocity = Vector2f(0.f, 400.f);
		settings.spriteScale = Vector2f(1.f, 1.f);
		settings.sound = EXPLOSION_2;
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
		settings.velocity = Vector2f(0.f, 350);
		settings.spriteScale = Vector2f(3.f, 3.f);
		settings.sound = EXPLOSION_3;
		break;
	}
	case TYPE_PLAYER:
	{
		settings.damage = 300;
		settings.damageUpgradeCount = 0;
		settings.hp = 100;
		settings.lifetime = 10.f;
		settings.scene = scene;
		settings.angle = 90.f;
		settings.category = FRIENDLY_BULLET;
		settings.direction = 1.f;
		settings.velocity = Vector2f(0.f, 300.f);
		settings.spriteScale = Vector2f(1.f, 1.f);
		settings.sound = EXPLOSION_1;
		break;
	}
	default:
		break;
	}
	return settings;
}
