#include "cmp_powerup.h"
#include "../randomNumber.h"
#include "../components/cmp_background_physics.h"

using namespace std;
using namespace sf;

void PowerupComponent::deployPowerup() {
	
	_powerupTextureHelper.spriteTexture.get()->loadFromFile(_powerupTextureHelper.spriteFilename);
	powerupSpriteCMP = _parent->addComponent<SpriteComponent>();
	powerupSpriteCMP.get()->loadTexture(_powerupTextureHelper, { 1.f, 1.f }, 0);
	auto p = _parent->addComponent<BackgroundPhysicsComponent>(Vector2f((float)powerupSpriteCMP->getSprite().getTexture()->getSize().x, (float)powerupSpriteCMP->getSprite().getTexture()->getSize().y));
	p->setVelocity(Vector2f(0.f, 100.f));
}

void PowerupComponent::update(double dt) {
	//if parent is of type coin_pwu
	if (_parent->getTags().find("coin_pwu") != _parent->getTags().end()) {
		_powerupTextureHelper.spriteTimer += dt;
		if (_powerupTextureHelper.spriteTimer < 0.1) {
			_powerupTextureHelper.spriteRectangle.get()->left = (_powerupTextureHelper.spriteTexture.get()->getSize().x / _powerupTextureHelper.spriteCols) * 0;
		}
		if (_powerupTextureHelper.spriteTimer >= 0.1 && _powerupTextureHelper.spriteTimer < 0.3) {
			_powerupTextureHelper.spriteRectangle.get()->left = (_powerupTextureHelper.spriteTexture.get()->getSize().x / _powerupTextureHelper.spriteCols) * 1;
		}
		if (_powerupTextureHelper.spriteTimer >= 0.3 && _powerupTextureHelper.spriteTimer < 0.4) {
			_powerupTextureHelper.spriteRectangle.get()->left = (_powerupTextureHelper.spriteTexture.get()->getSize().x / _powerupTextureHelper.spriteCols) * 2;
		}
		if (_powerupTextureHelper.spriteTimer >= 0.4 && _powerupTextureHelper.spriteTimer < 0.5) {
			_powerupTextureHelper.spriteRectangle.get()->left = (_powerupTextureHelper.spriteTexture.get()->getSize().x / _powerupTextureHelper.spriteCols) * 3;
		}
		if (_powerupTextureHelper.spriteTimer >= 0.5 && _powerupTextureHelper.spriteTimer < 0.6) {
			_powerupTextureHelper.spriteRectangle.get()->left = (_powerupTextureHelper.spriteTexture.get()->getSize().x / _powerupTextureHelper.spriteCols) * 4;
		}
		if (_powerupTextureHelper.spriteTimer >= 0.7) {
			_powerupTextureHelper.spriteTimer = 0.0;
		}

		powerupSpriteCMP->getSprite().setTextureRect(*_powerupTextureHelper.spriteRectangle.get());
	}

	// Delete powerup entity if offscreen
	if (_parent->getPosition().y > _parent->getView().getSize().y) { _parent->setForDelete(); }
}

PowerupComponent::PowerupComponent(Entity* p, textureSettings powerupTextureHelper) : Component(p), _powerupTextureHelper(powerupTextureHelper) {
	deployPowerup();
}