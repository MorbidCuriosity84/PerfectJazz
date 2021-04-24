#pragma once

#include <ecm.h>
#include <list>
#include <random>
#include <map>
#include "../settings/texture_helper_settings.h"
#include "../components/cmp_sprite.h"
#include "../components/cmp_damage.h"
#include "../components/cmp_hp.h"
#include "../components/cmp_powerup_physics.h"
#include "../settings/collision_helper.h"


using namespace sf;
using namespace std;

class PowerupComponent : public Component{
protected:
	textureSettings _powerupTextureHelper;
	collisionHelper pow_colHelp;
	Scene* _scene;

public:
	void render() override {}
	void update(double dt) override;
	void deployPowerup();
	std::shared_ptr<SpriteComponent> powerupSpriteCMP;
	std::shared_ptr<DamageComponent> damageCMP;
	std::shared_ptr<HPComponent> hpCMP;
	std::shared_ptr<PowerupPhysicsComponent> physicsCMP;

	PowerupComponent() = delete;
	explicit PowerupComponent(Entity* p, textureSettings powerupTextureHelper, Scene* scene);
};

