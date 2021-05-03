#include "background_settings.h"

backgroundSettings BackgroundSettings::LoadSettings(_backgroundType type, Scene* scene) {

	backgroundSettings settings;

	switch (type) {
	case MOUNTAIN:
	{
		settings.scene = scene;
		settings.direction = -1.f;
		settings.velocity = Vector2f(0.f / windowScale.x, 50.f * windowScale.y);
		settings.angle = 0;
		settings.opacity = { 255, 255, 255, 255 };
		settings.spriteScale = Vector2f(1.f, 1.f);
		break;
	}

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
