#pragma once
#include "ecm.h"
#include "../settings/texture_helper_settings.h"
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

class SpriteComponent : public Component {
protected:
  std::shared_ptr<sf::Sprite> _sprite;
  std::shared_ptr<sf::Texture> _texture;
public:
  SpriteComponent() = delete;
  ~SpriteComponent() override = default;
  explicit SpriteComponent(Entity* p);
  virtual void update(double dt) override;
  void render() override;
  sf::Sprite& getSprite() const;
  void isFollowingParent(bool b);
  bool _following;
  void loadTexture(textureSettings texHelper, sf::Vector2f scale, float angle);
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