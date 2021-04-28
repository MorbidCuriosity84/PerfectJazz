#include "cmp_powerup.h"
#include "../randomNumber.h"
#include "maths.h"
#include "../game.h"
#include "../player/cmp_player.h"

using namespace std;
using namespace sf;

void PowerupComponent::deployPowerup() {
	
	_powerupTextureHelper.spriteTexture.get()->loadFromFile(_powerupTextureHelper.spriteFilename);
	powerupSpriteCMP = _parent->addComponent<SpriteComponent>();
	powerupSpriteCMP.get()->loadTexture(_powerupTextureHelper, { _powerupSettings.spriteScale }, 0);
	damageCMP = _parent->addComponent<DamageComponent>(_powerupSettings.damage);
	physicsCMP = _parent->addComponent<PhysicsComponent>(true, powerupSpriteCMP->getSprite().getLocalBounds().getSize());
	
	hpCMP = _parent->addComponent<HPComponent>(_powerupSettings.scene, 1, 1);
	hpCMP->loadHP();
	hpCMP.get()->setVisible(false);

	physicsCMP->getBody()->SetBullet(true);
	physicsCMP->setSensor(true);
	physicsCMP->setVelocity(_powerupSettings.velocity * _powerupSettings.direction);
	physicsCMP->setCategory(_powerupSettings.category);

	sound = _powerupSettings.sound;
}

void PowerupComponent::update(double dt) {
	//if parent is of type coin_pwu
	if (_parent->getTags().find("coin_pwu") != _parent->getTags().end()) {
		_powerupTextureHelper.spriteTimer += dt;
		if (_powerupTextureHelper.spriteTimer < 0.1) {
			_powerupTextureHelper.spriteRectangle.get()->left = (_powerupTextureHelper.spriteTexture.get()->getSize().x / _powerupTextureHelper.spriteCols) * 0;
		}
		if (_powerupTextureHelper.spriteTimer >= 0.1 && _powerupTextureHelper.spriteTimer < 0.2) {
			_powerupTextureHelper.spriteRectangle.get()->left = (_powerupTextureHelper.spriteTexture.get()->getSize().x / _powerupTextureHelper.spriteCols) * 1;
		}
		if (_powerupTextureHelper.spriteTimer >= 0.2 && _powerupTextureHelper.spriteTimer < 0.3) {
			_powerupTextureHelper.spriteRectangle.get()->left = (_powerupTextureHelper.spriteTexture.get()->getSize().x / _powerupTextureHelper.spriteCols) * 2;
		}
		if (_powerupTextureHelper.spriteTimer >= 0.3 && _powerupTextureHelper.spriteTimer < 0.4) {
			_powerupTextureHelper.spriteRectangle.get()->left = (_powerupTextureHelper.spriteTexture.get()->getSize().x / _powerupTextureHelper.spriteCols) * 3;
		}
		if (_powerupTextureHelper.spriteTimer >= 0.4 && _powerupTextureHelper.spriteTimer < 0.5) {
			_powerupTextureHelper.spriteRectangle.get()->left = (_powerupTextureHelper.spriteTexture.get()->getSize().x / _powerupTextureHelper.spriteCols) * 4;
		}
		if (_powerupTextureHelper.spriteTimer >= 0.5) {
			_powerupTextureHelper.spriteTimer = 0.0;
		}

		powerupSpriteCMP->getSprite().setTextureRect(*_powerupTextureHelper.spriteRectangle.get());
	}

	if (hpCMP->getHP() <= 0) {
		_parent->setAlive(false);
		_parent->setVisible(false);
		physicsCMP->getBody()->SetActive(false);
		physicsCMP->getBody()->SetUserData(nullptr);
		_parent->setPosition(Vector2f(-100.f, -100.f));
		powerupAction();
		sounds[_powerupSettings.sound].play();
	}
	if (_parent->getPosition().y > _parent->getView().getSize().y) {
		_parent->setAlive(false);
		_parent->setVisible(false);
		physicsCMP->getBody()->SetActive(false);
		physicsCMP->getBody()->SetUserData(nullptr);
		_parent->setPosition(Vector2f(-100.f, -100.f));
	}

}

