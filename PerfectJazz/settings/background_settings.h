#pragma once

#include "../game.h"
#include <ecm.h>
//Defines all the fields for the backgrounds settings
struct backgroundSettings {
	float direction;
	Color opacity;
	Vector2f offset;
	Scene* scene;
	sf::Vector2f velocity;
	sf::Vector2f spriteScale;
	float angle;

	//Default constructor
	backgroundSettings() {};
	//Constructor with parameters
	backgroundSettings(float _direction, Color _opacity, Vector2f _offset, Scene* _scene, sf::Vector2f _velocity, sf::Vector2f _spriteScale, _entityCategory _category, float _angle)
		: direction(_direction), opacity(_opacity), offset(_offset), scene(_scene), velocity(_velocity), spriteScale(_spriteScale), angle(_angle) {
	}
};

class BackgroundSettings {
public:
	//Creates an instance of the struct backgroundSettings depending of the type of background
	static backgroundSettings LoadSettings(_backgroundType type, Scene* scene);
};

