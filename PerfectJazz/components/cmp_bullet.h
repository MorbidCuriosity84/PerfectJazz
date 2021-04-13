#pragma once
#include "cmp_physics.h"
#include <ecm.h>
#include "cmp_damage.h"

class BulletComponent : public Component {
protected:
  float _lifetime;
  shared_ptr<DamageComponent> _damage;

public:
  void update(double dt) override;
  void render() override {}
  explicit BulletComponent(Entity* p, shared_ptr<DamageComponent> _damage, float lifetime);
  BulletComponent() = delete;

  void setDamage(shared_ptr<DamageComponent> damage);
  shared_ptr<DamageComponent> getDamage() const;
};
