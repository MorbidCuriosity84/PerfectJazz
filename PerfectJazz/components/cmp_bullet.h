#pragma once
#include "cmp_physics.h"
#include "cmp_damage.h"
#include "../settings/bullet_settings.h"
#include "../game.h"
#include <ecm.h>

class BulletComponent : public Component {
protected:
	shared_ptr<SpriteComponent> _bulletSprite;
	textureSettings _bulletTextHelper;
	bulletSettings _settings;
public:
	void update(double dt) override;
	void render() override {}
	void createBullet();

	explicit BulletComponent(Entity* p, bulletSettings settings, textureSettings bulletTexHelper);
	BulletComponent() = delete;
};


