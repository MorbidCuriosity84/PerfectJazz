#pragma once
#include "cmp_physics.h"

//Enemy physics component that sets the basic physics for the enemy
//not as complex as the player physics
class EnemyPhysicsComponent : public PhysicsComponent {
protected:
  b2Vec2 _size;
  sf::Vector2f _maxVelocity;
  float _flySpeed;

public:
  void update(double dt) override;
  explicit EnemyPhysicsComponent(Entity* p, const sf::Vector2f& size);
  EnemyPhysicsComponent() = delete;
};