#include "cmp_bullet.h"
#include "../movement/cmp_missile_movement.h"
#include "maths.h"
#include <iostream>

using namespace std;
using namespace sf;


void BulletComponent::createBullet() {
	_bulletTextHelper.spriteTexture.get()->loadFromFile(_bulletTextHelper.spriteFilename);
	_bulletSprite = _parent->addComponent<SpriteComponent>();
	_bulletSprite->loadTexture(_bulletTextHelper, _settings.spriteScale, _settings.angle);
	_bulletSprite.get()->getSprite().setRotation(_settings.angle);
	damageCMP = _parent->addComponent<DamageComponent>(_settings.damage + (_settings.damage * 0.2 * _settings.damageUpgradeCount));
	physicsCMP = _parent->addComponent<PhysicsComponent>(true, _bulletSprite.get()->getSprite().getLocalBounds().getSize());
	hpCMP = _parent->addComponent<HPComponent>(_settings.scene, 100);
	hpCMP.get()->loadHP();

	physicsCMP->getBody()->SetBullet(true);
	physicsCMP->setSensor(true);
	physicsCMP->setVelocity(_settings.velocity * _settings.direction);
	physicsCMP->setVelocity(Vector2f(physicsCMP->getVelocity().x - _parent->getRotation(), physicsCMP->getVelocity().y));
	physicsCMP->setCategory(_settings.category);
	hpCMP.get()->setVisible(false);
}


void BulletComponent::update(double dt) {
	_bulletTextHelper.spriteTimer += dt / 2;

	if (_bulletTextHelper.spriteTimer < 0.1) {
		_bulletTextHelper.spriteRectangle.get()->left = (_bulletTextHelper.spriteTexture.get()->getSize().x / _bulletTextHelper.spriteCols) * 1;
	}
	if (_bulletTextHelper.spriteTimer >= 0.1 && _bulletTextHelper.spriteTimer < 0.3) {
		_bulletTextHelper.spriteRectangle.get()->left = (_bulletTextHelper.spriteTexture.get()->getSize().x / _bulletTextHelper.spriteCols) * 2;
	}
	if (_bulletTextHelper.spriteTimer >= 0.3 && _bulletTextHelper.spriteTimer < 0.4) {
		_bulletTextHelper.spriteRectangle.get()->left = (_bulletTextHelper.spriteTexture.get()->getSize().x / _bulletTextHelper.spriteCols) * 1;
	}
	if (_bulletTextHelper.spriteTimer >= 0.4 && _bulletTextHelper.spriteTimer < 0.5) {
		_bulletTextHelper.spriteRectangle.get()->left = (_bulletTextHelper.spriteTexture.get()->getSize().x / _bulletTextHelper.spriteCols) * 0;
	}
	if (_bulletTextHelper.spriteTimer >= 0.6) {
		_bulletTextHelper.spriteTimer = 0.0;
	}


	_bulletSprite->getSprite().setTextureRect(*_bulletTextHelper.spriteRectangle.get());
	_bulletSprite->getSprite().setPosition(_parent->getPosition());			
	Vector2f bul_pl_dif = _parent->getPosition() - player->getPosition();
	//_bulletSprite->getSprite().setRotation(90.f - bul_pl_dif.y / bul_pl_dif.x);
	
	_bulletSprite->getSprite().setRotation(_bulletSprite->getSprite().getRotation() - atan(bul_pl_dif.x / bul_pl_dif.y));
	
	if (hpCMP->getHP() <= 0) {
		_parent->setForDelete();
	}

	if (_parent->getPosition().y > _parent->getView().getSize().y ||
		_parent->getPosition().y < 0 ||
		_parent->getPosition().x > _parent->getView().getSize().x ||
		_parent->getPosition().x < 0) {
		_parent->setForDelete();
	}
}

BulletComponent::BulletComponent(Entity* p, bulletSettings settings, textureSettings bulletTexHelper)
	: Component(p), _settings(settings), _bulletTextHelper(bulletTexHelper) {
	createBullet();
	bul_colHelp.damageCMP = damageCMP.get();
	bul_colHelp.hpCMP = hpCMP.get();
	bul_colHelp.isMissile = false;
	bul_colHelp.missileCMP = nullptr;
	if (_settings.category == ENEMY_MISSILE || _settings.category == FRIENDLY_MISSILE) 	{
		bul_colHelp.isMissile = true;
	}
	else {
		bul_colHelp.isMissile = false;
	}
	//colHelp.isMissile = (_settings.category == (ENEMY_MISSILE || FRIENDLY_MISSILE) ? true : false);

	if (_settings.category == ENEMY_MISSILE || _settings.category == FRIENDLY_MISSILE) 	{
		bul_colHelp.missileCMP = _parent->addComponent<MissileMovementComponent>(Vector2f(0.f, -150.f), false, _settings.category).get();
		bul_colHelp.isMissile = true;
		_parent->addTag("missile");
	}
	physicsCMP->getBody()->SetUserData(&bul_colHelp);

}