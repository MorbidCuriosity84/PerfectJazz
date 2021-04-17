#pragma once

#include "ecm.h"
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

/*
* @param std::string _filename, uint16_t _spriteRows, uint16_t _spriteCols, uint16_t _desiredRow, uint16_t _desiredCol, std::shared_ptr<sf::Texture> _texture, std::shared_ptr<sf::IntRect> _rect, double _timer
* 
* @desc Helper structure for creating textures
*/
struct textureHelper {
	std::string spriteFilename;
	std::shared_ptr<sf::IntRect> spriteRectangle;
	std::shared_ptr<sf::Texture> spriteTexture;
	uint16_t spriteRows;
	uint16_t spriteCols;
	uint16_t desiredRow;
	uint16_t desiredCol;
	double spriteTimer;
	
	textureHelper() {};
	textureHelper(std::string _filename, uint16_t _spriteRows, uint16_t _spriteCols, uint16_t _desiredRow, uint16_t _desiredCol, std::shared_ptr<sf::Texture> _texture, std::shared_ptr<sf::IntRect> _rect, double _timer)
		: spriteFilename(_filename), spriteRows(_spriteRows), spriteCols(_spriteCols), desiredRow(_desiredRow), desiredCol(_desiredCol), spriteTexture(_texture), spriteRectangle(_rect), spriteTimer(_timer) {}
};

class SpriteComponent : public Component {
protected:
  std::shared_ptr<sf::Sprite> _sprite;
  std::shared_ptr<sf::Texture> _texture;
public:
  SpriteComponent() = delete;

  explicit SpriteComponent(Entity* p);
  void update(double dt) override;
  void render() override;

  sf::Sprite& getSprite() const;

  void loadTexture(textureHelper texHelper, sf::Vector2f scale, float angle);
  void setTexure(std::shared_ptr<sf::Texture> tex);
};

class ShapeComponent : public Component {
protected:
  std::shared_ptr<sf::Shape> _shape;
  // sf::Shape _shape;

public:
  ShapeComponent() = delete;

  explicit ShapeComponent(Entity* p);

  void update(double dt) override;
  void render() override;
  sf::Shape& getShape() const;
  template <typename T, typename... Targs> void setShape(Targs... params) {
    _shape.reset(new T(params...));
  }
};