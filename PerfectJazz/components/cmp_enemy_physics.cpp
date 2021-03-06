#include "cmp_enemy_physics.h"
#include <system_physics.h>

using namespace std;
using namespace sf;
using namespace Physics;

// Updates the enemy physics component by calling the physics component update
void EnemyPhysicsComponent::update(double dt) {
  PhysicsComponent::update(dt);
}
// Constructor for the enemy physics component
// Defines the settings for the body that is used for collisions
EnemyPhysicsComponent::EnemyPhysicsComponent(Entity* p, const Vector2f& size)
    : PhysicsComponent(p, true, size) {
  _size = sv2_to_bv2(size, true);
  _maxVelocity = Vector2f(200.f, 400.f);
  _flySpeed = 30.f;
  _body->SetSleepingAllowed(false);
  _body->SetFixedRotation(true);
  //Bullet items have higher-res collision detection
  _body->SetBullet(true);
  setSensor(false);
}
