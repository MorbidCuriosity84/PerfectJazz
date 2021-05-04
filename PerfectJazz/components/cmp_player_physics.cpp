#include "cmp_player_physics.h"
#include "system_physics.h"
#include <SFML/Window/Keyboard.hpp>
#include "../player/cmp_player.h"
#include "../services/detecting_keys.h"

using namespace std;
using namespace sf;
using namespace Physics;
double playerCMPTimer;

// Updates the player physics component, allowing the user to set the direction of the entity
void PlayerPhysicsComponent::update(double dt) {

	const auto pos = _parent->getPosition();
	// Sets a reference to the parent's player component
	auto playerCMP = _parent->GetCompatibleComponent<PlayerComponent>()[0];
	// Sets the multiplier to be used for the movement speed, to take into consideration the upgrades done to the fly speed
	float multiplier = playerCMP->_playerSettings.flySpeed * 0.1f * playerCMP->_playerSettings.flySpeedUpgradeCount;
	float _flySpeed = playerCMP->_playerSettings.flySpeed + multiplier;

	{
		// Sets the boundaries for the player's movements. Once it gets to the boundaries, the velocity it's set to 0
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
		// Checks the key input and performs a change in the velocity to move the player in that direction
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
		// Checks the key input and performs a change in the velocity to move the player in that direction
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

		// If space key is pressed, change the rotation of the sprite and the bullet direction,
		// so the player can shoot backwards
		if (Keyboard::isKeyPressed(Keyboard::Space) && !detectingKeys.keySpace) {
			playerCMP->weaponCMP->_bSettings.direction *= -1.f;
			if (playerCMP->spriteCMP->getSprite().getRotation() != 180.f) {
				playerCMP->spriteCMP->getSprite().setRotation(180.f);
			}
			else { playerCMP->spriteCMP->getSprite().setRotation(0.f); }
		}
	}

	detectingKeys.detectingKeys();

	// If the player is glitched out of the screen, it get's teleported back to the center of the view
	if ((pos.x > mainView.getSize().x || pos.x < 0 || pos.y > mainView.getSize().y || pos.y < 0)) {
		playerCMP->setPlayerAlive(false);
		teleport((Vector2f((round)(mainView.getSize().x / 2), mainView.getSize().y - mainView.getSize().y / 10)));
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
	//Put player facing forward if the level is finished
	if (Engine::isLevelComplete) {
		if (playerCMP->spriteCMP->getSprite().getRotation() == 180.f) {
			playerCMP->spriteCMP->getSprite().setRotation(0.f);
			playerCMP->weaponCMP->_bSettings.direction *= -1.f;
		}
	}
	// Updates the physics component
	PhysicsComponent::update(dt);
}
// Constructor for the player physics component. It sets the player's max velocity and body settings
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
	// Sets a reference to the parent's sprite component
	playerSpriteCMP = player->GetCompatibleComponent<SpriteComponent>()[0];
}
// Gets the player's direction
std::string PlayerPhysicsComponent::GetDirection() {
	return _direction;
}
// Sets the player fly speed
void PlayerPhysicsComponent::setFlySpeed(int speed) {
	auto playerCMP = player->GetCompatibleComponent<PlayerComponent>()[0].get()->_playerSettings.flySpeed = speed;
}