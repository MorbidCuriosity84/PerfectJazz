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
	int maxLifes;
	int score;
	int shopPoints;
	int flySpeedUpgradeCount;
	Scene* scene;
	_entityCategory category;
	float flySpeed;
	sf::Vector2f scale;

	playerSettings() {};
	playerSettings(int _damage, int _hp, Scene* _scene, float _restitution, float _friction, int _lifes, int _maxLifes, int _score, int _shopPoints, float _flySpeed, int _flySpeedUpgradeCount,_entityCategory _category, bool _hpVisible, sf::Vector2f _scale, float _angle)
		: damage(_damage), hp(_hp), scene(_scene), restitution(_restitution), friction(_friction), lifes(_lifes), maxLifes(_maxLifes), score(_score), shopPoints(_shopPoints), flySpeed(_flySpeed), flySpeedUpgradeCount(_flySpeedUpgradeCount), category(_category), hpVisible(_hpVisible), scale(_scale), angle(_angle) {
	}
};

class PlayerSettings {
public:
	static playerSettings LoadSettings(_playerType type, Scene* scene);
	playerSettings currentPlayerSettings;

};

