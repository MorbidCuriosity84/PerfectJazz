#include "cmp_enemy_physics.h"
#include "system_physics.h"
#include "../PerfectJazz/game.h"
#include <LevelSystem.h>
#include <SFML/Window/Keyboard.hpp>

using namespace std;
using namespace sf;
using namespace Physics;

bool EnemyPhysicsComponent::isGrounded() const {
  auto touch = getTouching();
  const auto& pos = _body->GetPosition();
  const float halfPlrHeigt = _size.y * .5f;
  const float halfPlrWidth = _size.x * .52f;
  b2WorldManifold manifold;
  for (const auto& contact : touch) {
    contact->GetWorldManifold(&manifold);
    const int numPoints = contact->GetManifold()->pointCount;
    bool onTop = numPoints > 0;
    // If all contacts are below the player.
    for (int j = 0; j < numPoints; j++) {
      onTop &= (manifold.points[j].y < pos.y - halfPlrHeigt);
    }
    if (onTop) {
      return true;
    }
  }

  return false;
}

void EnemyPhysicsComponent::update(double dt) {

  const auto ppos = _parent->getPosition();
  if (ppos.x > gameWidth || ppos.x < 0) {
      _parent->setForDelete();
  }
  if (ppos.y > gameHeight ) {
      _parent->setForDelete();
  }
  PhysicsComponent::update(dt);
}

EnemyPhysicsComponent::EnemyPhysicsComponent(Entity* p,
                                               const Vector2f& size)
    : PhysicsComponent(p, true, size) {
  _size = sv2_to_bv2(size, true);
  _maxVelocity = Vector2f(200.f, 400.f);
  _groundspeed = 30.f;
  _grounded = false;
  _body->SetSleepingAllowed(false);
  _body->SetFixedRotation(true);
  //Bullet items have higher-res collision detection
  _body->SetBullet(true);
  setSensor(false);
}
