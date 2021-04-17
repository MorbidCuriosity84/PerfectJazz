#include "player_settings.h"
#include "../game.h"
#include "../engine/engine.h"

playerSettings PlayerSettings::LoadSettings(_playerType type, Scene* scene) {

	playerSettings settings;

	switch (type) {
	case PLAYER1:
	{
		settings.damage = 100;
		settings.hp = 99999;
		settings.scene = scene;
		settings.restitution = 0.4f;
		settings.friction = 0.005f;
		settings.velocity = { 0.f,100.f };
		settings.category = PLAYER_BODY;
		settings.hpVisible = true;
		settings.scale = { 1.f,1.f };
		settings.angle = 0;
		break;
	}

	case PLAYER2:
	{
		break;
	}
	default:
		break;
	}
	return settings;
}
