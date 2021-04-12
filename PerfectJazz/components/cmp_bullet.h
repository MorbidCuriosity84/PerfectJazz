#pragma once
#include "cmp_physics.h"
#include <ecm.h>

class BulletComponent : public Component {
protected:
  float _lifetime;
  uint16 _damage;

public:
  void update(double dt) override;
  void render() override {}
  explicit BulletComponent(Entity* p, uint16 damage = 50.f, float lifetime = 3.f);
  BulletComponent() = delete;

  void setDamage(uint16 damage);
  uint16 getDamage() const;  
};
