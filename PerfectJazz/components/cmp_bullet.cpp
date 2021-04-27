#include "cmp_bullet.h"
#include "../movement/cmp_missile_movement.h"
#include "maths.h"
#include <iostream>
#include "cmp_sound.h"
#include "../sound_Queue.h"

using namespace std;
using namespace sf;


void BulletComponent::createBullet() {
	_bulletTextHelper.spriteTexture->loadFromFile(_bulletTextHelper.spriteFilename);
	spriteCMP = _parent->addComponent<SpriteComponent>();
	spriteCMP.get()->loadTexture(_bulletTextHelper, _settings.spriteScale, _settings.angle);	
	spriteCMP.get()->getSprite().setRotation(_settings.angle);
	damageCMP = _parent->addComponent<DamageComponent>(_settings.damage + (_settings.damage * 0.2 * _settings.damageUpgradeCount));
	physicsCMP = _parent->addComponent<PhysicsComponent>(true, spriteCMP.get()->getSprite().getLocalBounds().getSize());
	
	hpCMP = _parent->addComponent<HPComponent>(_settings.scene, 100, 100);
	hpCMP.get()->loadHP();
	hpCMP.get()->setVisible(false);

	physicsCMP->getBody()->SetBullet(true);
	physicsCMP->setSensor(true);
	Vector2f bulletVelocity =_settings.velocity * _settings.direction;
	physicsCMP->setVelocity(Vector2f(bulletVelocity.x - _parent->getRotation(), bulletVelocity.y));
	physicsCMP->setCategory(_settings.category);		
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

	spriteCMP->getSprite().setTextureRect(*_bulletTextHelper.spriteRectangle.get());
	spriteCMP->getSprite().setPosition(_parent->getPosition());		
	
	if (hpCMP->getHP() <= 0) {
		_parent->setAlive(false);
		_parent->setVisible(false);
		physicsCMP->getBody()->SetActive(false);	
		_parent->setPosition(Vector2f(-100.f, -100.f));
	}	
	if (_parent->getPosition().y > _parent->getView().getSize().y ||
		_parent->getPosition().y < 0 ||
		_parent->getPosition().x > _parent->getView().getSize().x ||
		_parent->getPosition().x < 0) {
		_parent->setAlive(false);
		_parent->setVisible(false);
		physicsCMP->getBody()->SetActive(false);
		_parent->setPosition(Vector2f(-100.f, -100.f));
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
		bul_colHelp.missileCMP = _parent->addComponent<MissileMovementComponent>(Vector2f(0.f, -150.f), false, _settings.category).get();		
		_parent->addTag("missile");
	}
	else {
		bul_colHelp.isMissile = false;
	}
	physicsCMP->getBody()->SetUserData(&bul_colHelp);

}