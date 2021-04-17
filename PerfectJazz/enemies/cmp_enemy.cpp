#include "cmp_enemy.h"
#include "engine.h"
#include "../components/cmp_sprite.h"
#include "../components/cmp_enemy_physics.h"
#include "../components/cmp_hp.h"
#include "../components/cmp_damage.h"
#include "../components/cmp_weapon.h"

using namespace std;

void EnemyComponent::Load(int index) {
	vector<Vector2ul> tile = ls::findTiles(_enemySettings.tile);

	_parent->setPosition(Vector2f(ls::getTilePosition(tile[index]).x, ls::getTilePosition(tile[index]).y - 460.f));
	_parent->addComponent<DamageComponent>(_enemySettings.damage);
	_parent->addComponent<WeaponComponent>(_weaponSettings, _bulletSettings, _bulletTextureHelper);
	_parent->addTag("enemies");
	_enemyTextureHelper.spriteTexture.get()->loadFromFile(_enemyTextureHelper.spriteFilename);

	auto s = _parent->addComponent<SpriteComponent>();
	s.get()->loadTexture(_enemyTextureHelper, _enemySettings.scale, _enemySettings.angle);
	auto phys = _parent->addComponent<EnemyPhysicsComponent>(s->getSprite().getGlobalBounds().getSize());
	phys.get()->setCategory(_enemySettings.category);

	auto h = _parent->addComponent<HPComponent>(_enemySettings.scene, _enemySettings.hp);
	phys.get()->getBody()->SetUserData(h.get());
}

void EnemyComponent::update(double dt) {
	auto s = _parent->GetCompatibleComponent<SpriteComponent>();

	_enemyTextureHelper.spriteTimer += dt / 2;

	if (_enemyTextureHelper.spriteTimer < 0.5) {
		_enemyTextureHelper.spriteRectangle.get()->left = (_enemyTextureHelper.spriteTexture.get()->getSize().x / 2) * 0;
	}
	if (_enemyTextureHelper.spriteTimer >= 0.5 && _enemyTextureHelper.spriteTimer < 1) {
		_enemyTextureHelper.spriteRectangle.get()->left = (_enemyTextureHelper.spriteTexture.get()->getSize().x / 2) * 1;
	}
	if (_enemyTextureHelper.spriteTimer > 1) {
		_enemyTextureHelper.spriteTimer = 0.0;
	}
	s[0]->getSprite().setTextureRect(*_enemyTextureHelper.spriteRectangle.get());
}

EnemyComponent::EnemyComponent(Entity* p, textureHelper enemyTextureHelper, textureHelper bulletTextureHelper, enemySettings enemySettings, wepSettings weaponSettings, bulletSettings bulletSettings)
	: Component(p), _enemyTextureHelper(enemyTextureHelper), _bulletTextureHelper(bulletTextureHelper), _enemySettings(enemySettings), _weaponSettings(weaponSettings), _bulletSettings(bulletSettings){ }





