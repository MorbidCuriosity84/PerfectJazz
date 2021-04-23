#include "cmp_player_physics.h"
#include "system_physics.h"
#include <SFML/Window/Keyboard.hpp>
#include "../player/cmp_player.h"

using namespace std;
using namespace sf;
using namespace Physics;

void PlayerPhysicsComponent::update(double dt) {

	const auto pos = _parent->getPosition();
	auto playerCMP = _parent->GetCompatibleComponent<PlayerComponent>()[0];
	auto _flySpeed = playerCMP->_playerSettings.flySpeed;
	float multiplier = dt * _flySpeed * (0.1f * playerCMP->_playerSettings.flySpeedUpgradeCount);
	{
		if (pos.x <= playerSpriteCMP->getSprite().getTextureRect().width/2) {
			setVelocity(Vector2f(0.f, getVelocity().y));
			impulse({ (float)(dt * _flySpeed + multiplier), 0 });
		}
		if (pos.x >= mainView.getSize().x - playerSpriteCMP->getSprite().getTextureRect().width / 2) {
			setVelocity(Vector2f(0.f, getVelocity().y));
			impulse({ -((float)dt * _flySpeed + multiplier), 0 });
		}
		if (pos.y <= playerSpriteCMP->getSprite().getTextureRect().height / 2) {
			setVelocity(Vector2f(getVelocity().x, 0.f));
			impulse({ 0, (float)(dt * _flySpeed + multiplier) });
		}
		if (pos.y >= mainView.getSize().y - playerSpriteCMP->getSprite().getTextureRect().height / 2) {
			setVelocity(Vector2f(getVelocity().x, 0.f));
			impulse({ 0, -(float)(dt * _flySpeed + multiplier) });
		}
	}
	//Player movement
	{
		_direction = "none";

		if (Keyboard::isKeyPressed(Keyboard::Left) ||
			Keyboard::isKeyPressed(Keyboard::Right)) {
			// Moving Either Left or Right
			if (Keyboard::isKeyPressed(Keyboard::Right)) {
				if (getVelocity().x < _maxVelocity.x)
					impulse({ (float)(dt * _flySpeed + multiplier), 0 });
					_direction = "right";
			}
			else {
				if (getVelocity().x > -_maxVelocity.x)
					impulse({ -(float)(dt * _flySpeed + multiplier), 0 });
					_direction = "left";

			}
		}

		if (Keyboard::isKeyPressed(Keyboard::Up) ||
			Keyboard::isKeyPressed(Keyboard::Down)) {
			// Moving Either Up or Down
			if (Keyboard::isKeyPressed(Keyboard::Up)) {
				if (getVelocity().y < _maxVelocity.y)
					impulse({ 0, -(float)(dt * _flySpeed + multiplier) });
			}
			else {
				if (getVelocity().y > -_maxVelocity.y)
					impulse({ 0, (float)(dt * _flySpeed + multiplier) });
			}
		}
	}

	dampen({ 0.994f, 0.992f });

	// Clamp velocity.
	auto v = getVelocity();
	v.x = copysign(min(abs(v.x), _maxVelocity.x), v.x);
	v.y = copysign(min(abs(v.y), _maxVelocity.y), v.y);
	setVelocity(v);

	const auto ppos = _parent->getPosition();
	if (ppos.x > gameWidth || ppos.x < 0) {
		_parent->setForDelete();
	}
	if (ppos.y > gameHeight) {
		_parent->setForDelete();
	}

	PhysicsComponent::update(dt);
}

PlayerPhysicsComponent::PlayerPhysicsComponent(Entity* p,
	const Vector2f& size)
	: PhysicsComponent(p, true, size) {
	_size = sv2_to_bv2(size, true);
	_maxVelocity = Vector2f(300.f, 300.f);
	_body->SetSleepingAllowed(false);
	_body->SetFixedRotation(true);
	//Bullet items have higher-res collision detection
	_body->SetBullet(true);		
	playerSpriteCMP = player->GetCompatibleComponent<SpriteComponent>()[0];
}

std::string PlayerPhysicsComponent::GetDirection() {
	return _direction;
}

void PlayerPhysicsComponent::setFlySpeed(int speed) {
	auto playerCMP = player->GetCompatibleComponent<PlayerComponent>()[0];
	playerCMP->_playerSettings.flySpeed = speed;
}

