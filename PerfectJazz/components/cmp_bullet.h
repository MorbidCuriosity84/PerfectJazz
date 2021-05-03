#pragma once
#include "cmp_physics.h"
#include "cmp_damage.h"
#include "../settings/bullet_settings.h"
#include "../game.h"
#include <ecm.h>
#include "../settings/collision_helper.h"
#include "../components/cmp_sound.h"

//Bullet component that adds sprites, damage, physics and hp components to the entity
//It also helps to perform the animation for the sprites and checks whether the entity
//hp is over 0, and alive, or no.
class BulletComponent : public Component {
protected:
	textureSettings _bulletTextHelper;
	bulletSettings _settings;
	collisionHelper bul_colHelp;
	float accumulation;
public:
	void update(double dt) override;
	void render() override {}
	void createBullet();

	SOUNDS bulletImpactSound;
	std::shared_ptr<SpriteComponent> spriteCMP;
	std::shared_ptr<DamageComponent> damageCMP;
	std::shared_ptr<HPComponent> hpCMP;
	std::shared_ptr<PhysicsComponent> physicsCMP;	

	explicit BulletComponent(Entity* p, bulletSettings settings, textureSettings bulletTexHelper);
	BulletComponent() = delete;
};

