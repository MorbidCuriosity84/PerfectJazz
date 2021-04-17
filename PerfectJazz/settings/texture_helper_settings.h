#pragma once
#include "ecm.h"
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "../game.h"
/*
* @param std::string _filename, uint16_t _spriteRows, uint16_t _spriteCols, uint16_t _desiredRow, uint16_t _desiredCol, std::shared_ptr<sf::Texture> _texture, std::shared_ptr<sf::IntRect> _rect, double _timer
*
* @desc Helper structure for creating textures
*/

struct textureSettings {
	std::string spriteFilename;
	std::shared_ptr<sf::IntRect> spriteRectangle;
	std::shared_ptr<sf::Texture> spriteTexture;
	uint16_t spriteRows;
	uint16_t spriteCols;
	uint16_t desiredRow;
	uint16_t desiredCol;
	double spriteTimer;

	textureSettings() {};
	textureSettings(std::string _filename, uint16_t _spriteRows, uint16_t _spriteCols, uint16_t _desiredRow, uint16_t _desiredCol, std::shared_ptr<sf::Texture> _texture, std::shared_ptr<sf::IntRect> _rect, double _timer)
		: spriteFilename(_filename), spriteRows(_spriteRows), spriteCols(_spriteCols), desiredRow(_desiredRow), desiredCol(_desiredCol), spriteTexture(_texture), spriteRectangle(_rect), spriteTimer(_timer) {
	}
};

class TextureHelpingSettings {
public:
	static textureSettings LoadSettings(_enemyType type, Scene* scene);
	static textureSettings LoadSettings(_playerType type, Scene* scene);
	static textureSettings LoadSettings(_bulletType type, Scene* scene);

};