#include "cmp_background.h"
#include "../components/cmp_background_physics.h"

void BackgroundComponent::Load(bool second) {
	spriteCMP = _parent->addComponent<SpriteComponent>();
	_backgroundTextureHelper.spriteTexture.get()->loadFromFile(_backgroundTextureHelper.spriteFilename);
	spriteCMP.get()->loadTexture(_backgroundTextureHelper, _backgroundSettings.spriteScale, _backgroundSettings.angle);
	auto p = _parent->addComponent<BackgroundPhysicsComponent>(Vector2f((float)spriteCMP->getSprite().getTexture()->getSize().x, (float)spriteCMP->getSprite().getTexture()->getSize().y));

	auto offset = (float)spriteCMP->getSprite().getTexture()->getSize().y - mainView.getSize().y;

	_parent->setPosition(Vector2f(mainView.getSize().x/2, (spriteCMP->getSprite().getGlobalBounds().top + mainView.getSize().y)));
	spriteCMP->getSprite().setColor(sf::Color(_backgroundSettings.opacity));

	if (second) {
		_parent->setPosition(Vector2f((round)(mainView.getSize().x / 2), (spriteCMP->getSprite().getGlobalBounds().top + mainView.getSize().y - spriteCMP->getSprite().getGlobalBounds().height) + 1.f));
	}

	p->setVelocity(_backgroundSettings.velocity);
}

void BackgroundComponent::update(double dt) {

	//Update background
	{
		if (_parent->getPosition().y >= mainView.getSize().y + spriteCMP->getSprite().getGlobalBounds().height/2 + _backgroundSettings.offset.y) {
			_parent->setPosition(Vector2f(_parent->getPosition().x, (_parent->getPosition().y - spriteCMP->getSprite().getGlobalBounds().height * 2 - (floor)((_backgroundSettings.offset.y) * 2) + 1.f)));
		}
	}
}

BackgroundComponent::BackgroundComponent(Entity* p, textureSettings backgroundTextureHelper, backgroundSettings backgroundSettings)
	: Component(p), _backgroundTextureHelper(backgroundTextureHelper), _backgroundSettings(backgroundSettings) {
}