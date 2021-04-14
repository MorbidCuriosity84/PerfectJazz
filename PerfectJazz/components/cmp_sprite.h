#pragma once

#include "ecm.h"
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

/*
* @param string filename, uint16_t rows, uint16_t  cols, uint16_t dRow, uint16_t dCol
* 
* @Desc Helper structure for creating textures
*/
struct textureHelper {
	std::string spriteFilename;
	std::shared_ptr<sf::IntRect> _spriteRectangle;
	std::shared_ptr<sf::Texture> _spriteTexture;
	uint16_t spriteRows;
	uint16_t spriteCols;
	uint16_t desiredRow;
	uint16_t desiredCol;
	double _spriteTimer;
	
	textureHelper(std::string filename, uint16_t rows, uint16_t cols, uint16_t dRow, uint16_t dCol, std::shared_ptr<sf::Texture> texture, std::shared_ptr<sf::IntRect> rect, double timer)
		: spriteFilename(filename), spriteRows(rows), spriteCols(cols), desiredRow(dRow), desiredCol(dCol) , _spriteRectangle(rect), _spriteTexture(texture), _spriteTimer(timer) {}
	
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

  void loadTexture(textureHelper texHelper, sf::Vector2f scale);
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