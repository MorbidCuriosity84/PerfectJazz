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

	wepSettings wSettings;
	wSettings.damage = 100;
	wSettings.fireTime = 1.5f;
	wSettings.fireTimer = 1.5f;
	wSettings.numBullets = 1;
	wSettings.scene = _enemySettings.scene;
	wSettings.direction = 1;

	bulletSettings bSettings;
	bSettings.damage = 100;
	bSettings.hp = 100;
	bSettings.lifetime = 10.f;
	bSettings.scene = _enemySettings.scene;
	bSettings.angle = 90.f;
	bSettings.category = ENEMY_BULLET;
	bSettings.direction = -1;
	bSettings.velocity = Vector2f(0.f, 100.f);

	_parent->setPosition(Vector2f(ls::getTilePosition(tile[index]).x, ls::getTilePosition(tile[index]).y - 460.f));
	_parent->addComponent<DamageComponent>(_enemySettings.damage);
	_parent->addComponent<WeaponComponent>(wSettings, bSettings);
	_parent->addTag("enemies");
	_spriteHelper.spriteTexture.get()->loadFromFile(_spriteHelper.spriteFilename);

	auto s = _parent->addComponent<SpriteComponent>();
	s.get()->loadTexture(_spriteHelper, _enemySettings.scale, _enemySettings.angle);
	auto phys = _parent->addComponent<EnemyPhysicsComponent>(s->getSprite().getGlobalBounds().getSize());
	phys.get()->setCategory(_enemySettings.category);

	auto h = _parent->addComponent<HPComponent>(_enemySettings.scene, _enemySettings.hp);
	phys.get()->getBody()->SetUserData(h.get());
}

void EnemyComponent::update(double dt) {
	auto s = _parent->GetCompatibleComponent<SpriteComponent>();

	_spriteHelper.spriteTimer += dt / 2;

	if (_spriteHelper.spriteTimer < 0.5) {
		_spriteHelper.spriteRectangle.get()->left = (_spriteHelper.spriteTexture.get()->getSize().x / 2) * 0;
	}
	if (_spriteHelper.spriteTimer >= 0.5 && _spriteHelper.spriteTimer < 1) {
		_spriteHelper.spriteRectangle.get()->left = (_spriteHelper.spriteTexture.get()->getSize().x / 2) * 1;
	}
	if (_spriteHelper.spriteTimer > 1) {
		_spriteHelper.spriteTimer = 0.0;
	}
	s[0]->getSprite().setTextureRect(*_spriteHelper.spriteRectangle.get());
}

EnemyComponent::EnemyComponent(Entity* p, textureHelper spriteTexHelp, enemySettings enemySettings)
	: Component(p), _spriteHelper(spriteTexHelp), _enemySettings(enemySettings) { }





