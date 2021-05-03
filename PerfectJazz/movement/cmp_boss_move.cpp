#include "cmp_boss_move.h"

BossMovement::BossMovement(Entity* p, sf::Vector2f vel, Vector2f initPos, bool l) : MovementComponent(p, vel, initPos, l)
{
	accumulation = 0.0;
	stopped = false;
}

void BossMovement::update(double dt)
{
	accumulation += dt;
	if (!stopped) {
		if (_parent->getPosition().y > mainView.getCenter().y) {
			parentPhysics->setVelocity(Vector2f(0.f, 0.f));
			parentPhysics->getBody()->ApplyLinearImpulseToCenter(b2Vec2(1.f, 0.f), true);
			stopped = true;
		}
	}
	else {
		if (_parent->getPosition().x < mainView.getSize().x / 10) {
			parentPhysics->getBody()->ApplyLinearImpulseToCenter(b2Vec2(1.f,0.f), true);
		}
		if (_parent->getPosition().x > mainView.getSize().x - mainView.getSize().x / 10) {
			parentPhysics->getBody()->ApplyLinearImpulseToCenter(b2Vec2(-1.f, 0.f), true);
		}
		if (_parent->getPosition().y > mainView.getSize().x / 10) {
			parentPhysics->getBody()->ApplyLinearImpulseToCenter(b2Vec2(0.f, 1.f), true);
		}
		if (_parent->getPosition().y < mainView.getSize().y - mainView.getSize().x / 10) {
			parentPhysics->getBody()->ApplyLinearImpulseToCenter(b2Vec2(0.f, -1.f), true);
		}
	}
}
