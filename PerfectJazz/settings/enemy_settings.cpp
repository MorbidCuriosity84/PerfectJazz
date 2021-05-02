#include "enemy_settings.h"
#include "../game.h"
#include <engine.h>
enemySettings EnemySettings::LoadSettings(_enemyType type, Scene* scene) {
	
	enemySettings settings;

	switch (type) {
	case AIRMAN:
	{
		settings.damage = 1000;
		settings.hp = 1000;
		settings.scene = scene;
		settings.restitution = 0.4f;
		settings.friction = 0.005f;
		settings.velocity = { 0.f,-100.f };
		settings.tile = ls::AIRMAN;
		settings.category = ENEMY_BODY;
		settings.type = AIRMAN;
		settings.hpVisible = true;
		settings.scale = { 1.f,1.f };
		settings.angle = 0;		
		settings.sound = ENEMY_DIE_1;
		break;
	}

	case SERGEANT:
	{
		settings.damage = 2000;
		settings.hp = 2500;
		settings.scene = scene;
		settings.restitution = 0.4f;
		settings.friction = 0.005f;
		settings.velocity = { 0.f,-100.f };
		settings.tile = ls::SERGEANT;
		settings.category = ENEMY_BODY;
		settings.type = SERGEANT;
		settings.hpVisible = true;
		settings.scale = { 1.f,1.f };
		settings.angle = 0;				
		settings.sound = ENEMY_DIE_2;
		break;
	}
	case COLONEL:
	{
		settings.damage = 3000;
		settings.hp = 3500;
		settings.scene = scene;
		settings.restitution = 0.4f;
		settings.friction = 0.005f;
		settings.velocity = { 0.f,-100.f };
		settings.tile = ls::COLONEL;
		settings.category = ENEMY_BODY;
		settings.type = COLONEL;
		settings.hpVisible = true;
		settings.scale = { 1.f,1.f };
		settings.angle = 0;		
		settings.sound = ENEMY_DIE_3;
		break;
	}
	case BANSAI:
	{
		settings.damage = 1000;
		settings.hp = 500;
		settings.scene = scene;
		settings.restitution = 0.4f;
		settings.friction = 0.005f;
		settings.velocity = { 0.f,-350.f };
		settings.tile = ls::KAMIKAZE;
		settings.category = KAMIKAZE;
		settings.type = BANSAI;
		settings.hpVisible = true;
		settings.scale = { 1.f,1.f };
		settings.angle = 90.f;
		settings.sound = EXPLOSION_5;
		break;
	}
	case MADMAN:
	{
		settings.damage = 500;
		settings.hp = 2500;
		settings.scene = scene;
		settings.restitution = 0.4f;
		settings.friction = 0.005f;
		settings.velocity = { 0.f,-150.f };
		settings.tile = ls::BESERKER;
		settings.category = BESERKER;
		settings.type = MADMAN;
		settings.hpVisible = true;
		settings.scale = { 1.f,1.f };
		settings.angle = 90.f;
		settings.sound = EXPLOSION_3;
		break;
	}
	default:
		break;
	}
	return settings;
}
