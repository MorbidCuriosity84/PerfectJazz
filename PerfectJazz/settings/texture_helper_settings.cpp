#include "texture_helper_settings.h"
#include "../game.h"
#include "../engine/engine.h"


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
		settings.spriteTimer = 1.5;
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
		settings.spriteTimer = 1.5;
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
		settings.spriteTimer = 1.5;
		break;
	}
	default:
		break;
	}
	return settings;
}

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
		settings.spriteTimer = 2.0;
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
		settings.spriteTimer = 2.0;
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
		settings.spriteTimer = 2.0;
		break;
	}
	default:
		break;
	}
	return settings;
}
