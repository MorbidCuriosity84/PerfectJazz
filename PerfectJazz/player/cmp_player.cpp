#include "cmp_player.h"
#include <SFML/Graphics/CircleShape.hpp>
#include "../settings/settings_holder.h"

using namespace std;
using namespace sf;

void PlayerComponent::Load() {

	player->setPosition((Vector2f((round)(mainView.getSize().x / 2), mainView.getSize().y - mainView.getSize().y/6)));
	damageCMP = player->addComponent<DamageComponent>(_playerSettings.damage);
	weaponCMP = player->addComponent<WeaponComponent>(_weaponSettings, _bulletSettings, _bulletTextureHelper);
	player->addTag("player");
	_playerTextureHelper.spriteTexture.get()->loadFromFile(_playerTextureHelper.spriteFilename);


	spriteCMP = player->addComponent<SpriteComponent>();
	spriteCMP.get()->loadTexture(_playerTextureHelper, _playerSettings.scale, _playerSettings.angle);
	physicsCMP = player->addComponent<PlayerPhysicsComponent>(spriteCMP->getSprite().getGlobalBounds().getSize());
	physicsCMP.get()->setCategory(_playerSettings.category);

	hpCMP = player->addComponent<HPComponent>(_playerSettings.scene, _playerSettings.hp, _playerSettings.maxHP);
	hpCMP->loadHP();
	hpCMP.get()->setVisible(_playerSettings.hpVisible);
	hpCMP->setSpriteColour(Color::Red);
	hpCMP->setTextColour(Color::White);
	hpCMP->setScale(Vector2f(1.f, 0.8f));
}

void PlayerComponent::revive() {

	setPlayerAlive(true);
	_gracePeriod = true;
	physicsCMP->setCategory(NO_COLLIDE);
	physicsCMP->teleport((Vector2f((round)(mainView.getSize().x / 2), mainView.getSize().y - mainView.getSize().y / 6)));
	hpCMP->setHP(_playerSettings.maxHP);
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
			physicsCMP->setCategory(PLAYER_BODY);
			_gracePeriod = false;
			setPlayerAlive(true);
		}
	}

	if (player->isAlive()) {

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

		if (hpCMP->getHP() <= 0) {
			setPlayerAlive(false);
			if (_playerSettings.lifes <= 0) { _gracePeriod = false; }
		}
	}
}

void PlayerComponent::setPlayerAlive(bool b) {

	if (!b) {
		hpCMP->setHP(0);
		_playerSettings.lifes--;
		_gracePeriod = true;
		physicsCMP->impulse(Vector2f(0.f, 0.f));
		physicsCMP->setVelocity(Vector2f(0.f, 0.f));
		_gracePeriodTimer = 0;
		_visibilityTimer = 0;
	}

	player->setVisible(b);
	player->setAlive(b);
	physicsCMP->getBody()->SetActive(b);

}

void PlayerComponent::setFlySpeedUpgradeState(int state) {
	if (state <= _maxUpdate) { _playerSettings.flySpeedUpgradeCount = state; }
}
int PlayerComponent::getFlySpeedUpgradeState() { return _playerSettings.flySpeedUpgradeCount; }

int PlayerComponent::getDamageUpgradeState() { return weaponCMP->_bSettings.damageUpgradeCount; }
void PlayerComponent::setDamageUpgradeState(int state) {
	if (state <= _maxUpdate) { weaponCMP->_bSettings.damageUpgradeCount = state; }
}

int PlayerComponent::getFireRateUpgradeState() { return weaponCMP->_wSettings.firerateUpgradeCount; }
void PlayerComponent::setFireRateUpgradeState(int state) {
	if (state <= _maxUpdate) { weaponCMP->_wSettings.firerateUpgradeCount = state; }
}

int PlayerComponent::getBulletNumberUpgradeState() { return weaponCMP->_wSettings.numBulletsUpgradeCount; }
void PlayerComponent::setBulletNumberUpgradeState(int state) {
	if (state <= _maxUpdate) { weaponCMP->_wSettings.numBullets = state; weaponCMP->_wSettings.numBulletsUpgradeCount = state; }
}

int PlayerComponent::getPlayerLifes() { return _playerSettings.lifes; }
void PlayerComponent::setPlayerLifes(int life) {
	if (life <= _playerSettings.maxLifes) { _playerSettings.lifes = life; }
}

void PlayerComponent::setMaxUpdate(int max) { _maxUpdate = max; }
int PlayerComponent::getMaxUpdate() { return _maxUpdate; }

void PlayerComponent::setMaxLifes(int max) { _playerSettings.maxLifes = max; }
int PlayerComponent::getShoppingCoins() {
	return _playerSettings.shopPoints;
}
void PlayerComponent::setShoppingCoins(int coins) {
	_playerSettings.shopPoints = coins;
}
int PlayerComponent::getScorePoints() {
	return _playerSettings.score;
}

int PlayerComponent::getMaxLifes() { return _playerSettings.maxLifes; }

PlayerComponent::PlayerComponent(Entity* p, textureSettings playerTextureHelper, textureSettings bulletTextureHelper, playerSettings playerSettings, weaponSettings weaponSettings, bulletSettings bulletSettings)
	: Component(p), _playerTextureHelper(playerTextureHelper), _bulletTextureHelper(bulletTextureHelper), _playerSettings(playerSettings), _weaponSettings(weaponSettings), _bulletSettings(bulletSettings), _gracePeriod(false), _gracePeriodTimer(0), _visibilityTimer(0), _maxUpdate(5) {
	Load();
	colHelp.damageCMP = damageCMP.get();
	colHelp.hpCMP = hpCMP.get();
	colHelp.isMissileRadar = false;
	colHelp.missileCMP = nullptr;

	physicsCMP->getBody()->SetUserData(&colHelp);
}

void PlayerComponent::clonePlayer(shared_ptr<Entity> pl, Scene* target)
{
	auto oldCMP = pl->GetCompatibleComponent<PlayerComponent>()[0];
	auto wep = pl->GetCompatibleComponent<WeaponComponent>()[0];
	auto hp = pl->GetCompatibleComponent<HPComponent>()[0];
	SettingsHolder::pSettings.flySpeed = oldCMP->_playerSettings.flySpeed;
	SettingsHolder::pSettings.flySpeedUpgradeCount = oldCMP->_playerSettings.flySpeedUpgradeCount;
	SettingsHolder::pSettings.hp = hp->getHP();
	SettingsHolder::pSettings.maxHP = hp->getMaxHP();
	SettingsHolder::wSettings = wep->_wSettings;
	SettingsHolder::bSettings = wep->_bSettings;
	SettingsHolder::pTexHelper = oldCMP->_playerTextureHelper;
	SettingsHolder::bTexHelper = oldCMP->_bulletTextureHelper;
	//auto newPCMP = en->addComponent<PlayerComponent>(oldCMP->_playerTextureHelper, oldCMP->_bulletTextureHelper, oldCMP->_playerSettings, oldCMP->_weaponSettings, oldCMP->_bulletSettings);
}