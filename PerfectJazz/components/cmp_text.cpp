#include "cmp_text.h"
#include "../game.h"
#include <system_renderer.h>
#include <system_resources.h>

// Updates the text component
void TextComponent::update(double dt) {}
// Renders the text component, adding it to the renderer queue
void TextComponent::render() { Renderer::queue(&_text, _parent->getView()); }

// Text component constructor, that sets the initial string and fount
TextComponent::TextComponent(Entity* const p, const std::string& str)
	: Component(p), _string(str) {
	_text.setString(_string);
	_font = Resources::get<sf::Font>("monogram.ttf");
	_text.setFont(*_font);
}

// Sets the text of the text component
void TextComponent::setText(const std::string& str) {
	_string = str;
	_text.setString(_string);
}
// Gets the position of the text component
sf::Vector2f TextComponent::getPosition() { return _text.getPosition(); }
// Sets the position of the text component
void TextComponent::setPosition(sf::Vector2f position) { _text.setPosition(position); }
// Gets the local bounds of the text component
sf::FloatRect TextComponent::getLocalBounds() {	return _text.getLocalBounds();}
// Sets the local bounds of the text component
sf::FloatRect TextComponent::getGlobalBounds() {return _text.getGlobalBounds();}
// Sets the origin of the text component, defining its center point
void TextComponent::setOrigin(sf::Vector2f origin) {_text.setOrigin(origin);}
// Gets the origin of the text component
sf::Vector2f TextComponent::getOrigin() {return _text.getOrigin();}
// Sets the font size of the text using a double
void TextComponent::setFontSize(double size) {_text.setCharacterSize((round)(size * windowScale.x));}
// Gets the font size of the text
double TextComponent::getFontSize() {return _text.getCharacterSize();}
// Sets the font size of the text using an unsigned int
void TextComponent::setFontSize(unsigned int size) {_text.setCharacterSize((round)(size * windowScale.x));}
