
#include "cmp_sprite.h"
#include "system_renderer.h"

using namespace std;


void SpriteComponent::loadTexture(textureHelper texHelper, sf::Vector2f scale, float angle)
{
	texHelper._spriteRectangle.get()->left = (texHelper._spriteTexture.get()->getSize().x / texHelper.spriteCols) * texHelper.desiredCol;
	texHelper._spriteRectangle.get()->top = (texHelper._spriteTexture.get()->getSize().y / texHelper.spriteRows) * texHelper.desiredRow;
	texHelper._spriteRectangle.get()->width = (texHelper._spriteTexture.get()->getSize().x / texHelper.spriteCols);
	texHelper._spriteRectangle.get()->height = (texHelper._spriteTexture.get()->getSize().y / texHelper.spriteRows);
	getSprite().setTexture(*texHelper._spriteTexture.get());
	getSprite().setTextureRect(*texHelper._spriteRectangle.get());	


	getSprite().setOrigin(texHelper._spriteTexture->getSize().x / (texHelper.spriteCols * 2),  texHelper._spriteTexture->getSize().y / (texHelper.spriteRows * 2));
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

