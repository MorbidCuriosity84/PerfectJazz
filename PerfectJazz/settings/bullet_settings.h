#pragma once

#include "../game.h"
#include <ecm.h>

struct bulletSettings {
	float lifetime;
	int damage;
	int hp;
	_entityCategory category;
	float angle;
	float direction;
	Scene* scene;
	sf::Vector2f velocity;
	sf::Vector2f spriteScale;	

	bulletSettings() {};
	bulletSettings(float _lifeTime, int _damage, int _hp, float _angle, float _direction, Scene* _scene, sf::Vector2f _velocity, sf::Vector2f _spriteScale, _entityCategory _category)
		: lifetime(_lifeTime), damage(_damage), hp(_hp), angle(_angle), direction(_direction), scene(_scene), velocity(_velocity), spriteScale(_spriteScale), category(_category) {
	}
};

class BulletSettings {
public:
	static bulletSettings LoadSettings(_bulletType type, Scene* scene);
};

