#pragma once

#include "../game.h"
#include <ecm.h>
//Defines all the fields for the powerups settings
struct powerupSettings {
	float lifetime;
	int damage;
	int damageUpgradeCount;
	int hp;
	_entityCategory category;
	float angle;
	float direction;
	Scene* scene;
	sf::Vector2f velocity;
	sf::Vector2f spriteScale;
	SOUNDS sound;

	//Default constructor
	powerupSettings() {};
	//Constructor with parameters
	powerupSettings(float _lifeTime, int _damage, int _damageUpgradeCount, int _hp, float _angle, float _direction, Scene* _scene, sf::Vector2f _velocity, sf::Vector2f _spriteScale, _entityCategory _category, SOUNDS snd)
		: lifetime(_lifeTime), damage(_damage), damageUpgradeCount(_damageUpgradeCount), hp(_hp), angle(_angle), direction(_direction), scene(_scene), velocity(_velocity), spriteScale(_spriteScale), category(_category), sound(snd) {
	}
};

class PowerupSettings {
public:
	//Creates an instance of the struct powerupSettings depending of the type of powerup
	static powerupSettings LoadSettings(_powerUpsType type, Scene* scene);
};