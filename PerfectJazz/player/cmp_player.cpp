#include "cmp_player.h"

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
}

void PlayerComponent::revive() {

	physicsCMP->teleport((Vector2f((round)(mainView.getSize().x / 2), mainView.getSize().y - 100.f)));
	setPlayerAlive(true);
	_gracePeriod = true;
	physicsCMP->setCategory(NO_COLLIDE);
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

		if (hpCMP->getHP() <= 0) {
			hpCMP->setHP(0);
			setPlayerAlive(false);

			_playerSettings.lifes--;

			if (_playerSettings.lifes <= 0) {
				_gracePeriod = false;
				setPlayerAlive(false);
			}
		}
	}
}

void PlayerComponent::setPlayerAlive(bool b) {

	if (!b) {
		physicsCMP->impulse(Vector2f(0.f, 0.f));
		physicsCMP->setVelocity(Vector2f(0.f, 0.f));
	}

	player->setVisible(b);
	player->setAlive(b);
	physicsCMP->getBody()->SetActive(b);

	_gracePeriodTimer = 0;
	_visibilityTimer = 0;
}

void PlayerComponent::setFlySpeedUpgradeState(int state) {
	if (state <= _maxUpdate) {
		_playerSettings.flySpeedUpgradeCount = state;
	}
}
int PlayerComponent::getFlySpeedUpgradeState() { return _playerSettings.flySpeedUpgradeCount; }

int PlayerComponent::getDamageUpgradeState() { return weaponCMP->_bSettings.damageUpgradeCount; }
void PlayerComponent::setDamageUpgradeState(int state) {
	if (state <= _maxUpdate) {
		if (state > weaponCMP->_bSettings.damageUpgradeCount) {
			weaponCMP.get()->_bSettings.damage = weaponCMP->_bSettings.damage * (state * 0.2f);
		}
		if (state < weaponCMP->_bSettings.damageUpgradeCount) {
			weaponCMP.get()->_bSettings.damage = weaponCMP->_bSettings.damage / (state * 0.2f);
		}
		weaponCMP->_bSettings.damageUpgradeCount = state;
	}
}

int PlayerComponent::getFireRateUpgradeState() { return weaponCMP.get()->_wSettings.firerateUpgradeCount; }
void PlayerComponent::setFireRateUpgradeState(int state) {
	if (state <= _maxUpdate) {
		if (state > weaponCMP->_wSettings.firerateUpgradeCount) {
			weaponCMP.get()->_wSettings.fireTime = weaponCMP->_wSettings.fireTime * (state * 0.2f);
			weaponCMP.get()->_wSettings.firerateUpgradeCount = state;
		}
		if (state < weaponCMP->_wSettings.firerateUpgradeCount) {
			weaponCMP.get()->_wSettings.fireTime = weaponCMP->_wSettings.fireTime / (state * 0.2f);
			weaponCMP.get()->_wSettings.firerateUpgradeCount = state;
		}
	}
}

int PlayerComponent::getBulletNumberUpgradeState() { return weaponCMP.get()->_wSettings.numBulletsUpgradeCount; }
void PlayerComponent::setBulletNumberUpgradeState(int state) {
	if (state <= _maxUpdate) {
		if (state > weaponCMP->_wSettings.numBulletsUpgradeCount) {
			weaponCMP.get()->_wSettings.numBullets = state;
			weaponCMP.get()->_wSettings.numBulletsUpgradeCount = state;
		}
		if (state < weaponCMP->_wSettings.numBulletsUpgradeCount) {
			weaponCMP.get()->_wSettings.numBullets = state;
			weaponCMP.get()->_wSettings.numBulletsUpgradeCount = state;
		}
		weaponCMP.get()->_wSettings.numBulletsUpgradeCount = state;
	}
}

int PlayerComponent::getPlayerLifes() { return _playerSettings.lifes; }
void PlayerComponent::setPlayerLifes(int life) {
	if (life <= _playerSettings.maxLifes) {
		_playerSettings.lifes = life;
	}
}

void PlayerComponent::setMaxUpdate(int max) { _maxUpdate = max; }
int PlayerComponent::getMaxUpdate() { return _maxUpdate; }

void PlayerComponent::setMaxLifes(int max) { _playerSettings.maxLifes = max; }
int PlayerComponent::getMaxLifes() { return _playerSettings.maxLifes; }

PlayerComponent::PlayerComponent(Entity* p, textureSettings playerTextureHelper, textureSettings bulletTextureHelper, playerSettings playerSettings, weaponSettings weaponSettings, bulletSettings bulletSettings)
	: Component(p), _playerTextureHelper(playerTextureHelper), _bulletTextureHelper(bulletTextureHelper), _playerSettings(playerSettings), _weaponSettings(weaponSettings), _bulletSettings(bulletSettings), _gracePeriod(false), _gracePeriodTimer(0), _visibilityTimer(0), _maxUpdate(5)
{
	Load();
	colHelp.damageCMP = damageCMP.get();
	colHelp.hpCMP = hpCMP.get();
	colHelp.isMissile = false;
	colHelp.missileCMP = nullptr;

	physicsCMP->getBody()->SetUserData(&colHelp);
}
