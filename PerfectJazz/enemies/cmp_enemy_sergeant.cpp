#include "cmp_enemy_sergeant.h"
#include "../components/cmp_bullet.h"
#include "../components/cmp_enemy_physics.h"
#include "../components/cmp_sprite.h"
#include "../components/cmp_hp.h"
#include <LevelSystem.h>
#include "engine.h"
#include <SFML/Graphics/CircleShape.hpp>

using namespace std;
using namespace sf;
sf::Texture sergeantTexture;
sf::IntRect sergeantRectangle;
sf::Texture sg_bulletTexture;
sf::IntRect sg_bulletRectangle;
double sergeantSpriteTimer;

void SergeantEnemyComponent::Load(int _index) {
	sergeantTexture.loadFromFile("res/img/enemies/enemy2_900.png");
	auto s = _parent->addComponent<SpriteComponent>();
	s->loadTexture(1, 2, 0, 0, sergeantRectangle, sergeantTexture);		
	vector<Vector2ul> tile = ls::findTiles(ls::SERGEANT);
	_parent->setPosition(Vector2f(ls::getTilePosition(tile[_index]).x + 15.f, ls::getTilePosition(tile[_index]).y - 500.f));
	auto phys = _parent->addComponent<EnemyPhysicsComponent>(Vector2f(15.f, 15.f));
	auto d = _parent->addComponent<DamageComponent>(100u);	
	phys.get()->setCategory(ENEMY);	
	auto h = _parent->addComponent<HPComponent>(_scene, 1000);	
	phys.get()->getBody()->SetUserData(h.get());
	//_parent->addComponent<HurtComponent>();
	_parent->addTag("enemies");
}
void SergeantEnemyComponent::update(double dt) {
	auto s = _parent->GetCompatibleComponent<SpriteComponent>();
	auto p = _parent->GetCompatibleComponent<PhysicsComponent>();

	sergeantSpriteTimer += dt / 2;

	if (sergeantSpriteTimer < 0.5) {
		sergeantRectangle.left = (sergeantTexture.getSize().x / 2) * 0;
	}
	if (sergeantSpriteTimer >= 0.5 && sergeantSpriteTimer < 1) {
		sergeantRectangle.left = (sergeantTexture.getSize().x / 2) * 1;
	}
	if (sergeantSpriteTimer > 1) {
		sergeantSpriteTimer = 0.0;
	}
	s[0]->getSprite().setTextureRect(sergeantRectangle);

	_firetime -= dt;
	if (_firetime <= 0.f) {
		fire();
		_firetime = 1.5f;
	}
	static float angle = 0.f;
	angle += 1.f * dt;
}

void SergeantEnemyComponent::fire() const {
	auto bullet = _parent->scene->makeEntity();
	bullet->setPosition({ _parent->getPosition().x, _parent->getPosition().y + 5.f });	
	auto d = bullet->addComponent<DamageComponent>(100u);
	auto b = bullet->addComponent<BulletComponent>(d, 3.0f);	
	bullet->setView(_parent->getView());
	
	sg_bulletTexture.loadFromFile("res/img/weapons/Fx_02.png");
	auto s = bullet->addComponent<SpriteComponent>();
	s->loadTexture(1, 3, 0, 2, sg_bulletRectangle, sg_bulletTexture);	
	s->getSprite().setScale({ 1.f,2.f });
	
	auto p = bullet->addComponent<PhysicsComponent>(true, Vector2f(4.f, 4.f));
	p->getBody()->SetBullet(true);
	p->setSensor(true);
	p->setRestitution(.4f);
	p->setFriction(.005f);
	p->setVelocity({ 0.f, -500.f });
	p->setCategory(ENEMY_BULLET);

	auto h = bullet->addComponent<HPComponent>(_scene, 100);
	h->setVisible(false);
	p->getBody()->SetUserData(h.get());
	//p->impulse(sf::rotate(Vector2f(0, 15.f), -_parent->getRotation()));
}

SergeantEnemyComponent::SergeantEnemyComponent(Entity* p, Scene* scene)
	: Component(p), _firetime(3.f), _scene(scene) {
}
