#include "cmp_enemy.h"
#include "../components/cmp_sprite.h"
#include "../components/cmp_enemy_physics.h"
#include "../components/cmp_hp.h"
#include "../components/cmp_damage.h"
#include "../components/cmp_bullet.h"

using namespace std;

void EnemyComponent::fire() {
	auto bullet = _parent->scene->makeEntity();
	bullet->setPosition({ _parent->getPosition().x, _parent->getPosition().y + 5.f });
	auto d = bullet->addComponent<DamageComponent>(_settings._damage);
	auto b = bullet->addComponent<BulletComponent>(d, 5.f);
	bullet->setView(_parent->getView());

	_weaponSpriteHelper._spriteTexture.get()->loadFromFile(_weaponSpriteHelper.spriteFilename);
	auto s = bullet->addComponent<SpriteComponent>();
	s->loadTexture(_weaponSpriteHelper, _settings._wepSpriteScale);

	auto p = bullet->addComponent<PhysicsComponent>(true, s.get()->getSprite().getLocalBounds().getSize());
	p->getBody()->SetBullet(true);
	p->setSensor(true);
	p->setRestitution(_settings._restitution);
	p->setFriction(_settings._friction);
	p->setVelocity(_settings._velocity);
	p->setCategory(_settings._wepCat);

	auto h = bullet->addComponent<HPComponent>(_settings._scene, 100);
	h.get()->setVisible(false);
	p->getBody()->SetUserData(h.get());
}

void EnemyComponent::Load(int index) {
	_spriteHelper._spriteTexture.get()->loadFromFile(_spriteHelper.spriteFilename);
	auto s = _parent->addComponent<SpriteComponent>();
	s.get()->loadTexture(_spriteHelper, _settings._spriteScale);

	vector<Vector2ul> tile = ls::findTiles(_settings._tile);

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

	_fireTime -= dt;
	if (_fireTime <= 0.f) {
		fire();
		_fireTime = _settings._fireTime;
	}
	static float angle = 0.f;
	angle += 1.f * dt;
}

EnemyComponent::EnemyComponent(Entity* p, textureHelper spriteTexHelp, textureHelper wepSpriteTexHelp, enemySettings settings)
	: Component(p), _spriteHelper(spriteTexHelp), _weaponSpriteHelper(wepSpriteTexHelp), _settings(settings) {
}


