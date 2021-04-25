#pragma once

#include <ecm.h>
#include "../settings/bullet_settings.h"
#include "../game.h"
#include "../settings/collision_helper.h"
#include "../components/cmp_physics.h"
#include "../components/cmp_damage.h"
#include "../settings/powerup_settings.h"

class PowerupComponent : public Component{
protected:
	textureSettings _powerupTextureHelper;
	collisionHelper pow_colHelp;
	powerupSettings _powerupSettings;

public:
	void update(double dt) override;
	void powerupAction();
	void render() override {};
	void deployPowerup();

	std::shared_ptr<SpriteComponent> powerupSpriteCMP;
	std::shared_ptr<DamageComponent> damageCMP;
	std::shared_ptr<HPComponent> hpCMP;
	std::shared_ptr<PhysicsComponent> physicsCMP;

	explicit PowerupComponent(Entity* p, textureSettings powerupTextureHelper, powerupSettings powerupSettings);
	PowerupComponent() = delete;
};

