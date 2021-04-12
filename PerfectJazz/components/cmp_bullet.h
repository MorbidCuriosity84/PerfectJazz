#pragma once
#include "cmp_physics.h"
#include <ecm.h>

class BulletComponent : public Component {
protected:
  float _lifetime;
  float _damage;

public:
  void update(double dt) override;
  void render() override {}
  explicit BulletComponent(Entity* p, float damage = 50.f, float lifetime = 3.f);
  BulletComponent() = delete;

  void setDamage(float damage);
  float getDamage() const;  
};
