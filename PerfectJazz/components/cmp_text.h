#pragma once

#include <SFML/Graphics/Text.hpp>
#include <ecm.h>

class TextComponent : public Component {
public:
	TextComponent() = delete;
	explicit TextComponent(Entity* p, const std::string& str = "");
	void update(double dt) override;
	void render() override;
	void setFontSize(double size);
	double getFontSize();
	~TextComponent() override = default;
	void setText(const std::string& str);
	void setPosition(sf::Vector2f position);
	sf::FloatRect getLocalBounds();
	void setOrigin(sf::Vector2f position);
	sf::Vector2f getOrigin();
	sf::Vector2f getPosition();

	void setFontSize(unsigned int size);

protected:
	std::shared_ptr<sf::Font> _font;
	std::string _string;
	sf::Text _text;
};
