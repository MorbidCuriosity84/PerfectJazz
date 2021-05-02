#include <math.h>
#include "cmp_weapon.h"
#include "cmp_bullet.h"
#include "../pools/entityPool.h"
#include "../game.h"
#include "../services/sound_Queue.h"
#include "../lib_maths/maths.h"


void WeaponComponent::fire() {

	int odd = _wSettings.numBulletsUpgradeCount * 2 + 1;
	float deg = 30.f / (float)odd;
	float spread = 1.f;
	float angleStart = _parent->getRotation();
	if (_wSettings.numBulletsUpgradeCount + 1 > 1) {
		for (int i = 0 ; i < odd; i++) {			
			if (i % 2 != 0) {
				deg *= i;
			}			
			auto pS = _parent->GetCompatibleComponent<SpriteComponent>();
			shared_ptr<Entity> bullet = EntityPool::pool[EntityPool::poolPointer++];
			bullet->clearComponents();
			bullet->setView(_parent->getView());
			bullet->setPosition({ _parent->getPosition().x, _parent->getPosition().y + (pS[0]->getSprite().getTextureRect().height / 2 * _wSettings.direction) });
			bullet->setRotation(_parent->getRotation());
			bullet->addTag("Bullet");
			auto bul = bullet->addComponent<BulletComponent>(_bSettings, _bulletTextureHelper);
			float len = length(bul->physicsCMP->getVelocity());
			Vector2f direction = Vector2f(len * spread * cos(deg), bul->physicsCMP->getVelocity().y);				
			bul->physicsCMP->setVelocity(direction);
			bullet->setView(_parent->getView());
			bullet->setAlive(true);
			bullet->setVisible(true);
			spread *= -1.f;
		}
		sounds[_wSettings.sound].setPitch(1.f + sin(accumulation) * .025f);
		sounds[_wSettings.sound].setVolume(15.f);
		sounds[_wSettings.sound].play();
	}	

	auto pS = _parent->GetCompatibleComponent<SpriteComponent>();
	shared_ptr<Entity> bullet = EntityPool::pool[EntityPool::poolPointer++];
	bullet->clearComponents();
	bullet->setView(_parent->getView());
	bullet->setPosition({ _parent->getPosition().x, _parent->getPosition().y + (pS[0]->getSprite().getTextureRect().height/2 * _wSettings.direction) });
	bullet->setRotation(_parent->getRotation());
	bullet->addTag("Bullet");
	auto bul = bullet->addComponent<BulletComponent>(_bSettings, _bulletTextureHelper);	
	bullet->setView(_parent->getView());
	bullet->setAlive(true);
	bullet->setVisible(true);
	
	sounds[_wSettings.sound].setPitch(1.f + sin(accumulation) * .025f);
	sounds[_wSettings.sound].setVolume(15.f);
	sounds[_wSettings.sound].play();
}

void WeaponComponent::update(double dt) {
	accumulation += dt;
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
	: Component(p), _wSettings(wSettings), _bSettings(bSettings), _bulletTextureHelper(bTextureHelper), accumulation(0.f) {}