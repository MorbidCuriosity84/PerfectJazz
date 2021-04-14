
#include "cmp_sprite.h"
#include "system_renderer.h"

using namespace std;


void SpriteComponent::loadTexture(int numRows, int numCols, int row, int col, sf::IntRect& rect, sf::Texture& texture)
{
	rect.left = (texture.getSize().x / numCols) * col;
	rect.top = (texture.getSize().y / numRows) * row;
	rect.width = (texture.getSize().x / numCols);
	rect.height = (texture.getSize().y / numRows);
	getSprite().setTexture(texture);
	getSprite().setTextureRect(rect);
	getSprite().setOrigin(texture.getSize().x / (2 * numCols), texture.getSize().y / (2 * numRows));
}

void SpriteComponent::loadTexture(textureHelper texHelper, sf::Vector2f scale)
{
	texHelper._spriteRectangle.get()->left = (texHelper._spriteTexture.get()->getSize().x / texHelper.spriteCols) * texHelper.desiredCol;
	texHelper._spriteRectangle.get()->top = (texHelper._spriteTexture.get()->getSize().y / texHelper.spriteRows) * texHelper.desiredRow;
	texHelper._spriteRectangle.get()->width = (texHelper._spriteTexture.get()->getSize().x / texHelper.spriteCols);
	texHelper._spriteRectangle.get()->height = (texHelper._spriteTexture.get()->getSize().y / texHelper.spriteRows);
	getSprite().setTexture(*texHelper._spriteTexture.get());
	getSprite().setTextureRect(*texHelper._spriteRectangle.get());	
	getSprite().setOrigin(texHelper._spriteTexture.get()->getSize().x / (2.f * texHelper.spriteCols), texHelper._spriteTexture.get()->getSize().y / (2.f * texHelper.spriteRows));
	getSprite().setScale(scale);
}

void SpriteComponent::setTexure(std::shared_ptr<sf::Texture> tex)
{
  _texture = tex;
  _sprite->setTexture(*_texture);
}


SpriteComponent::SpriteComponent(Entity* p)
    : Component(p), _sprite(make_shared<sf::Sprite>()) {}

void SpriteComponent::update(double dt) {
  _sprite->setPosition(_parent->getPosition());
  _sprite->setRotation(_parent->getRotation());
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

sf::Sprite& SpriteComponent::getSprite() const { return *_sprite; }
