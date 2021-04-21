#include "cmp_enemy.h"
#include "ecm.h"
#include "../components/cmp_sprite.h"
#include "../components/cmp_enemy_physics.h"
#include "../movement/cmp_movement.h"
#include "../movement/cmp_move_sine.h"

using namespace std;
using namespace sf;

void EnemyComponent::Load(int index) {
	vector<Vector2ul> tile = ls::findTiles(_enemySettings.tile);

	_parent->setPosition(Vector2f(ls::getTilePosition(tile[index]).x, ls::getTilePosition(tile[index]).y - 460.f));
	_parent->addComponent<DamageComponent>(_enemySettings.damage);
	_parent->addComponent<WeaponComponent>(_weaponSettings, _bulletSettings, _bulletTextureHelper);
	//_parent->addComponent<MovementComponent>(Vector2f(0.f, -50.f));
	_parent->addTag("enemies");
	_enemyTextureHelper.spriteTexture.get()->loadFromFile(_enemyTextureHelper.spriteFilename);

	auto s = _parent->addComponent<SpriteComponent>();
	s.get()->loadTexture(_enemyTextureHelper, _enemySettings.scale, _enemySettings.angle);
	auto phys = _parent->addComponent<EnemyPhysicsComponent>(s->getSprite().getGlobalBounds().getSize());
	phys.get()->setCategory(_enemySettings.category);

	auto h = _parent->addComponent<HPComponent>(_enemySettings.scene, _enemySettings.hp);	
	h->loadHP();
	h.get()->setVisible(_enemySettings.hpVisible);
	h->setSpriteColour(Color::Red);
	h->setTextColour(Color::White);
	h->setScale(Vector2f(1.f, 0.8f));

	phys.get()->getBody()->SetUserData(h.get());

	//_parent->addComponent<SineMovementComponent>(Vector2f(0.f,-50.f), 15.f);
}

void EnemyComponent::update(double dt) {
	auto s = _parent->GetCompatibleComponent<SpriteComponent>();

	_enemyTextureHelper.spriteTimer += dt;

	if (_enemyTextureHelper.spriteTimer < 0.05) {
		_enemyTextureHelper.spriteRectangle.get()->left = (_enemyTextureHelper.spriteTexture.get()->getSize().x / 2) * 0;
	}
	if (_enemyTextureHelper.spriteTimer >= 0.1 && _enemyTextureHelper.spriteTimer < 0.15) {
		_enemyTextureHelper.spriteRectangle.get()->left = (_enemyTextureHelper.spriteTexture.get()->getSize().x / 2) * 1;
	}
	if (_enemyTextureHelper.spriteTimer > 0.2) {
		_enemyTextureHelper.spriteTimer = 0.0;
	}
	s[0]->getSprite().setTextureRect(*_enemyTextureHelper.spriteRectangle.get());
	s[0]->getSprite().setPosition(_parent->getPosition());

	auto hp = _parent->GetCompatibleComponent<HPComponent>()[0];
	if (hp->getHP() <= 0) {
		_parent->setForDelete();
	}
}

EnemyComponent::EnemyComponent(Entity* p, textureSettings enemyTextureHelper, textureSettings bulletTextureHelper, enemySettings enemySettings, weaponSettings weaponSettings, bulletSettings bulletSettings)
	: Component(p), _enemyTextureHelper(enemyTextureHelper), _bulletTextureHelper(bulletTextureHelper), _enemySettings(enemySettings), _weaponSettings(weaponSettings), _bulletSettings(bulletSettings) {
}





