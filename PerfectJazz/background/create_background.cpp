#include "create_background.h"
#include "../game.h"
#include "../components/cmp_background_physics.h"
#include "cmp_background.h"

textureSettings _backgroundTextureHelper;
backgroundSettings _backgroundSettings;

//Creates the background entity for de scene, adding a background component and
//the settings for the type of background
void Background::createBackground(Scene* _scene) {

	//Load infinite background by adding two of the same sprites, one after the other
	{
		for (int i = 0; i < 2; i++) {
			auto background = _scene->makeEntity();
			background->setView(mainView);

			if (Engine::currentPlayerLevel == 0 || Engine::currentPlayerLevel == 2) {
				_backgroundTextureHelper = TextureHelpingSettings::LoadSettings(FOREST, _scene);
				_backgroundSettings = BackgroundSettings::LoadSettings(FOREST, _scene);
			}

			else {
				_backgroundTextureHelper = TextureHelpingSettings::LoadSettings(MOUNTAIN, _scene);
				_backgroundSettings = BackgroundSettings::LoadSettings(MOUNTAIN, _scene);
			}

			auto loadBackground = background->addComponent<BackgroundComponent>(_backgroundTextureHelper, _backgroundSettings);

			//Sets the flat repeat false for the first sprite, true for the second
			//so we can differenciate which sprite comes first, and which one comes after
			bool repeated = false;
			if (i == 1) { repeated = true; };
			loadBackground->Load(repeated);
		}
	}

	//Load the sprites that go over the background
	{
		for (int i = 0; i < 2; i++) {
			auto background = _scene->makeEntity();
			background->setView(mainView);
			_backgroundTextureHelper = TextureHelpingSettings::LoadSettings(MOUNTAIN_OVER, _scene);
			_backgroundSettings = BackgroundSettings::LoadSettings(MOUNTAIN_OVER, _scene);

			bool repeated = false;
			if (i == 1) {
				repeated = true;
				_backgroundSettings.spriteScale = { _backgroundSettings.spriteScale.x, _backgroundSettings.spriteScale.y * -1.f };
				_backgroundSettings.velocity = { 0, 80.f };
				_backgroundSettings.opacity = { 255, 255, 255, 120 };
			}
			auto loadBackground = background->addComponent<BackgroundComponent>(_backgroundTextureHelper, _backgroundSettings);

			loadBackground->Load(repeated);
		}
	}
}
