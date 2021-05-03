#include "cmp_player.h"
#include <SFML/Graphics/CircleShape.hpp>
#include "../settings/settings_holder.h"
#include "../services/load_save_game.h"

using namespace std;
using namespace sf;

//Loads a player component,that helps to add a damage component, weapon component, sprite component, 
//player physics component, and HP component to the player.
void PlayerComponent::Load() {
	player->setPosition((Vector2f((round)(mainView.getSize().x / 2), mainView.getSize().y - mainView.getSize().y / 6)));
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

//Brings the player back to live, giving it a period of grace, during 
//which cannot be hit. Resets the hp to its maximum and teleport the player backs to the middle of the screen
void PlayerComponent::revive() {
	setPlayerAlive(true);
	_gracePeriod = true;
	physicsCMP->setCategory(NO_COLLIDE);
	physicsCMP->teleport((Vector2f((round)(mainView.getSize().x / 2), mainView.getSize().y - mainView.getSize().y / 6)));
	hpCMP->setHP(hpCMP->getMaxHP());
	_playerSettings.maxHP = hpCMP->getMaxHP();
}

void PlayerComponent::update(double dt) {
	_playerTextureHelper.spriteTimer += dt;

	//If period of grace is on, players sprite flickers, to show inmunity
	if (_gracePeriod) {
		_gracePeriodTimer += dt;

		if (_gracePeriodTimer < 3.f) {
			_visibilityTimer += dt;
			if (_visibilityTimer >= 0.1f && _visibilityTimer < 0.2f) { player->setVisible(false); }
			if (_visibilityTimer >= 0.2f) { player->setVisible(true); _visibilityTimer = 0; }
		}
		//When the timer is higher or equal 3, the grace period finishes, and 
		//the player is set alive
		if (_gracePeriodTimer >= 3) {
			physicsCMP->setCategory(PLAYER_BODY);
			_gracePeriod = false;
			setPlayerAlive(true);
		}
	}

	//If the player is alive, the sprites get updated
	if (player->isAlive()) {

		if (_playerTextureHelper.spriteTimer > 0.1f) {

			//Check if the loaded sprite is the bottom, if so, load the top. And viceversa
			if (_playerTextureHelper.spriteRectangle.get()->top == _playerTextureHelper.spriteTexture.get()->getSize().y / 2) { _playerTextureHelper.spriteRectangle.get()->top = 0; }
			else { _playerTextureHelper.spriteRectangle.get()->top = _playerTextureHelper.spriteTexture.get()->getSize().y / _playerTextureHelper.spriteRows; }

			//Check if it's loaded the right sprite for the movement and performs the sprite animation
			if (physicsCMP->GetDirection() == "right") {
				if (_playerTextureHelper.spriteTimer > 0.2f) {
					_playerTextureHelper.spriteRectangle.get()->left = (_playerTextureHelper.spriteTexture.get()->getSize().x / _playerTextureHelper.spriteCols) * 4;
				}
				else { _playerTextureHelper.spriteRectangle.get()->left = (_playerTextureHelper.spriteTexture.get()->getSize().x / _playerTextureHelper.spriteCols) * 3; }
			}
			//Check if it's loaded the left sprite for the movement and performs the sprite animation
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
		//Sets the sprite position to the players position
		spriteCMP->getSprite().setPosition(player->getPosition());

		//If the HP is equal or below 0, set the player not alive
		if (hpCMP->getHP() <= 0) {
			setPlayerAlive(false);
			//If the player has no lifes left, set period of grace to false
			if (_playerSettings.lifes <= 0) { _gracePeriod = false; }
		}
	}
}

//Sets the player current state to alive/not alive, visible/not visible, active/not active
//reducing the currents lifes by one if not alive, and setting the movement and impulse to 0.
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
//Gets the fly movement current upgrade level
int PlayerComponent::getFlySpeedUpgradeState() { return _playerSettings.flySpeedUpgradeCount; }
//Sets the fly movement upgrade level
void PlayerComponent::setFlySpeedUpgradeState(int state) {
	if (state <= _maxUpdate) { _playerSettings.flySpeedUpgradeCount = state; }
}
//Gets the damage upgrade current level
int PlayerComponent::getDamageUpgradeState() { return weaponCMP->_bSettings.damageUpgradeCount; }
//Sets the damage upgrade level
void PlayerComponent::setDamageUpgradeState(int state) {
	if (state <= _maxUpdate) { weaponCMP->_bSettings.damageUpgradeCount = state; }
}
//Gets the fire rate upgrade current level
int PlayerComponent::getFireRateUpgradeState() { return weaponCMP->_wSettings.firerateUpgradeCount; }
//Sets the fire rate upgrade level
void PlayerComponent::setFireRateUpgradeState(int state) {
	if (state <= _maxUpdate) { weaponCMP->_wSettings.firerateUpgradeCount = state; }
}
//Gets the number of bullets upgrade current level
int PlayerComponent::getBulletNumberUpgradeState() { return weaponCMP->_wSettings.numBulletsUpgradeCount; }
//Sets the number of bullets upgrade level
void PlayerComponent::setBulletNumberUpgradeState(int state) {
	if (state <= _maxUpdate) { weaponCMP->_wSettings.numBullets = state; weaponCMP->_wSettings.numBulletsUpgradeCount = state; }
}
//Gets the players lifes
int PlayerComponent::getPlayerLifes() { return _playerSettings.lifes; }
//Sets the players lifes
void PlayerComponent::setPlayerLifes(int life) {
	if (life <= _playerSettings.maxLifes) { _playerSettings.lifes = life; }
}
//Sets the max update level
void PlayerComponent::setMaxUpdate(int max) { _maxUpdate = max; }
//Gets the max update level
int PlayerComponent::getMaxUpdate() { return _maxUpdate; }
//Sets the max number of lifes
void PlayerComponent::setMaxLifes(int max) { _playerSettings.maxLifes = max; }
//Gets the current number of coins
int PlayerComponent::getShoppingCoins() {
	return _playerSettings.shopPoints;
}
//Sets the number of coins
void PlayerComponent::setShoppingCoins(int coins) {
	_playerSettings.shopPoints = coins;
}
//Gets the score points
int PlayerComponent::getScorePoints() {
	return _playerSettings.score;
}

//Constructor for PlayerComponent
//Sets initial values for the collision helper and assigns a body to the player component
PlayerComponent::PlayerComponent(Entity* p, textureSettings playerTextureHelper, textureSettings bulletTextureHelper, playerSettings playerSettings, weaponSettings weaponSettings, bulletSettings bulletSettings)
	: Component(p), _playerTextureHelper(playerTextureHelper), _bulletTextureHelper(bulletTextureHelper), _playerSettings(playerSettings), _weaponSettings(weaponSettings), _bulletSettings(bulletSettings), _gracePeriod(false), _gracePeriodTimer(0), _visibilityTimer(0), _maxUpdate(5) {
	Load();
	colHelp.damageCMP = damageCMP.get();
	colHelp.hpCMP = hpCMP.get();
	colHelp.isMissileRadar = false;
	colHelp.missileCMP = nullptr;

	physicsCMP->getBody()->SetUserData(&colHelp);
}
//Clones the player by updating the current settings
//with the ones stored on the SettingHolder
void PlayerComponent::clonePlayer(shared_ptr<Entity> pl) {
	auto oldCMP = pl->GetCompatibleComponent<PlayerComponent>()[0];
	auto wep = pl->GetCompatibleComponent<WeaponComponent>()[0];
	auto hp = pl->GetCompatibleComponent<HPComponent>()[0];

	if (!Engine::isLoading) {
		SettingsHolder::pSettings = oldCMP->_playerSettings;
		SettingsHolder::pSettings.flySpeed = oldCMP->_playerSettings.flySpeed;
		SettingsHolder::pSettings.flySpeedUpgradeCount = oldCMP->_playerSettings.flySpeedUpgradeCount;
		SettingsHolder::pSettings.hp = hp->getHP();
		SettingsHolder::pSettings.maxHP = hp->getMaxHP();
		SettingsHolder::wSettings = wep->_wSettings;
		SettingsHolder::bSettings = wep->_bSettings;
		SettingsHolder::pTexHelper = oldCMP->_playerTextureHelper;
		SettingsHolder::bTexHelper = oldCMP->_bulletTextureHelper;
	}
}