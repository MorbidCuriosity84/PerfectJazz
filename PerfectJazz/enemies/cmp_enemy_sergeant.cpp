#include "cmp_enemy_sergeant.h"
#include "../components/cmp_bullet.h"
#include "../components/cmp_enemy_physics.h"
#include "../components/cmp_enemy_turret.h"
#include "../components//cmp_hurt_player.h"
#include "../components/cmp_sprite.h"
#include "../components/cmp_hp.h"
#include <LevelSystem.h>
#include "engine.h"
#include <SFML/Graphics/CircleShape.hpp>

using namespace std;
using namespace sf;
sf::Texture sergeantTexture;
sf::IntRect sergeantRectangle;
double sergeantSpriteTimer;

void SergeantEnemyComponent::Load(int _index) {
	sergeantTexture.loadFromFile("res/img/enemies/enemy2_900.png");
	auto s = _parent->addComponent<SpriteComponent>();
	sergeantRectangle.left = (sergeantTexture.getSize().x / 2);
	sergeantRectangle.top = (sergeantTexture.getSize().y) * 0;
	sergeantRectangle.width = (sergeantTexture.getSize().x / 2);
	sergeantRectangle.height = (sergeantTexture.getSize().y);
	s->getSprite().setTexture(sergeantTexture);
	s->getSprite().setTextureRect(sergeantRectangle);
	s->getSprite().setOrigin(sergeantTexture.getSize().x / 4, sergeantTexture.getSize().y / 2);

	vector<Vector2ul> tile = ls::findTiles(ls::SERGEANT);
	_parent->setPosition(Vector2f(ls::getTilePosition(tile[_index]).x + 15.f, ls::getTilePosition(tile[_index]).y - 500.f));
	_parent->addComponent<EnemyPhysicsComponent>(Vector2f(15.f, 15.f));
	_parent->addComponent<HPComponent>(_scene, 1000);
	_parent->addComponent<HurtComponent>();
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
	bullet->addComponent<HurtComponent>();
	bullet->addComponent<BulletComponent>();
	bullet->setView(_parent->getView());
	auto s = bullet->addComponent<ShapeComponent>();

	s->setShape<sf::CircleShape>(4.f);
	s->getShape().setFillColor(Color::Blue);
	s->getShape().setOrigin(2.f, 2.f);
	auto p = bullet->addComponent<PhysicsComponent>(true, Vector2f(4.f, 4.f));
	p->getBody()->SetBullet(true);
	p->setSensor(true);
	p->setRestitution(.4f);
	p->setFriction(.005f);
	p->setVelocity({ 0.f, -500.f });
	//p->impulse(sf::rotate(Vector2f(0, 15.f), -_parent->getRotation()));
}

SergeantEnemyComponent::SergeantEnemyComponent(Entity* p, Scene* scene)
	: Component(p), _firetime(3.f), _scene(scene) {
}
