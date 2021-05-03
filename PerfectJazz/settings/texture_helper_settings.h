#pragma once
#include "ecm.h"
#include "../game.h"
/*
* @param std::string _filename, uint16_t _spriteRows, uint16_t _spriteCols, uint16_t _desiredRow, uint16_t _desiredCol, std::shared_ptr<sf::Texture> _texture, std::shared_ptr<sf::IntRect> _rect, double _timer
*
* Helper structure for creating textures
*/
//Defines all the fields for the textures settings
struct textureSettings {
	std::string spriteFilename;
	std::shared_ptr<sf::IntRect> spriteRectangle;
	std::shared_ptr<sf::Texture> spriteTexture;
	uint16_t spriteRows;
	uint16_t spriteCols;
	uint16_t desiredRow;
	uint16_t desiredCol;
	double spriteTimer;

	//Default constructor
	textureSettings() {};
	//Constructor with parameters
	textureSettings(std::string _filename, uint16_t _spriteRows, uint16_t _spriteCols, uint16_t _desiredRow, uint16_t _desiredCol, std::shared_ptr<sf::Texture> _texture, std::shared_ptr<sf::IntRect> _rect, double _timer)
		: spriteFilename(_filename), spriteRows(_spriteRows), spriteCols(_spriteCols), desiredRow(_desiredRow), desiredCol(_desiredCol), spriteTexture(_texture), spriteRectangle(_rect), spriteTimer(_timer) {
	}
};

class TextureHelpingSettings {
public:
	//Creates an instance of the struct textureSettings depending of the type of enemy
	static textureSettings LoadSettings(_enemyType type, Scene* scene);
	//Creates an instance of the struct textureSettings depending of the type of player
	static textureSettings LoadSettings(_playerType type, Scene* scene);
	//Creates an instance of the struct textureSettings depending of the type of bullet
	static textureSettings LoadSettings(_bulletType type, Scene* scene);
	//Creates an instance of the struct textureSettings depending of the type of background
	static textureSettings LoadSettings(_backgroundType type, Scene* scene);
	//Creates an instance of the struct textureSettings depending of the type of powerup
	static textureSettings LoadSettings(_powerUpsType type, Scene* scene);
};