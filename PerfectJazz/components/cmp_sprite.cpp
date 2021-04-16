#include "cmp_sprite.h"
#include "system_renderer.h"

using namespace std;

void SpriteComponent::loadTexture(textureHelper texHelper, sf::Vector2f scale, float angle)
{
	texHelper.spriteRectangle.get()->left = (texHelper.spriteTexture.get()->getSize().x / texHelper.spriteCols) * texHelper.desiredCol;
	texHelper.spriteRectangle.get()->top = (texHelper.spriteTexture.get()->getSize().y / texHelper.spriteRows) * texHelper.desiredRow;
	texHelper.spriteRectangle.get()->width = (texHelper.spriteTexture.get()->getSize().x / texHelper.spriteCols);
	texHelper.spriteRectangle.get()->height = (texHelper.spriteTexture.get()->getSize().y / texHelper.spriteRows);
	getSprite().setTexture(*texHelper.spriteTexture.get());
	getSprite().setTextureRect(*texHelper.spriteRectangle.get());
	getSprite().setOrigin(texHelper.spriteRectangle.get()->width / 2, texHelper.spriteRectangle.get()->height / 2);
	getSprite().setScale(scale);
	getSprite().setRotation(angle);
}

void SpriteComponent::setTexure(std::shared_ptr<sf::Texture> tex)
{
  _texture = tex;
  _sprite->setTexture(*_texture);
}

SpriteComponent::SpriteComponent(Entity* p)
    : Component(p), _sprite(make_shared<sf::Sprite>()) {}

sf::Sprite& SpriteComponent::getSprite() const { return *_sprite; }


void SpriteComponent::update(double dt) {
  _sprite->setPosition(_parent->getPosition());
}
void SpriteComponent::render() { Renderer::queue(_sprite.get(), _parent->getView()); }


void ShapeComponent::update(double dt) {
  _shape->setPosition(_parent->getPosition());
  _shape->setRotation(_parent->getRotation());
}

void ShapeComponent::render() { Renderer::queue(_shape.get(), _parent->getView()); }

sf::Shape& ShapeComponent::getShape() const { return *_shape; }

ShapeComponent::ShapeComponent(Entity* p)
    : Component(p), _shape(make_shared<sf::CircleShape>()) {}

