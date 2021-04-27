#include "cmp_text.h"
#include "../game.h"
#include <system_renderer.h>
#include <system_resources.h>

void TextComponent::update(double dt) {
	//_text.setPosition(_parent->getPosition()); 
}

void TextComponent::render() { Renderer::queue(&_text, _parent->getView()); }

TextComponent::TextComponent(Entity* const p, const std::string& str)
	: Component(p), _string(str) {
	_text.setString(_string);
	_font = Resources::get<sf::Font>("monogram.ttf");
	_text.setFont(*_font);
}

void TextComponent::setText(const std::string& str) {
	_string = str;
	_text.setString(_string);
}

sf::Vector2f TextComponent::getPosition() { return _text.getPosition(); }

void TextComponent::setPosition(sf::Vector2f position) { _text.setPosition(position); }

sf::FloatRect TextComponent::getLocalBounds() {	return _text.getLocalBounds();}

sf::FloatRect TextComponent::getGlobalBounds() {return _text.getGlobalBounds();}

void TextComponent::setOrigin(sf::Vector2f origin) {_text.setOrigin(origin);}

sf::Vector2f TextComponent::getOrigin() {return _text.getOrigin();}

void TextComponent::setFontSize(double size) {_text.setCharacterSize((round)(size * windowScale.x));}

double TextComponent::getFontSize() {return _text.getCharacterSize();}

void TextComponent::setFontSize(unsigned int size) {_text.setCharacterSize((round)(size * windowScale.x));}
