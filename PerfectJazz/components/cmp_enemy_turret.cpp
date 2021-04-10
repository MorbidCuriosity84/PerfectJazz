#include "cmp_enemy_turret.h"
#include "cmp_bullet.h"
#include "cmp_hurt_player.h"
#include "engine.h"
#include <SFML/Graphics/CircleShape.hpp>
using namespace std;
using namespace sf;

void EnemyTurretComponent::update(double dt) {
  _firetime -= dt;
  if (_firetime <= 0.f) {
    fire();
    _firetime = 0.5f;
  }
  static float angle = 0.f;
  angle += 1.f * dt;

  _parent->setRotation(180.f + sin(angle) * 45.f);
}

void EnemyTurretComponent::fire() const {
  auto bullet = _parent->scene->makeEntity();
  bullet->setPosition(_parent->getPosition());
  bullet->addComponent<HurtComponent>();
  bullet->addComponent<BulletComponent>();
  bullet->setView(_parent->getView());
  auto s = bullet->addComponent<ShapeComponent>();

  s->setShape<sf::CircleShape>(4.f);
  s->getShape().setFillColor(Color::Red);
  s->getShape().setOrigin(2.f, 2.f);
  auto p = bullet->addComponent<PhysicsComponent>(true, Vector2f(4.f, 4.f));        
  p->setRestitution(.4f);
  p->setFriction(.005f);
  p->impulse(sf::rotate(Vector2f(0, 15.f), -_parent->getRotation()));
}

EnemyTurretComponent::EnemyTurretComponent(Entity* p)
    : Component(p), _firetime(2.f) {}
