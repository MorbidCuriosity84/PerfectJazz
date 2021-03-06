#pragma once

#include <SFML/Graphics/Text.hpp>
#include "ecm.h"

// Text component that provides methods to change the font size, colour, position, and origin
class TextComponent : public Component {
public:
	TextComponent() = delete;
	explicit TextComponent(Entity* p, const std::string& str = "");
	void update(double dt) override;
	void render() override;
	void setFontSize(double size);
	double getFontSize();
	void setText(const std::string& str);
	void setPosition(sf::Vector2f position);
	sf::FloatRect getLocalBounds();
	sf::FloatRect getGlobalBounds();
	void setOrigin(sf::Vector2f position);
	sf::Vector2f getOrigin();
	sf::Vector2f getPosition();
	sf::Text _text;
	void setFontSize(unsigned int size);
	~TextComponent() override = default;

protected:
	std::shared_ptr<sf::Font> _font;
	std::string _string;
};