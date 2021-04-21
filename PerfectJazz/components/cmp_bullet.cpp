#include "cmp_bullet.h"
#include "../movement/cmp_missile_movement.h"

using namespace std;
using namespace sf;

void BulletComponent::createBullet() {
	_bulletTextHelper.spriteTexture.get()->loadFromFile(_bulletTextHelper.spriteFilename);
	_bulletSprite = _parent->addComponent<SpriteComponent>();
	_bulletSprite->loadTexture(_bulletTextHelper, _settings.spriteScale, _settings.angle);
	auto d = _parent->addComponent<DamageComponent>(_settings.damage);
	auto p = _parent->addComponent<PhysicsComponent>(true, _bulletSprite.get()->getSprite().getLocalBounds().getSize());
	auto h = _parent->addComponent<HPComponent>(_settings.scene, 100);
	h.get()->loadHP();

	p->getBody()->SetBullet(true);
	p->setSensor(true);
	p->setVelocity(_settings.velocity * _settings.direction);
	p->setCategory(_settings.category);

	h.get()->setVisible(false);
	p->getBody()->SetUserData(h.get());

	if (_settings.category == ENEMY_MISSILE) {
		_parent->addComponent<MissileMovementComponent>(Vector2f(0.f, -150.f), true);
	}
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

	auto hp = _parent->GetCompatibleComponent<HPComponent>()[0];
	if (hp->getHP() <= 0) {
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
}