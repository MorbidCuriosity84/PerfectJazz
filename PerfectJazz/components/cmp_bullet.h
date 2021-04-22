#pragma once
#include "cmp_physics.h"
#include "cmp_damage.h"
#include "../settings/bullet_settings.h"
#include "../game.h"
#include <ecm.h>
#include "../settings/collision_helper.h"

class BulletComponent : public Component {
protected:
	shared_ptr<SpriteComponent> _bulletSprite;
	textureSettings _bulletTextHelper;
	bulletSettings _settings;
	collisionHelper bul_colHelp;
public:
	void update(double dt) override;
	void render() override {}
	void createBullet();

	std::shared_ptr<SpriteComponent> spriteCMP;
	std::shared_ptr<DamageComponent> damageCMP;
	std::shared_ptr<HPComponent> hpCMP;
	std::shared_ptr<PhysicsComponent> physicsCMP;	

	explicit BulletComponent(Entity* p, bulletSettings settings, textureSettings bulletTexHelper);
	BulletComponent() = delete;
};

