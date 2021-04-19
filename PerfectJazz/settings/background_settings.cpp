#include "background_settings.h"

backgroundSettings BackgroundSettings::LoadSettings(_backgroundType type, Scene* scene) {

	backgroundSettings settings;

	switch (type) {
	case MOUNTAIN:
	{
		settings.scene = scene;
		settings.direction = -1.f;
		settings.velocity = Vector2f(0.f, 100.f);
		settings.spriteScale = Vector2f(1.f, 1.f);
		settings.angle = 0;
		settings.opacity = { 255, 255, 255, 255 };
		break;
	}

	case MOUNTAIN_OVER:
	{
		settings.scene = scene;
		settings.direction = -1.f;
		settings.velocity = Vector2f(0.f, 10.f);
		settings.spriteScale = Vector2f(1.f, 1.f);
		settings.angle = 0;
		settings.opacity = { 255, 255, 255, 255 };
		settings.offset = { 0.f, mainView.getSize().y };

		break;
	}

	case FOREST:
	{
		settings.scene = scene;
		settings.direction = -1.f;
		settings.velocity = Vector2f(0.f, 100.f);
		settings.spriteScale = Vector2f(1.f, 1.f);
		settings.angle = 0;
		settings.opacity = { 255, 255, 255, 255 };
		break;
	}
	case FOREST_OVER:
	{
		settings.scene = scene;
		settings.direction = -1.f;
		settings.velocity = Vector2f(0.f, 100.f);
		settings.spriteScale = Vector2f(1.f, 1.f);
		settings.angle = 0;
		settings.opacity = { 255, 255, 255, 255 };
		break;
	}
	default:
		break;
	}
	return settings;
}
