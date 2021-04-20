#include "cmp_background.h"
#include "../components/cmp_background_physics.h"

void BackgroundComponent::Load(bool second) {
	_backgroundTextureHelper.spriteTexture.get()->loadFromFile(_backgroundTextureHelper.spriteFilename);
	auto s = _parent->addComponent<SpriteComponent>();
	s.get()->loadTexture(_backgroundTextureHelper, _backgroundSettings.spriteScale, _backgroundSettings.angle);
	auto p = _parent->addComponent<BackgroundPhysicsComponent>(Vector2f((float)s->getSprite().getTexture()->getSize().x, (float)s->getSprite().getTexture()->getSize().y));

	auto offset = (float)s->getSprite().getTexture()->getSize().y - mainView.getSize().y;

	s->getSprite().setOrigin(Vector2f(_parent->getPosition().x/2, _parent->getPosition().y));
	s->getSprite().setColor(sf::Color(_backgroundSettings.opacity));

	if (second) {
		s->getSprite().setOrigin(Vector2f(_parent->getPosition().x / 2, s->getSprite().getTexture()->getSize().y));
	}

	p->setVelocity(_backgroundSettings.velocity);
}

void BackgroundComponent::update(double dt) {

	//Update background
	{
		auto s = _parent->GetCompatibleComponent<SpriteComponent>();

		if (s[0]->getSprite().getPosition().y > mainView.getSize().y + (_backgroundSettings.offset.y)) {
			_parent->setPosition(Vector2f(_parent->getPosition().x, s[0]->getSprite().getPosition().y - s[0]->getSprite().getTexture()->getSize().y - (_backgroundSettings.offset.y*2)));
		}
	}
}

BackgroundComponent::BackgroundComponent(Entity* p, textureSettings backgroundTextureHelper, backgroundSettings backgroundSettings)
	: Component(p), _backgroundTextureHelper(backgroundTextureHelper), _backgroundSettings(backgroundSettings) {
}
