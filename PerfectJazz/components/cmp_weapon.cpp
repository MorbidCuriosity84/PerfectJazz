#include "cmp_weapon.h"
#include "cmp_bullet.h"
#include "../pools/entityPool.h"
#include "../game.h"


void WeaponComponent::fire() {
	//auto bullet = _wSettings.scene->makeEntity();
	auto pS = _parent->GetCompatibleComponent<SpriteComponent>();
	auto bullet = EntityPool::pool[EntityPool::poolPointer++];
	bullet->clearComponents();
	bullet->setView(_parent->getView());
	bullet->setPosition({ _parent->getPosition().x, _parent->getPosition().y + (pS[0]->getSprite().getTextureRect().height/2 * _wSettings.direction) });
	bullet->setRotation(_parent->getRotation());
	bullet->addTag("Bullet");
	auto bul = bullet->addComponent<BulletComponent>(_bSettings, _bulletTextureHelper);	
	bullet->setView(_parent->getView());
	bullet->setAlive(true);
	bullet->setVisible(true);
	sounds[bul->bulletImpactSound].play();	
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