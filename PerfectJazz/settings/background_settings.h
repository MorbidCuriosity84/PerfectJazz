#pragma once

#include "../game.h"
#include <ecm.h>

struct backgroundSettings {
	float direction;
	Color opacity;
	Vector2f offset;
	Scene* scene;
	sf::Vector2f velocity;
	sf::Vector2f spriteScale;
	float angle;


	backgroundSettings() {};
	backgroundSettings(float _direction, Color _opacity, Vector2f _offset, Scene* _scene, sf::Vector2f _velocity, sf::Vector2f _spriteScale, _entityCategory _category, float _angle)
		: direction(_direction), opacity(_opacity), offset(_offset), scene(_scene), velocity(_velocity), spriteScale(_spriteScale), angle(_angle) {
	}
};

class BackgroundSettings {
public:
	static backgroundSettings LoadSettings(_backgroundType type, Scene* scene);
};

