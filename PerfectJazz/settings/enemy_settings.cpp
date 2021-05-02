#include "enemy_settings.h"
#include "../game.h"
#include <engine.h>
enemySettings EnemySettings::LoadSettings(_enemyType type, Scene* scene) {

	enemySettings settings;

	switch (type) {
	case AIRMAN:
	{
		settings.damage = 300;
		settings.hp = 1000;
		settings.scene = scene;
		settings.restitution = 0.4f;
		settings.friction = 0.005f;
		settings.velocity = { 0.f,-20.f };
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
		settings.damage = 500;
		settings.hp = 2500;
		settings.scene = scene;
		settings.restitution = 0.4f;
		settings.friction = 0.005f;
		settings.velocity = { 0.f,-20.f };
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
		settings.damage = 700;
		settings.hp = 3500;
		settings.scene = scene;
		settings.restitution = 0.4f;
		settings.friction = 0.005f;
		settings.velocity = { 0.f,-20.f };
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
		settings.damage = 500;
		settings.hp = 500;
		settings.scene = scene;
		settings.restitution = 0.4f;
		settings.friction = 0.005f;
		settings.velocity = { 0.f,-150.f };
		settings.tile = ls::KAMIKAZE;
		settings.category = KAMIKAZE;
		settings.type = BANSAI;
		settings.hpVisible = true;
		settings.scale = { 1.f,1.f };
		settings.angle = 0;
		settings.sound = EXPLOSION_5;
		break;
	}
	case MADMAN:
	{
		settings.damage = 300;
		settings.hp = 2500;
		settings.scene = scene;
		settings.restitution = 0.4f;
		settings.friction = 0.005f;
		settings.velocity = { 0.f,-300.f };
		settings.tile = ls::BESERKER;
		settings.category = ENEMY_BODY;
		settings.type = MADMAN;
		settings.hpVisible = true;
		settings.scale = { 1.f,1.f };
		settings.angle = 0;
		settings.sound = EXPLOSION_3;
		break;
	}
	case BOSS:
	{
		settings.damage = 5000;
		settings.hp = 25000;
		settings.scene = scene;
		settings.restitution = 0.4f;
		settings.friction = 0.005f;
		settings.velocity = { 0.f,-30.f };
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
	return settings;
}