#include "cmp_hurt_player.h"
#include <engine.h>

using namespace std;
using namespace sf;

void HurtComponent::update(double dt) {
  /*if (auto pl = _player.lock()) {
    if (length(pl->getPosition() - _parent->getPosition()) < 25.0) {
        pl->setVisible(false);
        pl->setAlive(false);
        pl->setPosition({ -50.f, -50.f });
      _parent->setVisible(false);
      _parent->setAlive(false);
      _parent->setPosition({ -50.f, -50.f });
    }
  }  */

    auto cList = _parent->GetCompatibleComponent<PhysicsComponent>();
    auto body = cList[0].get()->getBody();
    auto f = body->GetFixtureList();    
}

HurtComponent::HurtComponent(Entity* p)
    : Component(p), _player(_parent->scene->ents.find("player")[0]) {}
