#include "cmp_weapon.h"
#include "cmp_bullet.h"


void WeaponComponent::fire() {
	auto bullet = _settings.scene->makeEntity();
	bullet->setView(_parent->getView());
	bullet->setPosition({ _parent->getPosition().x, _parent->getPosition().y / 2 });

	auto wepSpriteTexture = make_shared<sf::Texture>();
	auto wepSpriteRectangle = make_shared<sf::IntRect>();
	textureHelper spriteHelp("res/img/weapons/Fx_01.png", 1, 3, 0, 2, wepSpriteTexture, wepSpriteRectangle, 2.0);
	bulletSettings settings;
	settings.damage = 100;
	settings.hp = 100;
	settings.lifetime = 10.f;
	settings.scene = _settings.scene;
	settings.spriteAngle = 90.f;
	settings.category = ENEMY_BULLET;
	settings.velocity = Vector2f(0.f, -100.f);
	bullet->addComponent<BulletComponent>(settings, spriteHelp);
}

void WeaponComponent::update(double dt) {
	_settings.fireTime -= dt;
	if (_settings.fireTime <= 0.f) {
		fire();
		_settings.fireTime = _settings.fireTimer;
	}
}


void WeaponComponent::setDamage(uint16_t damage) {
	_settings.damage = damage;
}

uint16_t WeaponComponent::getDamage() const {
	return _settings.damage;
}
WeaponComponent::WeaponComponent(Entity* p, wepSettings settings)
	: Component(p), _settings(settings) {}