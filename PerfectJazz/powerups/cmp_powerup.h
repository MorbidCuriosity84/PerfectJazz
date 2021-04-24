#pragma once

#include <ecm.h>
#include <list>
#include <random>
#include <map>
#include "../settings/texture_helper_settings.h"
#include "../components/cmp_sprite.h"

using namespace sf;
using namespace std;

class PowerupComponent : public Component{
protected:
	textureSettings _powerupTextureHelper;
	std::shared_ptr<SpriteComponent> powerupSpriteCMP;
	string _type;

public:
	void render() override {};
	void update(double dt);
	void deployPowerup();

	PowerupComponent() = delete;
	explicit PowerupComponent(Entity* p, textureSettings powerupTextureHelper, string type);
};

