#include "cmp_powerup.h"
#include "../randomNumber.h"
#include "maths.h"

using namespace std;
using namespace sf;

void PowerupComponent::deployPowerup() {
	
	_powerupTextureHelper.spriteTexture.get()->loadFromFile(_powerupTextureHelper.spriteFilename);
	powerupSpriteCMP = _parent->addComponent<SpriteComponent>();
	powerupSpriteCMP.get()->loadTexture(_powerupTextureHelper, { 1.f, 1.f }, 0);
	damageCMP = _parent->addComponent<DamageComponent>(1);
	physicsCMP = _parent->addComponent<PhysicsComponent>(true, powerupSpriteCMP->getSprite().getLocalBounds().getSize());
	
	hpCMP = _parent->addComponent<HPComponent>(_powerupSettings.scene, 1);
	hpCMP->loadHP();
	hpCMP.get()->setVisible(false);

	physicsCMP->getBody()->SetBullet(true);
	physicsCMP->setSensor(true);
	physicsCMP->setVelocity(_powerupSettings.velocity * _powerupSettings.direction);
	physicsCMP->setCategory(ENEMY_BULLET);
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

		if (hpCMP->getHP() <= 0) {
			physicsCMP->teleport(Vector2f(-500.f, -500.f));
		}
	}

	// Delete powerup entity if offscreen
	if (_parent->getPosition().y > _parent->getView().getSize().y) { _parent->setForDelete(); }
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