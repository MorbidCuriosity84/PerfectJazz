#include "cmp_enemy_colonel.h"
#include "../components/cmp_bullet.h"
#include "../components/cmp_enemy_physics.h"
#include "../components/cmp_enemy_turret.h"
#include "../components//cmp_hurt_player.h"
#include "../components/cmp_sprite.h"
#include <LevelSystem.h>
#include "engine.h"
#include <SFML/Graphics/CircleShape.hpp>
#include "../components/cmp_health.h"
#include "../components/cmp_hp.h"
using namespace std;
using namespace sf;
sf::Texture colonelTexture;
sf::IntRect colonelRectangle;
sf::Texture bulletTexture;
sf::IntRect bulletRectangle;
double colonelSpriteTimer;

void ColonelEnemyComponent::Load(int _index) {
	colonelTexture.loadFromFile("res/img/enemies/enemy3_900.png");
	auto s = _parent->addComponent<SpriteComponent>();
	s->loadTexture(1, 2, 0, 0, colonelRectangle, colonelTexture);	

	vector<Vector2ul> tile = ls::findTiles(ls::COLONEL);
	_parent->setPosition(Vector2f(ls::getTilePosition(tile[_index]).x + 15.f, ls::getTilePosition(tile[_index]).y - 500.f));
	auto phys = _parent->addComponent<EnemyPhysicsComponent>(Vector2f(15.f, 15.f));
	phys.get()->setCategory(ENEMY);
	auto h = _parent->addComponent<HPComponent>(_scene, 1000);	
	auto d = _parent->addComponent<DamageComponent>(100u);
	phys.get()->getBody()->SetUserData(h.get());
	//_parent->addComponent<HurtComponent>();
	_parent->addTag("enemies");
}
void ColonelEnemyComponent::update(double dt) {
	auto s = _parent->GetCompatibleComponent<SpriteComponent>();
	auto p = _parent->GetCompatibleComponent<PhysicsComponent>();

	colonelSpriteTimer += dt / 2;

	if (colonelSpriteTimer < 0.5) {
		colonelRectangle.left = (colonelTexture.getSize().x / 2) * 0;
	}
	if (colonelSpriteTimer >= 0.5 && colonelSpriteTimer < 1) {
		colonelRectangle.left = (colonelTexture.getSize().x / 2) * 1;
	}
	if (colonelSpriteTimer > 1) {
		colonelSpriteTimer = 0.0;
	}
	s[0]->getSprite().setTextureRect(colonelRectangle);

	_firetime -= dt;
	if (_firetime <= 0.f) {
		fire();
		_firetime = 1.5f;
	}
	static float angle = 0.f;
	angle += 1.f * dt;
}

void ColonelEnemyComponent::fire() const {
	auto bullet = _parent->scene->makeEntity();
	bullet->setPosition({ _parent->getPosition().x, _parent->getPosition().y + 5.f });	
	auto d = bullet->addComponent<DamageComponent>(100u);
	auto b = bullet->addComponent<BulletComponent>(d, 3.0f);
	bullet->setView(_parent->getView());		
	bulletTexture.loadFromFile("res/img/weapons/Fx_02.png");
	auto s = bullet->addComponent<SpriteComponent>();
	s->loadTexture(1, 3, 0, 1, bulletRectangle, bulletTexture);
		
	auto p = bullet->addComponent<PhysicsComponent>(true, Vector2f(5.f, 5.f));
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

ColonelEnemyComponent::ColonelEnemyComponent(Entity* p, Scene* scene)
	: Component(p), _firetime(2.f), _scene(scene) {
}
