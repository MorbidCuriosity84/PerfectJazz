#include "create_background.h"
#include "../game.h"
#include "../components/cmp_background_physics.h"
#include "cmp_background.h"


textureSettings _backgroundTextureHelper;
backgroundSettings _backgroundSettings;
textureSettings _backgroundTextureHelper2;
backgroundSettings _backgroundSettings2;

void Background::createBackground(Scene* _scene) {

	//Load infinite background
	{
		for (int i = 0; i < 2; i++) {
			bool repeated = false;
			auto background = _scene->makeEntity();
			background->setView(mainView);
			_backgroundTextureHelper = TextureHelpingSettings::LoadSettings(MOUNTAIN, _scene);
			_backgroundSettings = BackgroundSettings::LoadSettings(MOUNTAIN, _scene);
			auto loadBackground = background->addComponent<BackgroundComponent>(_backgroundTextureHelper, _backgroundSettings);

			if (i == 1) { repeated = true; };
			loadBackground->Load(repeated);
		}

	}

	//CARLOS NEED TO FIX THIS
	//Load over background sprites
	{
		auto background = _scene->makeEntity();
		background->setView(mainView);
		_backgroundTextureHelper = TextureHelpingSettings::LoadSettings(MOUNTAIN_OVER2, _scene);
		_backgroundSettings = BackgroundSettings::LoadSettings(MOUNTAIN_OVER2, _scene);
		auto loadBackground = background->addComponent<BackgroundComponent>(_backgroundTextureHelper, _backgroundSettings);
		loadBackground->Load(false);

		auto background2 = _scene->makeEntity();
		background2->setView(mainView);
		_backgroundTextureHelper = TextureHelpingSettings::LoadSettings(MOUNTAIN_OVER1, _scene);
		_backgroundSettings = BackgroundSettings::LoadSettings(MOUNTAIN_OVER1, _scene);
		auto loadBackground2 = background2->addComponent<BackgroundComponent>(_backgroundTextureHelper, _backgroundSettings);
		loadBackground2->Load(true);


	}
}
