#pragma once
#include "../game.h"

/*
* @param int _damage, int _hp, Scene* _scene, float _restitution, float _friction, sf::Vector2f _velocity, _entityCategory _category, bool _hpVisible, sf::Vector2f _scale, float _angle;
*/

static struct playerSettings {
	int damage;
	int hp;
	int maxHP;
	bool hpVisible;
	float restitution;
	float friction;
	float angle;
	int lifes;
	int score;
	int shopPoints;
	Scene* scene;
	_entityCategory category;
	sf::Vector2f velocity;
	sf::Vector2f scale;

	playerSettings() {};
	playerSettings(int _damage, int _hp, Scene* _scene, float _restitution, float _friction, float _lifes, int _score, int _shopPoints, sf::Vector2f _velocity, _entityCategory _category, bool _hpVisible, sf::Vector2f _scale, float _angle)
		: damage(_damage), hp(_hp), scene(_scene), restitution(_restitution), friction(_friction), lifes(_lifes), score(_score), shopPoints(_shopPoints), velocity(_velocity), category(_category), hpVisible(_hpVisible), scale(_scale), angle(_angle) {
	}
};

class PlayerSettings {
public:
	static playerSettings LoadSettings(_playerType type, Scene* scene);
	playerSettings currentPlayerSettings;

};

