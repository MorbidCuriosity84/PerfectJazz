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
sf::Texture airmanTexture;
sf::IntRect airmanRectangle;
sf::Texture air_bulletTexture;
sf::IntRect air_bulletRectangle;
double airmanSpriteTimer;

void AirManEnemyComponent::Load(int _index) {
	airmanTexture.loadFromFile("res/img/enemies/enemy1_900.png");
	auto s = _parent->addComponent<SpriteComponent>();
	airmanRectangle.left = (airmanTexture.getSize().x / 2);
	airmanRectangle.top = (airmanTexture.getSize().y) * 0;
	airmanRectangle.width = (airmanTexture.getSize().x / 2);
	airmanRectangle.height = (airmanTexture.getSize().y);
	s->getSprite().setTexture(airmanTexture);
	s->getSprite().setTextureRect(airmanRectangle);
	s->getSprite().setOrigin(airmanTexture.getSize().x / 4, airmanTexture.getSize().y / 2);

	vector<Vector2ul> tile = ls::findTiles(ls::AIRMAN);
	_parent->setPosition(Vector2f(ls::getTilePosition(tile[_index]).x + 15.f, ls::getTilePosition(tile[_index]).y - 500.f));
	_parent->addComponent<EnemyPhysicsComponent>(Vector2f(15.f, 15.f));
	_parent->addComponent<HurtComponent>();
	_parent->addTag("enemies");
}
void AirManEnemyComponent::update(double dt) {
	auto s = _parent->GetCompatibleComponent<SpriteComponent>();
	auto p = _parent->GetCompatibleComponent<PhysicsComponent>();

	airmanSpriteTimer += dt /2;

	if (airmanSpriteTimer < 0.5) {
		airmanRectangle.left = (airmanTexture.getSize().x / 2) * 0;
	}
	if (airmanSpriteTimer >= 0.5 && airmanSpriteTimer < 1) {
		airmanRectangle.left = (airmanTexture.getSize().x / 2) * 1;
	}
	if (airmanSpriteTimer > 1) {
		airmanSpriteTimer = 0.0;
	}
	s[0]->getSprite().setTextureRect(airmanRectangle);

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
	
	air_bulletTexture.loadFromFile("res/img/weapons/Fx_01.png");
	auto s = bullet->addComponent<SpriteComponent>();
	air_bulletRectangle.left = (air_bulletTexture.getSize().x / 3);
	air_bulletRectangle.top = (air_bulletTexture.getSize().y) * 0;
	air_bulletRectangle.width = (air_bulletTexture.getSize().x / 3);
	air_bulletRectangle.height = (air_bulletTexture.getSize().y);
	s->getSprite().setTexture(air_bulletTexture);
	s->getSprite().setTextureRect(air_bulletRectangle);
	s->getSprite().setOrigin(air_bulletTexture.getSize().x / 6, air_bulletTexture.getSize().y / 2);

	auto p = bullet->addComponent<PhysicsComponent>(true, Vector2f(4.f, 4.f));
	p->getBody()->SetBullet(true);
	p->setSensor(true);
	p->setRestitution(.4f);
	p->setFriction(.005f);
	p->setVelocity({ 0.f, -300.f });
	p->setCategory(ENEMY);
	//p->impulse(sf::rotate(Vector2f(0, 15.f), -_parent->getRotation()));
}

AirManEnemyComponent::AirManEnemyComponent(Entity* p)
	: Component(p), _firetime(2.f) {
}
