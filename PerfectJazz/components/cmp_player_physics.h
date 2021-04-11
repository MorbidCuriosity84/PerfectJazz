#pragma once

#include "cmp_physics.h"

class PlayerPhysicsComponent : public PhysicsComponent {
protected:
  b2Vec2 _size;
  sf::Vector2f _maxVelocity;
  bool _grounded;
  float _groundspeed;
  std::string _direction;

  bool isGrounded() const;

public:
  void update(double dt) override;
  explicit PlayerPhysicsComponent(Entity* p, const sf::Vector2f& size);
  PlayerPhysicsComponent() = delete;
  std::string GetDirection();
};
