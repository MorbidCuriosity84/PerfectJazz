#include "cmp_player_physics.h"
#include "system_physics.h"
#include <SFML/Window/Keyboard.hpp>
#include "../player/cmp_player.h"

using namespace std;
using namespace sf;
using namespace Physics;
double playerCMPTimer;

void PlayerPhysicsComponent::update(double dt) {

	const auto pos = _parent->getPosition();
	auto playerCMP = _parent->GetCompatibleComponent<PlayerComponent>()[0];
	float multiplier = dt * playerCMP->_playerSettings.flySpeed * (0.1f * playerCMP->_playerSettings.flySpeedUpgradeCount);
	auto _flySpeed = playerCMP->_playerSettings.flySpeed + multiplier;

	{
		//CARLOS TO-DO fix movement. When the framerate is locked, the impulse feels different
		//check the collision when diagonally on the borders

		//The _flySpeed * 2 makes the player not to stick when it goes to a side, so it can fly away easily
		if (pos.x < 0 + playerSpriteCMP->getSprite().getTextureRect().width / 2) {
			setVelocity(Vector2f(0.f, getVelocity().y * 0.98f));
			impulse({ ((float)dt * _flySpeed * 2), 0 });
		}
		if (pos.x >= mainView.getSize().x - playerSpriteCMP->getSprite().getTextureRect().width / 2) {
			setVelocity(Vector2f(0.f, getVelocity().y * 0.98f));
			impulse({ -((float)dt * _flySpeed * 2), 0 });
		}
		if (pos.y <= playerSpriteCMP->getSprite().getTextureRect().height / 2) {
			setVelocity(Vector2f(getVelocity().x * 0.98f, 0.f));
			impulse({ 0, (float)(dt * _flySpeed * 2) });
		}
		if (pos.y >= mainView.getSize().y - playerSpriteCMP->getSprite().getTextureRect().height / 2) {
			setVelocity(Vector2f(getVelocity().x * 0.98f, 0.f));
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
					impulse({ (float)(dt * _flySpeed), 0 });
				_direction = "right";
			}
			else {
				if (getVelocity().x > -_maxVelocity.x)
					impulse({ -(float)(dt * _flySpeed), 0 });
				_direction = "left";
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::Up) ||
			Keyboard::isKeyPressed(Keyboard::Down)) {
			// Moving Either Up or Down
			if (Keyboard::isKeyPressed(Keyboard::Up)) {
				if (getVelocity().y < _maxVelocity.y)
					impulse({ 0, -(float)(dt * _flySpeed) });
			}
			else {
				if (getVelocity().y > -_maxVelocity.y)
					impulse({ 0, (float)(dt * _flySpeed) });
			}
		}
	}

	if ((pos.x > gameWidth || pos.x < 0 || pos.y > gameHeight || pos.y < 0)) {
		playerCMP->setPlayerAlive(false);
		teleport((Vector2f((round)(mainView.getSize().x / 2), mainView.getSize().y - 100.f)));
	}

	playerCMPTimer += dt;
	if (playerCMPTimer > 0.01) {
		// Damp velocity
		dampen({ 0.95f, 0.95f });

		// Clamp velocity
		auto v = getVelocity();
		v.x = copysign(min(abs(v.x), _maxVelocity.x), v.x);
		v.y = copysign(min(abs(v.y), _maxVelocity.y), v.y);
		setVelocity(v);

		playerCMPTimer = 0.f;
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
	playerCMPTimer = 0;
	playerSpriteCMP = player->GetCompatibleComponent<SpriteComponent>()[0];
}

std::string PlayerPhysicsComponent::GetDirection() {
	return _direction;
}

void PlayerPhysicsComponent::setFlySpeed(int speed) {
	auto playerCMP = player->GetCompatibleComponent<PlayerComponent>()[0];
	playerCMP->_playerSettings.flySpeed = speed;
}