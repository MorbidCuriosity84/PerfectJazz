#pragma once
#include <ecm.h>
#include <SFML/Graphics.hpp>
#include "LevelSystem.h"
#include "../components/cmp_sprite.h"
#include "../components/cmp_weapon.h"

using namespace sf;

/*
* @param int dam, int hp, double ft, Scene* scene, ls::Tile t, float res, float fr, sf::Vector2f vel, _entityCategory cat, bool hpV, sf::Vector2f wScale, sf::Vector2f sScale, _entityCategory wepCat;
*/
struct enemySettings {
	ls::Tile _tile;
	int _damage;
	int _hp;
	bool _hpVisible;
	float _restitution;
	float _friction;
	float _spriteAngle;
	Scene* _scene;
	_entityCategory _cat;
	sf::Vector2f _velocity;
	sf::Vector2f _spriteScale;

	enemySettings() {};
	enemySettings(int dam, int hp, Scene* scene, ls::Tile t, float res, float fr, sf::Vector2f vel, _entityCategory cat, bool hpV, sf::Vector2f sScale, float sAngle)
		: _damage(dam), _hp(hp), _spriteScale(sScale), _spriteAngle(sAngle), _scene(scene), _tile(t), _restitution(res), _friction(fr), _velocity(vel), _cat(cat), _hpVisible(hpV) {
	}
};

class EnemyComponent : public Component {
protected:
	textureHelper _spriteHelper;
	enemySettings _settings;

public:
	void Load(int index);
	void render() override {};
	void update(double dt);

	EnemyComponent() = delete;
	explicit EnemyComponent(Entity* p, textureHelper spriteTexHelp, enemySettings settings);
};

