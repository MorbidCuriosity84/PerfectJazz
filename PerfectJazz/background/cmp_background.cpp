#include "cmp_background.h"
#include "../components/cmp_background_physics.h"

//Loads the background, adding a sprite and background physics component
void BackgroundComponent::Load(bool second) {
	spriteCMP = _parent->addComponent<SpriteComponent>();
	_backgroundTextureHelper.spriteTexture.get()->loadFromFile(_backgroundTextureHelper.spriteFilename);
	spriteCMP.get()->loadTexture(_backgroundTextureHelper, _backgroundSettings.spriteScale, _backgroundSettings.angle);
	//The background physics moves the background down at a constant speed
	auto p = _parent->addComponent<BackgroundPhysicsComponent>(Vector2f((float)spriteCMP->getSprite().getTexture()->getSize().x, (float)spriteCMP->getSprite().getTexture()->getSize().y));

	_parent->setPosition(Vector2f(mainView.getSize().x/2, (spriteCMP->getSprite().getGlobalBounds().top + mainView.getSize().y)));
	spriteCMP->getSprite().setColor(sf::Color(_backgroundSettings.opacity));

	//Sets the positon of the second sprite to come right after the first one, to create the infinite background
	if (second) {
		_parent->setPosition(Vector2f((round)(mainView.getSize().x / 2), (spriteCMP->getSprite().getGlobalBounds().top + mainView.getSize().y - spriteCMP->getSprite().getGlobalBounds().height) + 2.f));
	}

	p->setVelocity(_backgroundSettings.velocity);
}
//Update the background position when it leaves the screen by the bottom end
void BackgroundComponent::update(double dt) {

	//When the background x axis is lower than the view w axis, the background gets send before the other sprite
	//to create the illusion of infinite background
	{
		if (_parent->getPosition().y >= mainView.getSize().y + spriteCMP->getSprite().getGlobalBounds().height/2 + _backgroundSettings.offset.y) {
			_parent->setPosition(Vector2f(_parent->getPosition().x, (_parent->getPosition().y - spriteCMP->getSprite().getGlobalBounds().height * 2 - (floor)((_backgroundSettings.offset.y) * 2) + 2.f)));
		}
	}
}
//Constructor for the background component
BackgroundComponent::BackgroundComponent(Entity* p, textureSettings backgroundTextureHelper, backgroundSettings backgroundSettings)
	: Component(p), _backgroundTextureHelper(backgroundTextureHelper), _backgroundSettings(backgroundSettings) {
}