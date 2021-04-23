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
		//The _flySpeed * 2 makes the player not to stick when it goes to a side, so it 
		//can fly away easily
		if (pos.x < 0 + playerSpriteCMP->getSprite().getTextureRect().width / 2) {
			setVelocity(Vector2f(0.f, getVelocity().y));
			impulse({ ((float)dt * _flySpeed * 2), 0 });
		}
		if (pos.x >= mainView.getSize().x - playerSpriteCMP->getSprite().getTextureRect().width / 2) {
			setVelocity(Vector2f(0.f, getVelocity().y));
			impulse({ -((float)dt * _flySpeed * 2), 0 });
		}
		if (pos.y <= playerSpriteCMP->getSprite().getTextureRect().height / 2) {
			setVelocity(Vector2f(getVelocity().x, 0.f));
			impulse({ 0, (float)(dt * _flySpeed * 2) });
		}
		if (pos.y >= mainView.getSize().y - playerSpriteCMP->getSprite().getTextureRect().height / 2) {
			setVelocity(Vector2f(getVelocity().x, 0.f));
			impulse({ 0, -(float)(dt * _flySpeed * 2) });
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

	if ((pos.x > gameWidth || pos.x < 0 || pos.y > gameHeight || pos.y < 0)) {
		playerCMP->setPlayerAlive(false);
		teleport((Vector2f((round)(mainView.getSize().x / 2), mainView.getSize().y - 100.f)));
	}

	//dampen({ 0.994f, 0.992f });

	// Clamp velocity.
	auto v = getVelocity();
	v.x = copysign(min(abs(v.x), _maxVelocity.x), v.x);
	v.y = copysign(min(abs(v.y), _maxVelocity.y), v.y);
	setVelocity(v);

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