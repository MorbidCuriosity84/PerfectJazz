#include "cmp_powerup.h"
#include "../randomNumber.h"
#include "../components/cmp_background_physics.h"

using namespace std;
using namespace sf;

void PowerupComponent::deployPowerup() {
	//probabilities for the columns. Each columns has a chance to be randomly picked
	std::discrete_distribution<> columnWeights({
		2,   // 1st column % chance
		10,  // 2nd column % chance
		8,   // 3rd column % chance
		5,   // 4th column % chance
		8,   // 5th column % chance
		2,   // 6th column % chance
		5,   // 7th column % chance
		10,  // 8th column % chance
		10,  // 9th column % chance
		5,   // 10th column % chance
		2,   // 11th column % chance
		8,   // 12th column % chance
		5,   // 13th column % chance
		8,   // 14th column % chance
		10,  // 15th column % chance
		2 });// 16th column % chance

	int choosenColumn = RandomNumber::generateRandomNumber(columnWeights);
	//cout << choosenColumn << ": colm" << endl;

	//add to x half size of sprite
	_powerupTextureHelper.spriteTexture.get()->loadFromFile(_powerupTextureHelper.spriteFilename);
	powerupSpriteCMP = _parent->addComponent<SpriteComponent>();
	powerupSpriteCMP.get()->loadTexture(_powerupTextureHelper, { 1.f, 1.f }, 0);
	auto p = _parent->addComponent<BackgroundPhysicsComponent>(Vector2f((float)powerupSpriteCMP->getSprite().getTexture()->getSize().x, (float)powerupSpriteCMP->getSprite().getTexture()->getSize().y));
	p->setVelocity(Vector2f(0.f, 100.f));
	//Set the powerup srpite in the right column, cencetered withing the tile
	_parent->setPosition(Vector2f((round)(mainView.getSize().x / 16 * choosenColumn) + ((mainView.getSize().x / 16) / 2), -200.f));
	_parent->addTag(_type);
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

PowerupComponent::PowerupComponent(Entity* p, textureSettings powerupTextureHelper, string type) : Component(p), _powerupTextureHelper(powerupTextureHelper), _type(type) {
	deployPowerup();
}