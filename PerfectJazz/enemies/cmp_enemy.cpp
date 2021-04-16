#include "cmp_enemy.h"
#include "../components/cmp_sprite.h"
#include "../components/cmp_enemy_physics.h"
#include "../components/cmp_hp.h"
#include "../components/cmp_damage.h"
#include "../components/cmp_bullet.h"

using namespace std;

void EnemyComponent::fire() {

	_weapon.get()->fire();


}

void EnemyComponent::Load(int index) {
	_spriteHelper._spriteTexture.get()->loadFromFile(_spriteHelper.spriteFilename);
	auto s = _parent->addComponent<SpriteComponent>();
	s.get()->loadTexture(_spriteHelper, _settings._spriteScale, _settings._spriteAngle);

	vector<Vector2ul> tile = ls::findTiles(_settings._tile);
		
	auto w = _parent->addComponent<MissileComponent>(_weaponSpriteHelper, _settings.weaponSettings);
	_weapon = w;
	_parent->setPosition(Vector2f(ls::getTilePosition(tile[index]).x + s->getSprite().getTextureRect().width / 2, ls::getTilePosition(tile[index]).y - 460.f));
	auto phys = _parent->addComponent<EnemyPhysicsComponent>(s->getSprite().getGlobalBounds().getSize());
	phys.get()->setCategory(_settings._cat);
	auto h = _parent->addComponent<HPComponent>(_settings._scene, _settings._hp);
	auto d = _parent->addComponent<DamageComponent>(_settings._damage);	

	phys.get()->getBody()->SetUserData(h.get());
	_parent->addTag("enemies");
}

void EnemyComponent::update(double dt) {
	auto s = _parent->GetCompatibleComponent<SpriteComponent>();

	_spriteHelper._spriteTimer += dt / 2;

	if (_spriteHelper._spriteTimer < 0.5) {
		_spriteHelper._spriteRectangle.get()->left = (_spriteHelper._spriteTexture.get()->getSize().x / 2) * 0;
	}
	if (_spriteHelper._spriteTimer >= 0.5 && _spriteHelper._spriteTimer < 1) {
		_spriteHelper._spriteRectangle.get()->left = (_spriteHelper._spriteTexture.get()->getSize().x / 2) * 1;
	}
	if (_spriteHelper._spriteTimer > 1) {
		_spriteHelper._spriteTimer = 0.0;
	}
	s[0]->getSprite().setTextureRect(*_spriteHelper._spriteRectangle.get());

	for (auto b : enemyBullets) {
		auto pSprite = b->GetCompatibleComponent<SpriteComponent>();
		_weaponSpriteHelper._spriteTimer += dt / 2;

		if (_weaponSpriteHelper._spriteTimer >= 1) {
			_weaponSpriteHelper._spriteRectangle.get()->left = (_weaponSpriteHelper._spriteTexture.get()->getSize().x / _weaponSpriteHelper.spriteCols) * 0;
		}
		if (_weaponSpriteHelper._spriteTimer >= 1 && _weaponSpriteHelper._spriteTimer < 2) {
			_weaponSpriteHelper._spriteRectangle.get()->left = (_weaponSpriteHelper._spriteTexture.get()->getSize().x / _weaponSpriteHelper.spriteCols) * 1;
		}
		if (_weaponSpriteHelper._spriteTimer >= 2 && _weaponSpriteHelper._spriteTimer < 3) {
			_weaponSpriteHelper._spriteRectangle.get()->left = (_weaponSpriteHelper._spriteTexture.get()->getSize().x / _weaponSpriteHelper.spriteCols) * 2;
		}
		if (_weaponSpriteHelper._spriteTimer >= 3) {
			_weaponSpriteHelper._spriteTimer = 0.0;

		}

		pSprite[0]->getSprite().setTextureRect(*_weaponSpriteHelper._spriteRectangle.get());
	}

	_fireTime -= dt;
	if (_fireTime <= 0.f) {
		fire();
		_fireTime = _settings._fireTimer;
	}
}

EnemyComponent::EnemyComponent(Entity* p, textureHelper spriteTexHelp, textureHelper wepSpriteTexHelp, enemySettings settings)
	: Component(p), _spriteHelper(spriteTexHelp), _weaponSpriteHelper(wepSpriteTexHelp), _settings(settings) {
}

void EnemyComponent::addWeapon(shared_ptr<WeaponComponent> wep) { _weapon = wep; }

shared_ptr<WeaponComponent> EnemyComponent::getWeapon() const { return _weapon; }


