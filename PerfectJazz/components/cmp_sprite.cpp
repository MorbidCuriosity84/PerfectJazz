#include "cmp_sprite.h"
#include "system_renderer.h"

using namespace std;

// Loads the necessary texture for the sprite, setting the rectangle and gettign the right sprite
// from the sprite sheet. It sets the origin of the sprite to its center
void SpriteComponent::loadTexture(textureSettings texHelper, sf::Vector2f scale, float angle) {
	getSprite().setTexture(*texHelper.spriteTexture.get());
	getSprite().setScale((scale * windowScale));
	getSprite().setRotation(angle);
	texHelper.spriteRectangle.get()->left = (texHelper.spriteTexture.get()->getSize().x / texHelper.spriteCols) * texHelper.desiredCol;
	texHelper.spriteRectangle.get()->top = (texHelper.spriteTexture.get()->getSize().y / texHelper.spriteRows) * texHelper.desiredRow;
	texHelper.spriteRectangle.get()->width = (texHelper.spriteTexture.get()->getSize().x / texHelper.spriteCols);
	texHelper.spriteRectangle.get()->height = (texHelper.spriteTexture.get()->getSize().y / texHelper.spriteRows);
	getSprite().setTextureRect(*texHelper.spriteRectangle.get());
	getSprite().setOrigin(getSprite().getLocalBounds().width / 2, getSprite().getLocalBounds().height / 2);
}

// Set the texture of the sprite
void SpriteComponent::setTexure(std::shared_ptr<sf::Texture> tex) {
	_texture = tex;
	_sprite->setTexture(*_texture);
}
// Constructor for the sprite component
SpriteComponent::SpriteComponent(Entity* p)
	: Component(p), _sprite(make_shared<sf::Sprite>()), _following(true) {
}
// Gets a pointer to the sprite component
sf::Sprite& SpriteComponent::getSprite() const { return *_sprite; }
// Sets if the sprite must follow the parent or no
void SpriteComponent::isFollowingParent(bool b) { _following = b; }

// Updates the sprites position only if it's following its parent
void SpriteComponent::update(double dt) {
	if (_following) {
		_sprite->setPosition(_parent->getPosition());
	}
}
// Renders the sprite component by adding it to the renderer queue
void SpriteComponent::render() { Renderer::queue(_sprite.get(), _parent->getView()); }

// Updates the shape component position and rotation
void ShapeComponent::update(double dt) {
	_shape->setPosition(_parent->getPosition());
	_shape->setRotation(_parent->getRotation());
}
// Renders the shape component by adding it to the renderer queue
void ShapeComponent::render() { Renderer::queue(_shape.get(), _parent->getView()); }
// Gets the shape of the shape component
sf::Shape& ShapeComponent::getShape() const { return *_shape; }
// Constructor for the shape component
ShapeComponent::ShapeComponent(Entity* p)
	: Component(p), _shape(make_shared<sf::CircleShape>()) {
}

