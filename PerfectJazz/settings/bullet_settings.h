#pragma once

#include "../game.h"
#include <ecm.h>
#include <SFML/Audio/Sound.hpp>

struct bulletSettings {
	float lifetime;
	int damage;
	int baseDamage;
	int damageUpgradeCount;
	int hp;
	_entityCategory category;
	float angle;
	float direction;
	Scene* scene;
	sf::Vector2f velocity;
	sf::Vector2f spriteScale;	
	std::string soundFile;

	bulletSettings() {};
	bulletSettings(float _lifeTime, int _damage, int _damageUpgradeCount, int _hp, float _angle, float _direction, Scene* _scene, sf::Vector2f _velocity, sf::Vector2f _spriteScale, _entityCategory _category, std::string snd)
		: lifetime(_lifeTime), damage(_damage), baseDamage(damage), damageUpgradeCount(_damageUpgradeCount), hp(_hp), angle(_angle), direction(_direction), scene(_scene), velocity(_velocity), spriteScale(_spriteScale), category(_category), soundFile(snd) {
	}
};

class BulletSettings {
public:
	static bulletSettings LoadSettings(_bulletType type, Scene* scene);
};

