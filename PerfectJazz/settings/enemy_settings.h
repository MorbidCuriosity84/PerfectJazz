#pragma once
#include "../game.h"
#include <ecm.h>
#include <LevelSystem.h>
#include "../components/cmp_sprite.h"
#include "../components/cmp_weapon.h"
#include "../components/cmp_bullet.h"

/*
* @param ls::Tile _tile, int _damage, int _hp, Scene* _scene, float _restitution, float _friction, sf::Vector2f _velocity, _entityCategory _category, bool _hpVisible, sf::Vector2f _scale, float _angle;
*/
//Defines all the fields for the enemies settings
struct enemySettings {
	ls::Tile tile;
	int damage;
	int hp;
	bool hpVisible;
	float restitution;
	float friction;
	float angle;
	_enemyType type;
	Scene* scene;
	_entityCategory category;
	sf::Vector2f velocity;
	sf::Vector2f scale;	
	SOUNDS sound;

	//Default constructor
	enemySettings() {};	
	//Constructor with parameters
	enemySettings(ls::Tile _tile, int _damage, int _hp, Scene* _scene, float _restitution, float _friction, sf::Vector2f _velocity, _entityCategory _category, _enemyType _type, bool _hpVisible, sf::Vector2f _scale, float _angle, SOUNDS snd)
		: tile(_tile), damage(_damage), hp(_hp), scene(_scene), restitution(_restitution), friction(_friction), velocity(_velocity), category(_category), type(_type), hpVisible(_hpVisible), scale(_scale), angle(_angle), sound(snd) {
	}
};

class EnemySettings {
public:
	//Creates an instance of the struct enemySettings depending of the type of enemy
	static enemySettings LoadSettings(_enemyType type, Scene* scene);
	static void scale(int factor, enemySettings& settings);
};

