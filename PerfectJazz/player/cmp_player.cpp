#include "cmp_player.h"
#include <thread>
#include "ecm.h"
#include <future>
#include <fstream>
#include <iostream>
#include "../components/cmp_sprite.h"
#include "../components/cmp_player_physics.h"
#include "../components/cmp_text.h"

using namespace std;
using namespace sf;

void PlayerComponent::Load() {
	player->setPosition((Vector2f((round)(mainView.getSize().x / 2), mainView.getSize().y - 100.f)));
	player->addComponent<DamageComponent>(_playerSettings.damage);
	player->addComponent<WeaponComponent>(_weaponSettings, _bulletSettings, _bulletTextureHelper);
	player->addTag("enemies");
	_playerTextureHelper.spriteTexture.get()->loadFromFile(_playerTextureHelper.spriteFilename);

	auto s = player->addComponent<SpriteComponent>();
	s.get()->loadTexture(_playerTextureHelper, _playerSettings.scale, _playerSettings.angle);
	auto phys = player->addComponent<PlayerPhysicsComponent>(s->getSprite().getGlobalBounds().getSize());
	phys.get()->setCategory(_playerSettings.category);

	auto h = player->addComponent<HPComponent>(_playerSettings.scene, _playerSettings.hp);
	h->loadHP();
	h.get()->setVisible(_playerSettings.hpVisible);
	h->setSpriteColour(Color::Red);
	h->setTextColour(Color::White);
	h->setScale(Vector2f(1.f, 0.8f));
	phys.get()->getBody()->SetUserData(h.get());
}

void PlayerComponent::revive() {

	auto phy = player->GetCompatibleComponent<PlayerPhysicsComponent>()[0];
	phy->teleport((Vector2f((round)(mainView.getSize().x / 2), mainView.getSize().y - 100.f)));
	auto hp = player->GetCompatibleComponent<HPComponent>()[0];
	setPlayerAlive(true);
	_gracePeriod = true;
	phy->setCategory(NO_COLLIDE);
	hp->setHP(_playerSettings.maxHP);
}

void PlayerComponent::update(double dt) {

	_playerTextureHelper.spriteTimer += dt;

	if (_gracePeriod) {
		_gracePeriodTimer += dt;

		if (_gracePeriodTimer < 3.f) {
			_visibilityTimer += dt;
			if (_visibilityTimer >= 0.1f && _visibilityTimer < 0.2f) { player->setVisible(false); }
			if (_visibilityTimer >= 0.2f) { player->setVisible(true); _visibilityTimer = 0; }
		}

		if (_gracePeriodTimer >= 3) {
			auto phy = player->GetCompatibleComponent<PhysicsComponent>()[0];
			phy->setCategory(PLAYER_BODY);
			_gracePeriod = false;
			setPlayerAlive(true);
		}
	}

	if (player->isAlive()) {
		auto pPhysics = player->GetCompatibleComponent<PlayerPhysicsComponent>();
		auto pSprite = player->GetCompatibleComponent<SpriteComponent>();

		if (_playerTextureHelper.spriteTimer > 0.1f) {

			//Check if the loaded sprite is the bottom, if so, load the top. And viceversa
			if (_playerTextureHelper.spriteRectangle.get()->top == _playerTextureHelper.spriteTexture.get()->getSize().y / 2) { _playerTextureHelper.spriteRectangle.get()->top = 0; }
			else { _playerTextureHelper.spriteRectangle.get()->top = _playerTextureHelper.spriteTexture.get()->getSize().y / _playerTextureHelper.spriteRows; }

			//Check if it's loaded the right sprite for the movement
			if (pPhysics[0]->GetDirection() == "right") {
				if (_playerTextureHelper.spriteTimer > 0.2f) {
					_playerTextureHelper.spriteRectangle.get()->left = (_playerTextureHelper.spriteTexture.get()->getSize().x / _playerTextureHelper.spriteCols) * 4;
				}
				else { _playerTextureHelper.spriteRectangle.get()->left = (_playerTextureHelper.spriteTexture.get()->getSize().x / _playerTextureHelper.spriteCols) * 3; }
			}
			if (pPhysics[0]->GetDirection() == "left") {
				if (_playerTextureHelper.spriteTimer > 0.2f) {
					_playerTextureHelper.spriteRectangle.get()->left = (_playerTextureHelper.spriteTexture.get()->getSize().x / _playerTextureHelper.spriteCols) * 0;
				}
				else { _playerTextureHelper.spriteRectangle.get()->left = (_playerTextureHelper.spriteTexture.get()->getSize().x / _playerTextureHelper.spriteCols) * 1; }
			}
			if (pPhysics[0]->GetDirection() == "none") {
				_playerTextureHelper.spriteRectangle.get()->left = (_playerTextureHelper.spriteTexture.get()->getSize().x / _playerTextureHelper.spriteCols) * 2;
				_playerTextureHelper.spriteTimer = 0;
			}
			pSprite[0]->getSprite().setTextureRect(*_playerTextureHelper.spriteRectangle.get());
		}
		pSprite[0]->getSprite().setPosition(player->getPosition());

		_playerSettings.score++;
		_playerSettings.shopPoints++;

		auto hp = player->GetCompatibleComponent<HPComponent>()[0];

		if (hp->getHP() <= 0) {
			hp->setHP(0);
			setPlayerAlive(false);
			_playerSettings.lifes--;

			if (_playerSettings.lifes <= 0) {
				GameOver();
			}
		}
	}
}

void PlayerComponent::setPlayerAlive(bool b) {
	auto phy = player->GetCompatibleComponent<PhysicsComponent>()[0];
	phy->impulse(Vector2f(0.f, 0.f));
	phy->setVelocity(Vector2f(0.f, 0.f));
	player->setVisible(b);
	player->setAlive(b);
	phy->getBody()->SetActive(b);

	_gracePeriodTimer = 0;
	_visibilityTimer = 0;
}

void PlayerComponent::GameOver() {
	player->setAlive(true);
	auto t = player->addComponent<TextComponent>("GAME OVER");
	t->setFontSize(220u);
	t->_text.setColor(Color::White);
	t->_text.setOutlineColor(Color::White);
	t->_text.setOutlineThickness(2);
	t->setOrigin(Vector2f(100.f, 100.f));
}

PlayerComponent::PlayerComponent(Entity* p, textureSettings playerTextureHelper, textureSettings bulletTextureHelper, playerSettings playerSettings, weaponSettings weaponSettings, bulletSettings bulletSettings)
	: Component(p), _playerTextureHelper(playerTextureHelper), _bulletTextureHelper(bulletTextureHelper), _playerSettings(playerSettings), _weaponSettings(weaponSettings), _bulletSettings(bulletSettings), _gracePeriod(false), _gracePeriodTimer(0), _visibilityTimer(0) {
}
