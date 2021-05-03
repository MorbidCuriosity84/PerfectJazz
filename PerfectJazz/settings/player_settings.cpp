#include "player_settings.h"
#include "../game.h"
#include "engine.h"

//Loads values for the player settings that will help to load the sprite
playerSettings PlayerSettings::LoadSettings(_playerType type, Scene* scene) {
	playerSettings currentPlayerSettings;
	//Switches between different settings for different players
	switch (type) {
	case PLAYER1:
	{
		currentPlayerSettings.damage = 100;            // Sets the current damage
		currentPlayerSettings.hp = 10000;			   // Sets the current hp
		currentPlayerSettings.lifes = 5;			   // Sets the number of lifes
		currentPlayerSettings.maxLifes = 5;			   // Sets the maximum number of lifes
		currentPlayerSettings.maxHP = 10000;		   // Sets the maximum hp value
		currentPlayerSettings.scene = scene;		   // Sets the scene
		currentPlayerSettings.restitution = 0.4f;	   // Sets the players restitution
		currentPlayerSettings.friction = 0.005f;	   // Sets the players friction
		currentPlayerSettings.flySpeed = 30.f;		   // Sets the player movement speed
		currentPlayerSettings.flySpeedUpgradeCount = 0;// Sets the player current upgrade for movement speed
		currentPlayerSettings.category = PLAYER_BODY;  // Sets the category for collisions
		currentPlayerSettings.hpVisible = false;	   // Sets whether the hp displaying the sprite is visible or not
		currentPlayerSettings.scale = { 1.f,1.f };	   // Sets the scale of the sprite
		currentPlayerSettings.angle = 0;			   // Sets the angle
		currentPlayerSettings.score = 0;			   // Sets the initial players score
		currentPlayerSettings.shopPoints = 0;		   // Sets the initial players coins
		currentPlayerSettings.currentLevel = 1;		   // Sets the current level
		break;
	}

	//Swtich case for a future second player
	case PLAYER2:
	{
		break;
	}
	default:
		break;
	}
	return currentPlayerSettings;
}
