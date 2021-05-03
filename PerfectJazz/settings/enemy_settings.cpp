#include "enemy_settings.h"
#include "../game.h"
#include <engine.h>

//Loads settings for the different enemy types
enemySettings EnemySettings::LoadSettings(_enemyType type, Scene* scene) {
	//Creates a reference to the struct enemySettings
	enemySettings settings;		
	switch (type) {
	//Type of enemy Airman
	case AIRMAN:
	{
		settings.damage = 300;              // Sets the current damage
		settings.hp = 1000;					// Sets the current hp
		settings.scene = scene;				// Sets the scene
		settings.restitution = 0.4f;		// Sets the players restitution
		settings.friction = 0.005f;			// Sets the players friction
		settings.velocity = { 0.f,-0.1f };	// Sets the player movement speed
		settings.tile = ls::AIRMAN;			// Sets the type of enemy for the creation of the enemy
		settings.category = ENEMY_BODY;		// Sets the category for collisions
		settings.type = AIRMAN;				// Sets the type of enemy
		settings.hpVisible = true;			// Sets whether the hp displaying the sprite is visible or not
		settings.scale = { 1.f,1.f };		// Sets the scale of the sprite
		settings.angle = 0;					// Sets the angle
		settings.sound = ENEMY_DIE_1;		// Sets the enemies sound
		break;
	}
	//Type of enemy Sergeant
	case SERGEANT:
	{
		settings.damage = 500;
		settings.hp = 2500;
		settings.scene = scene;
		settings.restitution = 0.4f;
		settings.friction = 0.005f;
		settings.velocity = { 0.f,-15.f };
		settings.tile = ls::SERGEANT;
		settings.category = ENEMY_BODY;
		settings.type = SERGEANT;
		settings.hpVisible = true;
		settings.scale = { 1.f,1.f };
		settings.angle = 0;
		settings.sound = ENEMY_DIE_2;
		break;
	}
	//Type of enemy Colonel
	case COLONEL:
	{
		settings.damage = 700;
		settings.hp = 3500;
		settings.scene = scene;
		settings.restitution = 0.4f;
		settings.friction = 0.005f;
		settings.velocity = { 0.f,-15.f };
		settings.tile = ls::COLONEL;
		settings.category = ENEMY_BODY;
		settings.type = COLONEL;
		settings.hpVisible = true;
		settings.scale = { 1.f,1.f };
		settings.angle = 0;
		settings.sound = ENEMY_DIE_3;
		break;
	}
	//Type of enemy Bansai
	case BANSAI:
	{
		settings.damage = 500;
		settings.hp = 500;
		settings.scene = scene;
		settings.restitution = 0.4f;
		settings.friction = 0.005f;
		settings.velocity = { 0.f,-45.f };
		settings.tile = ls::KAMIKAZE;
		settings.category = KAMIKAZE;
		settings.type = BANSAI;
		settings.hpVisible = true;
		settings.scale = { 1.f,1.f };
		settings.angle = 0;
		settings.sound = EXPLOSION_5;
		break;
	}
	//Type of enemy Madman
	case MADMAN:
	{
		settings.damage = 300;
		settings.hp = 2500;
		settings.scene = scene;
		settings.restitution = 0.4f;
		settings.friction = 0.005f;
		settings.velocity = { 0.f,-15.f };
		settings.tile = ls::BESERKER;
		settings.category = ENEMY_BODY;
		settings.type = MADMAN;
		settings.hpVisible = true;
		settings.scale = { 1.f,1.f };
		settings.angle = 0;
		settings.sound = EXPLOSION_3;
		break;
	}
	//Type of enemy Boss
	case BOSS:
	{
		settings.damage = 5000;
		settings.hp = 25000;
		settings.scene = scene;
		settings.restitution = 0.4f;
		settings.friction = 0.005f;
		settings.velocity = { 0.f,-15.f };
		settings.tile = ls::BOSS;
		settings.category = ENEMY_BODY;
		settings.type = BOSS;
		settings.hpVisible = true;
		settings.scale = { 1.5f,1.5f };
		settings.angle = 0;
		settings.sound = EXPLOSION_3;		
		break;
	}
	default:
		break;
	}
	scale(5, settings);
	return settings;
}

void EnemySettings::scale(int factor, enemySettings& settings)
{
	if (Engine::currentPlayerLevel > 0) {
		settings.damage *= Engine::currentPlayerLevel * factor;
		settings.hp *= Engine::currentPlayerLevel * factor;
	}
}
