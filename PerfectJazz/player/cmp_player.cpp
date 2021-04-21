#include "cmp_player.h"
#include <thread>
#include "ecm.h"
#include <future>
#include <fstream>
#include <iostream>
#include "../components/cmp_sprite.h"
#include "../components/cmp_player_physics.h"

using namespace std;
using namespace sf;

void PlayerComponent::Load() {
	player->setPosition((Vector2f((round)(mainView.getSize().x / 2), mainView.getSize().y - 100.f)));
	damageCMP = player->addComponent<DamageComponent>(_playerSettings.damage);
	weaponCMP = player->addComponent<WeaponComponent>(_weaponSettings, _bulletSettings, _bulletTextureHelper);
	player->addTag("player");
	_playerTextureHelper.spriteTexture.get()->loadFromFile(_playerTextureHelper.spriteFilename);

	spriteCMP = player->addComponent<SpriteComponent>();
	spriteCMP.get()->loadTexture(_playerTextureHelper, _playerSettings.scale, _playerSettings.angle);
	physicsCMP = player->addComponent<PlayerPhysicsComponent>(spriteCMP->getSprite().getGlobalBounds().getSize());
	physicsCMP.get()->setCategory(_playerSettings.category);

	hpCMP = player->addComponent<HPComponent>(_playerSettings.scene, _playerSettings.hp);
	hpCMP->loadHP();
	hpCMP.get()->setVisible(_playerSettings.hpVisible);
	hpCMP->setSpriteColour(Color::Red);
	hpCMP->setTextColour(Color::White);
	hpCMP->setScale(Vector2f(1.f, 0.8f));

	physicsCMP.get()->getBody()->SetUserData(hpCMP.get());
}

void PlayerComponent::revive() {
	
	physicsCMP->teleport((Vector2f((round)(mainView.getSize().x / 2), mainView.getSize().y - 100.f)));	
	setPlayerAlive(true);
	player->setAlive(true);
	hpCMP->setHP(_playerSettings.maxHP);

}

void PlayerComponent::update(double dt) {

	_playerTextureHelper.spriteTimer += dt;


	if (player->isAlive()) {
		//auto pPhysics = static_cast<PlayerPhysicsComponent>(*physicsCMP);
		//auto pSprite = player->GetCompatibleComponent<SpriteComponent>();

		if (_playerTextureHelper.spriteTimer > 0.1f) {

			//Check if the loaded sprite is the bottom, if so, load the top. And viceversa
			if (_playerTextureHelper.spriteRectangle.get()->top == _playerTextureHelper.spriteTexture.get()->getSize().y / 2) { _playerTextureHelper.spriteRectangle.get()->top = 0; }
			else { _playerTextureHelper.spriteRectangle.get()->top = _playerTextureHelper.spriteTexture.get()->getSize().y / _playerTextureHelper.spriteRows; }

			//Check if it's loaded the right sprite for the movement
			if (physicsCMP->GetDirection() == "right") {
				if (_playerTextureHelper.spriteTimer > 0.2f) {
					_playerTextureHelper.spriteRectangle.get()->left = (_playerTextureHelper.spriteTexture.get()->getSize().x / _playerTextureHelper.spriteCols) * 4;
				}
				else { _playerTextureHelper.spriteRectangle.get()->left = (_playerTextureHelper.spriteTexture.get()->getSize().x / _playerTextureHelper.spriteCols) * 3; }
			}
			if (physicsCMP->GetDirection() == "left") {
				if (_playerTextureHelper.spriteTimer > 0.2f) {
					_playerTextureHelper.spriteRectangle.get()->left = (_playerTextureHelper.spriteTexture.get()->getSize().x / _playerTextureHelper.spriteCols) * 0;
				}
				else { _playerTextureHelper.spriteRectangle.get()->left = (_playerTextureHelper.spriteTexture.get()->getSize().x / _playerTextureHelper.spriteCols) * 1; }
			}
			if (physicsCMP->GetDirection() == "none") {
				_playerTextureHelper.spriteRectangle.get()->left = (_playerTextureHelper.spriteTexture.get()->getSize().x / _playerTextureHelper.spriteCols) * 2;
				_playerTextureHelper.spriteTimer = 0;
			}
			spriteCMP->getSprite().setTextureRect(*_playerTextureHelper.spriteRectangle.get());
		}
		spriteCMP->getSprite().setPosition(player->getPosition());

		_playerSettings.score++;
		_playerSettings.shopPoints++;

		//auto hp = player->GetCompatibleComponent<HPComponent>()[0];

		if (hpCMP->getHP() <= 0) {
			hpCMP->setHP(0);
			setPlayerAlive(false);
			_playerSettings.lifes--;
		}
	}
}

void PlayerComponent::setPlayerAlive(bool b) {	
	physicsCMP->getBody()->SetActive(b);
	physicsCMP->impulse(Vector2f(0.f, 0.f));
	physicsCMP->setVelocity(Vector2f(0.f, 0.f));
	player->setVisible(b);
	player->setAlive(b);
	_playerAlive = b;
}

PlayerComponent::PlayerComponent(Entity* p, textureSettings playerTextureHelper, textureSettings bulletTextureHelper, playerSettings playerSettings, weaponSettings weaponSettings, bulletSettings bulletSettings)
	: Component(p), _playerTextureHelper(playerTextureHelper), _bulletTextureHelper(bulletTextureHelper), _playerSettings(playerSettings), _weaponSettings(weaponSettings), _bulletSettings(bulletSettings), _playerAlive(true) {
}
