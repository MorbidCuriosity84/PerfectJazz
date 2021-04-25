#include "player_settings.h"
#include "../game.h"
#include "../engine/engine.h"


playerSettings PlayerSettings::LoadSettings(_playerType type, Scene* scene) {
	playerSettings currentPlayerSettings;

	switch (type) {
	case PLAYER1:
	{
		currentPlayerSettings.damage = 10000;
		currentPlayerSettings.hp = 100000;
		currentPlayerSettings.lifes = 5;
		currentPlayerSettings.maxLifes = 5;
		currentPlayerSettings.maxHP = 400000;
		currentPlayerSettings.scene = scene;
		currentPlayerSettings.restitution = 0.4f;
		currentPlayerSettings.friction = 0.005f;
		currentPlayerSettings.flySpeed = 30.f;
		currentPlayerSettings.flySpeedUpgradeCount = 0;
		currentPlayerSettings.category = PLAYER_BODY;
		currentPlayerSettings.hpVisible = false;
		currentPlayerSettings.scale = { 1.f,1.f };
		currentPlayerSettings.angle = 0;
		currentPlayerSettings.score = 0;
		currentPlayerSettings.shopPoints = 0;
		break;
	}

	case PLAYER2:
	{
		break;
	}
	default:
		break;
	}
	return currentPlayerSettings;
}

