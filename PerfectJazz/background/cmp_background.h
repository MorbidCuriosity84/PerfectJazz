#pragma once
#pragma once
#include <ecm.h>
#include <SFML/Graphics.hpp>
#include "../components/cmp_sprite.h"
#include "../components/cmp_weapon.h"
#include "../components/cmp_bullet.h"
#include "../game.h"
#include "../settings/player_settings.h"
#include "../settings/background_settings.h"
using namespace sf;

//Background component that helps to set the sprites and infinite background effect
class BackgroundComponent : public Component {
protected:
	textureSettings _backgroundTextureHelper;
	textureSettings _overlayTextureHelper;
	backgroundSettings _backgroundSettings;
	std::shared_ptr<SpriteComponent> spriteCMP;

public:
	void Load(bool second);
	void render() override {};
	void update(double dt);

	BackgroundComponent() = delete;
	explicit BackgroundComponent(Entity* p, textureSettings backgroundTextureHelper, backgroundSettings backgroundSettings);
};