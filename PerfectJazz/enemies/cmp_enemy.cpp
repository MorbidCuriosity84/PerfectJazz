#include "cmp_enemy.h"
#include "engine.h"
#include "../components/cmp_sprite.h"
#include "../components/cmp_enemy_physics.h"
#include "../components/cmp_hp.h"
#include "../components/cmp_damage.h"
#include "../components/cmp_weapon.h"

using namespace std;

void EnemyComponent::Load(int index) {
	vector<Vector2ul> tile = ls::findTiles(_settings._tile);
	wepSettings wS(1.5f, 1, _settings._scene);

	_parent->setPosition(Vector2f(ls::getTilePosition(tile[index]).x, ls::getTilePosition(tile[index]).y - 460.f));
	_parent->addComponent<DamageComponent>(_settings._damage);
	_parent->addComponent<WeaponComponent>(wS);
	_parent->addTag("enemies");
	_spriteHelper.spriteTexture.get()->loadFromFile(_spriteHelper.spriteFilename);

	auto s = _parent->addComponent<SpriteComponent>();
	s.get()->loadTexture(_spriteHelper, _settings._spriteScale, _settings._spriteAngle);
	auto phys = _parent->addComponent<EnemyPhysicsComponent>(s->getSprite().getGlobalBounds().getSize());
	phys.get()->setCategory(_settings._cat);

	auto h = _parent->addComponent<HPComponent>(_settings._scene, _settings._hp);
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

EnemyComponent::EnemyComponent(Entity* p, textureHelper spriteTexHelp, enemySettings settings)
	: Component(p), _spriteHelper(spriteTexHelp), _settings(settings) { }





