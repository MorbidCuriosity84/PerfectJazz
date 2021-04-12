#include "cmp_enemy_airman.h"
#include "../components/cmp_bullet.h"
#include "../components/cmp_enemy_physics.h"
#include "../components/cmp_enemy_turret.h"
#include "../components//cmp_hurt_player.h"
#include "../components/cmp_sprite.h"
#include <LevelSystem.h>
#include "engine.h"
#include <SFML/Graphics/CircleShape.hpp>
#include "../components/cmp_health.h"
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
	s.get()->loadTexture(1, 2, 0, 0, airmanRectangle, airmanTexture);	

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
	auto b =bullet->addComponent<BulletComponent>();
	bullet->setView(_parent->getView());	
	
	air_bulletTexture.loadFromFile("res/img/weapons/Fx_01.png");
	auto s = bullet->addComponent<SpriteComponent>();
	s->loadTexture(1, 3, 0, 1, air_bulletRectangle, air_bulletTexture);

	auto h = bullet->addComponent<HealthComponent>();
	auto p = bullet->addComponent<PhysicsComponent>(true, Vector2f(4.f, 4.f));
	p->getBody()->SetBullet(true);
	p->setSensor(true);
	p->setRestitution(.4f);
	p->setFriction(.005f);
	p->setVelocity({ 0.f, -300.f });
	p->setCategory(ENEMY);	
	p->getBody()->SetUserData(&h);
	//p->impulse(sf::rotate(Vector2f(0, 15.f), -_parent->getRotation()));
}

AirManEnemyComponent::AirManEnemyComponent(Entity* p)
	: Component(p), _firetime(2.f) {
}
