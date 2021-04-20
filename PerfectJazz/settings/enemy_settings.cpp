#include "enemy_settings.h"
#include "../game.h"
#include "../engine/engine.h"

enemySettings EnemySettings::LoadSettings(_enemyType type, Scene* scene) {
	
	enemySettings settings;

	switch (type) {
	case AIRMAN:
	{
		settings.damage = 100;
		settings.hp = 1000;
		settings.scene = scene;
		settings.restitution = 0.4f;
		settings.friction = 0.005f;
		settings.velocity = { 0.f,-300.f };
		settings.tile = ls::AIRMAN;
		settings.category = ENEMY_BODY;
		settings.hpVisible = true;
		settings.scale = { 1.f,1.f };
		settings.angle = 0;
		break;
	}

	case SERGEANT:
	{
		settings.damage = 200;
		settings.hp = 2500;
		settings.scene = scene;
		settings.restitution = 0.4f;
		settings.friction = 0.005f;
		settings.velocity = { 0.f,-300.f };
		settings.tile = ls::SERGEANT;
		settings.category = ENEMY_BODY;
		settings.hpVisible = true;
		settings.scale = { 1.f,1.f };
		settings.angle = 0;		
		break;
	}
	case COLONEL:
	{
		settings.damage = 300;
		settings.hp = 3500;
		settings.scene = scene;
		settings.restitution = 0.4f;
		settings.friction = 0.005f;
		settings.velocity = { 0.f,-300.f };
		settings.tile = ls::COLONEL;
		settings.category = ENEMY_BODY;
		settings.hpVisible = true;
		settings.scale = { 1.f,1.f };
		settings.angle = 0;
		break;
	}
	default:
		break;
	}
	return settings;
}