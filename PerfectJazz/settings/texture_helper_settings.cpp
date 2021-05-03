#include "texture_helper_settings.h"
#include "../game.h"
#include "engine.h"

//Loads settings for the player that will help to load the sprite
textureSettings TextureHelpingSettings::LoadSettings(_playerType type, Scene* scene) {

	//Creates a reference to the struct textureSettings
	textureSettings settings;
	//Creates a pointer to  sf::Texture and sf::IntRect
	auto playerSpriteTexture = make_shared<sf::Texture>();
	auto playerSpriteRectangle = make_shared<sf::IntRect>();

	//Switches between different settings for different cases of weapon types
	switch (type) {
	case PLAYER1:
	{
		settings.spriteFilename = "res/img/player/player_900.png"; // Loads the sprite for the texture
		settings.spriteRows = 2;								   // Sets the number of rows for the sprite sheet
		settings.spriteCols = 5;								   // Sets the number of columns for the sprite sheet
		settings.desiredRow = 0;								   // Sets the desired row from the sprite sheet
		settings.desiredCol = 2;								   // Sets the desired column from the sprite sheet
		settings.spriteTexture = playerSpriteTexture;			   // Sets the Texture pointer to the current setting
		settings.spriteRectangle = playerSpriteRectangle;		   // Sets the IntRect pointer to the current setting
		settings.spriteTimer = 0;								   // Sets the timer to 0
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
	return settings;
}
//Loads settings for the different types of enemies that will help to load the sprite
textureSettings TextureHelpingSettings::LoadSettings(_enemyType type, Scene* scene) {

	textureSettings settings;
	auto enemySpriteTexture = make_shared<sf::Texture>();
	auto enemySpriteRectangle = make_shared<sf::IntRect>();
	switch (type) {
	case AIRMAN:
	{
		settings.spriteFilename = "res/img/enemies/enemy1_900.png";
		settings.spriteRows = 1;
		settings.spriteCols = 2;
		settings.desiredRow = 0; 
		settings.desiredCol = 0;
		settings.spriteTexture = enemySpriteTexture;
		settings.spriteRectangle = enemySpriteRectangle;
		settings.spriteTimer = 0;
		break;
	}

	case SERGEANT:
	{
		settings.spriteFilename = "res/img/enemies/enemy2_900.png";
		settings.spriteRows = 1;
		settings.spriteCols = 2;
		settings.desiredRow = 0;
		settings.desiredCol = 0;
		settings.spriteTexture = enemySpriteTexture;
		settings.spriteRectangle = enemySpriteRectangle;
		settings.spriteTimer = 0;
		break;
	}
	case COLONEL:
	{
		settings.spriteFilename = "res/img/enemies/enemy3_900.png";
		settings.spriteRows = 1;
		settings.spriteCols = 2;
		settings.desiredRow = 0;
		settings.desiredCol = 0;
		settings.spriteTexture = enemySpriteTexture;
		settings.spriteRectangle = enemySpriteRectangle;
		settings.spriteTimer = 0;
		break;
	}
	case BANSAI:
	{
		settings.spriteFilename = "res/img/enemies/kamikaze1.png";
		settings.spriteRows = 1;
		settings.spriteCols = 1;
		settings.desiredRow = 0;   
		settings.desiredCol = 0;
		settings.spriteTexture = enemySpriteTexture;
		settings.spriteRectangle = enemySpriteRectangle;
		settings.spriteTimer = 0;
		break;
	}
	case MADMAN:
	{
		settings.spriteFilename = "res/img/enemies/madman1.png";
		settings.spriteRows = 1;
		settings.spriteCols = 1;
		settings.desiredRow = 0;
		settings.desiredCol = 0;
		settings.spriteTexture = enemySpriteTexture;
		settings.spriteRectangle = enemySpriteRectangle;
		settings.spriteTimer = 0;
		break;
	}
	case BOSS:
	{
		settings.spriteFilename = "res/img/enemies/boss1.png";
		settings.spriteRows = 1;
		settings.spriteCols = 1;
		settings.desiredRow = 0;
		settings.desiredCol = 0;
		settings.spriteTexture = enemySpriteTexture;
		settings.spriteRectangle = enemySpriteRectangle;
		settings.spriteTimer = 0;
		break;
	}
	default:
		break;
	}
	return settings;
}
//Loads settings for the different types of bullets that will help to load the sprite
textureSettings TextureHelpingSettings::LoadSettings(_bulletType type, Scene* scene) {

	textureSettings settings;
	auto bulletSpriteTexture = make_shared<sf::Texture>();
	auto bulletSpriteRectangle = make_shared<sf::IntRect>();
	switch (type) {
	case TYPE1:
	{
		settings.spriteFilename = "res/img/weapons/Fx_01.png";
		settings.spriteRows = 1;
		settings.spriteCols = 3;
		settings.desiredRow = 0;
		settings.desiredCol = 2;
		settings.spriteTexture = bulletSpriteTexture;
		settings.spriteRectangle = bulletSpriteRectangle;
		settings.spriteTimer = 0;
		break;
	}

	case TYPE2:
	{
		settings.spriteFilename = "res/img/weapons/Fx_02.png";
		settings.spriteRows = 1;
		settings.spriteCols = 3;
		settings.desiredRow = 0;
		settings.desiredCol = 2;
		settings.spriteTexture = bulletSpriteTexture;
		settings.spriteRectangle = bulletSpriteRectangle;
		settings.spriteTimer = 0;
		break;
	}
	case TYPE3:
	{
		settings.spriteFilename = "res/img/weapons/Fx_02.png";
		settings.spriteRows = 1;
		settings.spriteCols = 3;
		settings.desiredRow = 0;
		settings.desiredCol = 2;
		settings.spriteTexture = bulletSpriteTexture;
		settings.spriteRectangle = bulletSpriteRectangle;
		settings.spriteTimer = 0;
		break;
	}
	case TYPE_PLAYER:
	{
		settings.spriteFilename = "res/img/weapons/Fx_01.png";
		settings.spriteRows = 1;
		settings.spriteCols = 3;
		settings.desiredRow = 0;
		settings.desiredCol = 2;
		settings.spriteTexture = bulletSpriteTexture;
		settings.spriteRectangle = bulletSpriteRectangle;
		settings.spriteTimer = 0;
		break;
	}
	default:
		break;
	}
	return settings;
}
//Loads settings for the different types of backgrounds that will help to load the sprite
textureSettings TextureHelpingSettings::LoadSettings(_backgroundType type, Scene* scene) {
	textureSettings settings;
	auto backgroundSpriteTexture = make_shared<sf::Texture>();
	auto backgroundSpriteRectangle = make_shared<sf::IntRect>();
	switch (type) {
	case MOUNTAIN:
	{
		settings.spriteFilename = "res/img/backgrounds/desert_900.png";
		settings.spriteRows = 1;
		settings.spriteCols = 1;
		settings.desiredRow = 0;
		settings.desiredCol = 0;
		settings.spriteTexture = backgroundSpriteTexture;
		settings.spriteRectangle = backgroundSpriteRectangle;
		settings.spriteTimer = 0;
		break;
	}
	case MOUNTAIN_OVER:
	{
		settings.spriteFilename = "res/img/backgrounds/desert_clouds.png";
		settings.spriteRows = 1;
		settings.spriteCols = 1;
		settings.desiredRow = 0;
		settings.desiredCol = 0;
		settings.spriteTexture = backgroundSpriteTexture;
		settings.spriteRectangle = backgroundSpriteRectangle;
		settings.spriteTimer = 0;
		break;
	}

	case FOREST:
	{
		settings.spriteFilename = "res/img/backgrounds/forest.png";
		settings.spriteRows = 1;
		settings.spriteCols = 1;
		settings.desiredRow = 0;
		settings.desiredCol = 0;
		settings.spriteTexture = backgroundSpriteTexture;
		settings.spriteRectangle = backgroundSpriteRectangle;
		settings.spriteTimer = 0;
		break;
	}
	case FOREST_OVER:
	{
		settings.spriteFilename = "res/img/backgrounds/desert_clouds.png";
		settings.spriteRows = 1;
		settings.spriteCols = 1;
		settings.desiredRow = 0;
		settings.desiredCol = 0;
		settings.spriteTexture = backgroundSpriteTexture;
		settings.spriteRectangle = backgroundSpriteRectangle;
		settings.spriteTimer = 0;
		break;
	}
	default:
		break;
	}
	return settings;
}
//Loads settings for the different types of powerups that will help to load the sprite
textureSettings TextureHelpingSettings::LoadSettings(_powerUpsType type, Scene* scene) {

	textureSettings settings;
	auto powerupSpriteTexture = make_shared<sf::Texture>();
	auto powerupSpriteRectangle = make_shared<sf::IntRect>();

	settings.spriteRows = 1;
	settings.spriteCols = 1;
	settings.desiredRow = 0;
	settings.desiredCol = 0;
	settings.spriteTexture = powerupSpriteTexture;
	settings.spriteRectangle = powerupSpriteRectangle;
	settings.spriteTimer = 0;

	switch (type) {
	case HP_PWU:
	{
		settings.spriteFilename = "res/img/powerups/potion.png";
		break;
	}

	case DAMAGE_PWU:
	{
		settings.spriteFilename = "res/img/powerups/power.png";
		break;
	}
	case BULLET_NUM_PWU:
	{
		settings.spriteFilename = "res/img/powerups/multi.png";
		break;
	}
	case FIRERATE_PWU:
	{
		settings.spriteFilename = "res/img/powerups/speed.png";

		break;
	}
	case PLAYER_MOVEMENT_PWU:
	{
		settings.spriteFilename = "res/img/powerups/player_speed.png";
		break;
	}
	case COIN_PWU:
	{
		settings.spriteFilename = "res/img/powerups/coins.png";
		settings.spriteRows = 1;
		settings.spriteCols = 5;
		break;
	}
	default:
		break;
	}
	return settings;
}