#include "background_settings.h"

backgroundSettings BackgroundSettings::LoadSettings(_backgroundType type, Scene* scene) {

	backgroundSettings settings;

	switch (type) {
	case MOUNTAIN:
	{
		settings.scene = scene;
		settings.direction = -1.f;
		settings.velocity = Vector2f(0.f, 200.f);
		settings.spriteScale = Vector2f(1.f, 1.f);
		settings.angle = 0;
		break;
	}

	case MOUNTAIN_OVER1:
	{
		settings.scene = scene;
		settings.direction = -1.f;
		settings.velocity = Vector2f(0.f, 10.f);
		settings.spriteScale = Vector2f(1.f, 1.f);
		settings.angle = 0;
		break;
	}
	case MOUNTAIN_OVER2:
	{
		settings.scene = scene;
		settings.direction = -1.f;
		settings.velocity = Vector2f(0.f, 30.f);
		settings.spriteScale = Vector2f(1.f, 1.f);
		settings.angle = 0;
		break;
	}
	case FOREST:
	{
		settings.scene = scene;
		settings.direction = -1.f;
		settings.velocity = Vector2f(0.f, 100.f);
		settings.spriteScale = Vector2f(1.f, 1.f);
		settings.angle = 0;
		break;
	}
	case FOREST_OVER:
	{
		settings.scene = scene;
		settings.direction = -1.f;
		settings.velocity = Vector2f(0.f, 100.f);
		settings.spriteScale = Vector2f(1.f, 1.f);
		settings.angle = 0;
		break;
	}
	default:
		break;
	}
	return settings;
}
