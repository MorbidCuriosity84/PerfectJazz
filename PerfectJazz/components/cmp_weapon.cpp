#include "cmp_weapon.h"
#include "cmp_bullet.h"


void WeaponComponent::fire() {
	auto bullet = _wSettings.scene->makeEntity();
	auto pS = _parent->GetCompatibleComponent<SpriteComponent>();
	bullet->setView(_parent->getView());
	bullet->setPosition({ _parent->getPosition().x, _parent->getPosition().y + (pS[0]->getSprite().getTextureRect().height/2 * _wSettings.direction) });
	bullet->setRotation(_parent->getRotation());
	bullet->addTag("Bullet");
	auto wepSpriteTexture = make_shared<sf::Texture>();
	auto wepSpriteRectangle = make_shared<sf::IntRect>();
	bullet->addComponent<BulletComponent>(_bSettings, _bulletTextureHelper);
}

void WeaponComponent::update(double dt) {
	_wSettings.fireTimer -= dt;
	if (_wSettings.fireTimer <= 0.f) {
		fire();
		_wSettings.fireTimer = _wSettings.fireTime - (_wSettings.fireTime * 0.15 * _wSettings.firerateUpgradeCount);
	}
}

void WeaponComponent::setDamage(uint16_t damage) {
	_bSettings.damage = damage;
}

uint16_t WeaponComponent::getDamage() const {
	return _bSettings.damage;
}
WeaponComponent::WeaponComponent(Entity* p, weaponSettings wSettings, bulletSettings bSettings, textureSettings bTextureHelper)
	: Component(p), _wSettings(wSettings), _bSettings(bSettings), _bulletTextureHelper(bTextureHelper){ }