#include "cmp_sprite.h"
#include "system_renderer.h"

using namespace std;

void SpriteComponent::loadTexture(textureSettings texHelper, sf::Vector2f scale, float angle) {
	getSprite().setTexture(*texHelper.spriteTexture.get());
	getSprite().setScale((scale * windowScale));
	getSprite().setRotation(angle);
	texHelper.spriteRectangle.get()->left = (texHelper.spriteTexture.get()->getSize().x / texHelper.spriteCols) * texHelper.desiredCol;
	texHelper.spriteRectangle.get()->top = (texHelper.spriteTexture.get()->getSize().y / texHelper.spriteRows) * texHelper.desiredRow;
	texHelper.spriteRectangle.get()->width = (texHelper.spriteTexture.get()->getSize().x / texHelper.spriteCols);
	texHelper.spriteRectangle.get()->height = (texHelper.spriteTexture.get()->getSize().y / texHelper.spriteRows);
	getSprite().setTextureRect(*texHelper.spriteRectangle.get());
	getSprite().setOrigin(getSprite().getLocalBounds().width/2, getSprite().getLocalBounds().height / 2);
}

void SpriteComponent::setTexure(std::shared_ptr<sf::Texture> tex) {
	_texture = tex;
	_sprite->setTexture(*_texture);
}

SpriteComponent::SpriteComponent(Entity* p)
	: Component(p), _sprite(make_shared<sf::Sprite>()), _following(true) {
}

sf::Sprite& SpriteComponent::getSprite() const { return *_sprite; }

void SpriteComponent::isFollowingParent(bool b) {
	_following = b;
}


void SpriteComponent::update(double dt) {
	if (_following) {
		_sprite->setPosition(_parent->getPosition());
		//_sprite->setRotation(_parent->getRotation() );
	}
}

void SpriteComponent::render() { Renderer::queue(_sprite.get(), _parent->getView()); }

void ShapeComponent::update(double dt) {
	_shape->setPosition(_parent->getPosition());
	_shape->setRotation(_parent->getRotation());
}

void ShapeComponent::render() { Renderer::queue(_shape.get(), _parent->getView()); }

sf::Shape& ShapeComponent::getShape() const { return *_shape; }

ShapeComponent::ShapeComponent(Entity* p)
	: Component(p), _shape(make_shared<sf::CircleShape>()) {
}

