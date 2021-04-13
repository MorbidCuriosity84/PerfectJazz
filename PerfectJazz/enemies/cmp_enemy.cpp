#include "cmp_enemy.h"
#include "../components/cmp_sprite.h"
#include "../components/cmp_enemy_physics.h"
#include "../components/cmp_hp.h"
#include "../components/cmp_damage.h"
#include "../components/cmp_bullet.h"

using namespace std;

//sf::IntRect _spriteRectangle;
//sf::Texture _spriteTexture;
//sf::IntRect _weaponSpriteRectangle;
//sf::Texture _weaponSpriteTexture;

void EnemyComponent::fire()
{
	auto bullet = _parent->scene->makeEntity();
	bullet->setPosition({ _parent->getPosition().x, _parent->getPosition().y + 5.f });
	auto d = bullet->addComponent<DamageComponent>(100u);
	auto b = bullet->addComponent<BulletComponent>(d, 3.0f);	
	bullet->setView(_parent->getView());

	_weaponSpriteHelper._spriteTexture.get()->loadFromFile(_weaponSpriteHelper.spriteFilename);
	auto s = bullet->addComponent<SpriteComponent>();
	s->loadTexture(_weaponSpriteHelper, { 1.f,2.f });
	
	auto p = bullet->addComponent<PhysicsComponent>(true, s.get()->getSprite().getLocalBounds().getSize());
	p->getBody()->SetBullet(true);
	p->setSensor(true);
	p->setRestitution(.4f);
	p->setFriction(.005f);
	p->setVelocity({ 0.f, -300.f });
	p->setCategory(ENEMY_BULLET);

	auto h = bullet->addComponent<HPComponent>(_scene, 100);
	h->setVisible(false);
	p->getBody()->SetUserData(h.get());
}

void EnemyComponent::Load(int index)
{
	_spriteHelper._spriteTexture.get()->loadFromFile(_spriteHelper.spriteFilename);
	auto s = _parent->addComponent<SpriteComponent>();
	s.get()->loadTexture(_spriteHelper, { 1.f,1.f });

	vector<Vector2ul> tile = ls::findTiles(_tileType);
	_parent->setPosition(Vector2f(ls::getTilePosition(tile[index]).x + 15.f, ls::getTilePosition(tile[index]).y - 500.f));
	auto phys = _parent->addComponent<EnemyPhysicsComponent>(Vector2f(15.f, 15.f));
	phys.get()->setCategory(ENEMY);
	auto h = _parent->addComponent<HPComponent>(_scene, 1000);
	auto d = _parent->addComponent<DamageComponent>(100u);
	phys.get()->getBody()->SetUserData(h.get());	
	_parent->addTag("enemies");
}

void EnemyComponent::update(double dt)
{
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
		_fireTime = 1.5f;
	}
	static float angle = 0.f;
	angle += 1.f * dt;
}

EnemyComponent::EnemyComponent(Entity* p, double fireTime, Scene* scene, ls::Tile tileType, textureHelper spriteTexHelp, textureHelper wepSpriteTexHelp)
	: Component(p), _fireTime(fireTime), _scene(scene), _tileType(tileType), _spriteHelper(spriteTexHelp), _weaponSpriteHelper(wepSpriteTexHelp) {}