void PowerupComponent::powerupAction() {
	auto playerCMP = player->GetCompatibleComponent<PlayerComponent>()[0];
	physicsCMP->teleport(Vector2f(-500.f, -500.f));
	hpCMP->setHP(1);

	if (_parent->getTags().find("hp_pwu") != _parent->getTags().end()) {
		int maxHP = playerCMP->_playerSettings.maxHP;
		int current = playerCMP->hpCMP->getHP();
		playerCMP->hpCMP->setHP(current + maxHP/8);
	}
	if (_parent->getTags().find("damage_pwu") != _parent->getTags().end()) {
		cout << "before: " << playerCMP->weaponCMP->_bSettings.damageUpgradeCount << ": damage upgrade" << endl;
		int current = playerCMP->getDamageUpgradeState();
		playerCMP->setDamageUpgradeState(current + 1);
		cout << "after: " << playerCMP->weaponCMP->_bSettings.damageUpgradeCount << ": damage upgrade " << endl;
	}
	if (_parent->getTags().find("firerate_pwu") != _parent->getTags().end()) {
		cout << "before: " << playerCMP->weaponCMP->_wSettings.firerateUpgradeCount << ": firetime upgrade" << endl;
		int current = playerCMP->getFireRateUpgradeState();
		playerCMP->setFireRateUpgradeState(current + 1);
		cout << "after: " << playerCMP->weaponCMP->_wSettings.firerateUpgradeCount << ": firetime upgrade" << endl;
	}
	if (_parent->getTags().find("bullet_num_pwu") != _parent->getTags().end()) {
		cout << "before: " << playerCMP->weaponCMP->_wSettings.numBulletsUpgradeCount << ": bullet num upgrade" << endl;
		int current = playerCMP->getBulletNumberUpgradeState();
		playerCMP->setBulletNumberUpgradeState(current + 1);
		cout << "after: " << playerCMP->weaponCMP->_wSettings.numBulletsUpgradeCount << ": bullet num upgrade" << endl;
	}
	if (_parent->getTags().find("player_movement_pwu") != _parent->getTags().end()) {
		cout << "before: " << playerCMP->_playerSettings.flySpeed << ": fly speed - ";
		cout << playerCMP->_playerSettings.flySpeedUpgradeCount << ": fly upgrade" << endl;
		int current = playerCMP->getFlySpeedUpgradeState();
		playerCMP->setFlySpeedUpgradeState(current + 1);
		cout << "after: " << playerCMP->_playerSettings.flySpeedUpgradeCount << ": fly upgrade" << endl;
	}
	if (_parent->getTags().find("coin_pwu") != _parent->getTags().end()) {
		cout << "before: " << playerCMP->_playerSettings.shopPoints << ": coins - ";
		int current = playerCMP->_playerSettings.shopPoints;
		playerCMP->_playerSettings.shopPoints = current + 10;
		cout << "after: " << playerCMP->_playerSettings.shopPoints << ": coins - " << endl;

	}
}

PowerupComponent::PowerupComponent(Entity* p, textureSettings powerupTextureHelper, powerupSettings powerupSettings) : Component(p), _powerupTextureHelper(powerupTextureHelper), _powerupSettings(powerupSettings){
	deployPowerup();
	pow_colHelp.damageCMP = damageCMP.get();
	pow_colHelp.hpCMP = hpCMP.get();
	pow_colHelp.isPowerup = true;
	pow_colHelp.isMissile = false;
	pow_colHelp.missileCMP = nullptr;
	_parent->addTag("powerup");
	physicsCMP->getBody()->SetUserData(&pow_colHelp);
}