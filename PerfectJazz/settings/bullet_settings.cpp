#include "bullet_settings.h"

//Loads values for the bullets settings that will help to load the sprite
bulletSettings BulletSettings::LoadSettings(_bulletType type, Scene* scene) {

	bulletSettings settings;	

	//Switches between different settigns for different bullets
	switch (type) {
	case TYPE1:
	{
		settings.damage = 100;						   // Sets the current damage
		settings.damageUpgradeCount = 0;			   // Sets the current upgrade count for the damage
		settings.hp = 100;							   // Sets the current hp
		settings.lifetime = 10.f;					   // Sets the entities lifetime
		settings.scene = scene;						   // Sets the scene
		settings.angle = 90.f;						   // Sets the angle
		settings.category = ENEMY_BULLET;			   // Sets the category for collision
		settings.direction = -1.f;					   // Sets the direction of the movement
		settings.velocity = Vector2f(0.f, 300.f);	   // Sets the bullets movement speed
		settings.spriteScale = Vector2f(1.25f, 1.25f); // Sets the sprites scale	
		settings.sound = EXPLOSION_1;				   // Sets the bullet sound
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
		settings.spriteScale = Vector2f(1.5f, 1.5f);
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
		settings.velocity = Vector2f(0.f, 200.f);
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
		return settings;		
	}
	default:
		break;
	}
	scale(2, settings);
	return settings;
}

void BulletSettings::scale(int factor, bulletSettings& settings)
{
	if (Engine::currentPlayerLevel - 1 > 0) {
		settings.damage *= Engine::currentPlayerLevel * factor;		
	}
}
