#include "cmp_enemy_airman.h"
#include "../components/cmp_bullet.h"
#include "../components/cmp_enemy_physics.h"
#include "../components/cmp_enemy_turret.h"
#include "../components//cmp_hurt_player.h"
#include "../components/cmp_sprite.h"
#include <LevelSystem.h>
#include "engine.h"
#include <SFML/Graphics/CircleShape.hpp>
using namespace std;
using namespace sf;
sf::Texture enemyTexture;
sf::IntRect enemyRectangle;
double enemySpriteTimer;

void AirManEnemyComponent::Load(int _index) {
	enemyTexture.loadFromFile("res/img/enemies/enemy1_900.png");
	auto s = _parent->addComponent<SpriteComponent>();
	enemyRectangle.left = (enemyTexture.getSize().x / 2);
	enemyRectangle.top = (enemyTexture.getSize().y) * 0;
	enemyRectangle.width = (enemyTexture.getSize().x / 2);
	enemyRectangle.height = (enemyTexture.getSize().y);
	s->getSprite().setTexture(enemyTexture);
	s->getSprite().setTextureRect(enemyRectangle);
	s->getSprite().setOrigin(enemyTexture.getSize().x / 4, enemyTexture.getSize().y / 2);

	vector<Vector2ul> tile = ls::findTiles(ls::AIRMAN);
	_parent->setPosition(Vector2f(ls::getTilePosition(tile[_index]).x + 15.f, ls::getTilePosition(tile[_index]).y - 500.f));
	_parent->addComponent<EnemyPhysicsComponent>(Vector2f(15.f, 15.f));
	_parent->addComponent<HurtComponent>();
	_parent->addTag("enemies");
}
void AirManEnemyComponent::update(double dt) {
	auto s = _parent->GetCompatibleComponent<SpriteComponent>();
	auto p = _parent->GetCompatibleComponent<PhysicsComponent>();

	enemySpriteTimer += dt /2;

	if (enemySpriteTimer < 0.5) {
		enemyRectangle.left = (enemyTexture.getSize().x / 2) * 0;
	}
	if (enemySpriteTimer >= 0.5 && enemySpriteTimer < 1) {
		enemyRectangle.left = (enemyTexture.getSize().x / 2) * 1;
	}
	if (enemySpriteTimer > 1) {
		enemySpriteTimer = 0.0;
	}
	s[0]->getSprite().setTextureRect(enemyRectangle);

	_firetime -= dt;
	if (_firetime <= 0.f) {
		fire();
		_firetime = 1.5f;
	}
	static float angle = 0.f;
	angle += 1.f * dt;
}

void AirManEnemyComponent::fire() const {
	auto bullet = _parent->scene->makeEntity();
	bullet->setPosition({ _parent->getPosition().x, _parent->getPosition().y + 5.f });
	bullet->addComponent<HurtComponent>();
	bullet->addComponent<BulletComponent>();
	bullet->setView(_parent->getView());
	auto s = bullet->addComponent<ShapeComponent>();

	s->setShape<sf::CircleShape>(4.f);
	s->getShape().setFillColor(Color::Red);
	s->getShape().setOrigin(2.f, 2.f);
	auto p = bullet->addComponent<PhysicsComponent>(true, Vector2f(4.f, 4.f));
	p->getBody()->SetBullet(true);
	p->setSensor(true);
	p->setRestitution(.4f);
	p->setFriction(.005f);
	p->setVelocity({ 0.f, -500.f });
	//p->impulse(sf::rotate(Vector2f(0, 15.f), -_parent->getRotation()));
}

AirManEnemyComponent::AirManEnemyComponent(Entity* p)
	: Component(p), _firetime(2.f) {
}
