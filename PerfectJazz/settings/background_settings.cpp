#include "background_settings.h"

//Loads settings for the different backgrounds types
backgroundSettings BackgroundSettings::LoadSettings(_backgroundType type, Scene* scene) {	
	//Creates a reference to the struct backgroundSettings
	backgroundSettings settings;

	switch (type) {
	//Type of background mountain
	case MOUNTAIN:
	{
		settings.scene = scene;													 // Sets the scene
		settings.direction = -1.f;												 // Sets the direction of the movement
		settings.velocity = Vector2f(0.f / windowScale.x, 50.f * windowScale.y); // Sets the velocity of the sprite
		settings.angle = 0;														 // Sets the angle
		settings.opacity = { 255, 255, 255, 255 };								 // Sets the opacity of the sprite
		settings.spriteScale = Vector2f(1.f, 1.f);								 // Sets the scale of the sprite
		break;
	}
	//Type of background mountain over
	case MOUNTAIN_OVER:
	{
		settings.scene = scene;
		settings.direction = -1.f;
		settings.velocity = Vector2f(0.f / windowScale.x, 10.f / windowScale.y);
		settings.angle = 0;
		settings.opacity = { 255, 255, 255, 255 };
		settings.offset = { 0.f, mainView.getSize().y };
		settings.spriteScale = Vector2f(1.f, 1.f);

		break;
	}
	//Type of background forest
	case FOREST:
	{
		settings.scene = scene;
		settings.direction = -1.f;
		settings.velocity = Vector2f(0.f / windowScale.x, 50.f * windowScale.y);
		settings.angle = 0;
		settings.opacity = { 255, 255, 255, 255 };
		settings.spriteScale = Vector2f(1.f, 1.f);
		break;
	}
	//Type of background forest over
	case FOREST_OVER:
	{
		settings.scene = scene;
		settings.direction = -1.f;
		settings.velocity = Vector2f(0.f / windowScale.x, 10.f / windowScale.y);
		settings.angle = 0;
		settings.opacity = { 255, 255, 255, 255 };
		settings.spriteScale = Vector2f(1.f, 1.f);
		break;
	}
	default:
		break;
	}
	return settings;
}
