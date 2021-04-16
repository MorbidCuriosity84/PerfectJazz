#include "cmp_weapon.h"
#include "cmp_bullet.h"


void WeaponComponent::fire() {
	auto bullet = _wSettings.scene->makeEntity();
	auto pS = _parent->GetCompatibleComponent<SpriteComponent>();
	bullet->setView(_parent->getView());
	bullet->setPosition({ _parent->getPosition().x, _parent->getPosition().y + (pS[0]->getSprite().getTextureRect().height/2 * _wSettings.direction) });

	auto wepSpriteTexture = make_shared<sf::Texture>();
	auto wepSpriteRectangle = make_shared<sf::IntRect>();
	textureHelper spriteHelp("res/img/weapons/Fx_01.png", 1, 3, 0, 2, wepSpriteTexture, wepSpriteRectangle, 2.0);

	bullet->addComponent<BulletComponent>(_bSettings, spriteHelp);
}

void WeaponComponent::update(double dt) {
	_wSettings.fireTime -= dt;
	if (_wSettings.fireTime <= 0.f) {
		fire();
		_wSettings.fireTime = _wSettings.fireTimer;
	}
}


void WeaponComponent::setDamage(uint16_t damage) {
	_wSettings.damage = damage;
}

uint16_t WeaponComponent::getDamage() const {
	return _wSettings.damage;
}
WeaponComponent::WeaponComponent(Entity* p, wepSettings wSettings, bulletSettings bSettings)
	: Component(p), _wSettings(wSettings), _bSettings(bSettings) {}