#pragma once
#include "../game.h"
#include <ecm.h>
#include <SFML/Graphics.hpp>
#include <LevelSystem.h>
#include "../components/cmp_sprite.h"
#include "../components/cmp_weapon.h"
#include "../components/cmp_bullet.h"


/*
* @param ls::Tile _tile, int _damage, int _hp, Scene* _scene, float _restitution, float _friction, sf::Vector2f _velocity, _entityCategory _category, bool _hpVisible, sf::Vector2f _scale, float _angle;
*/
struct enemySettings {
	ls::Tile tile;
	int damage;
	int hp;
	bool hpVisible;
	float restitution;
	float friction;
	float angle;
	Scene* scene;
	_entityCategory category;
	sf::Vector2f velocity;
	sf::Vector2f scale;

	enemySettings() {};
	enemySettings(ls::Tile _tile, int _damage, int _hp, Scene* _scene, float _restitution, float _friction, sf::Vector2f _velocity, _entityCategory _category, bool _hpVisible, sf::Vector2f _scale, float _angle)
		: tile(_tile), damage(_damage), hp(_hp), scene(_scene), restitution(_restitution), friction(_friction), velocity(_velocity), category(_category), hpVisible(_hpVisible), scale(_scale), angle(_angle) {
	}
};

class EnemySettings {
public:
	static enemySettings LoadSettings(_enemyType type, Scene* scene);
};

