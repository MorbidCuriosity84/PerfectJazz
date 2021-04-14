#include "cmp_text.h"
#include <system_renderer.h>
#include <system_resources.h>

void TextComponent::update(double dt) {}

void TextComponent::render() { Renderer::queue(&_text, _parent->getView()); }

TextComponent::TextComponent(Entity* const p, const std::string& str)
    : Component(p), _string(str) {
  _text.setString(_string);
  _font = Resources::get<sf::Font>("RobotoMono-Regular.ttf");
  _text.setFont(*_font);  
}

void TextComponent::setText(const std::string& str) {
  _string = str;
  _text.setString(_string);
  _text.setCharacterSize(12);
}

sf::Vector2f TextComponent::getPosition() {
    return _text.getPosition();
}

void TextComponent::setPosition(sf::Vector2f position) {
    _text.setPosition(position);
}

void TextComponent::setOrigin(sf::Vector2f position) {
    _text.setOrigin(position);
}

sf::Vector2f TextComponent::getOrigin() {
    return _text.getOrigin();
}

void TextComponent::setFontSize(double size) {
    _text.setCharacterSize(size);
}

void TextComponent::setFontSize(unsigned int size)
{
    _text.setCharacterSize(size);
}
