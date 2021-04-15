#pragma once
#include <ecm.h>
#include <SFML/Graphics.hpp>
#include "LevelSystem.h"
#include "../components/cmp_sprite.h"
#include "../game.h"

using namespace sf;

/*
* @param int dam, int hp, double ft, Scene* scene, ls::Tile t, float res, float fr, sf::Vector2f vel, _entityCategory cat, bool hpV, sf::Vector2f wScale, sf::Vector2f sScale, _entityCategory wepCat;
*/
struct playerSettings {
	int _damage;
	int _hp;
	double _fireTime;
	double _fireTimer;
	Scene* _scene;
	float _restitution;
	float _friction;
	float _wepAngle;
	float _spriteAngle;
	sf::Vector2f _velocity;
	_entityCategory _cat;
	_entityCategory _wepCat;
	bool _hpVisible;
	sf::Vector2f _wepSpriteScale;
	sf::Vector2f _spriteScale;

	playerSettings(int dam, int hp, double ft, Scene* scene, float res, float fr, sf::Vector2f vel, _entityCategory cat, bool hpV, sf::Vector2f wScale, sf::Vector2f sScale, float wAngle, float sAngle, _entityCategory wepCat)
		: _damage(dam), _hp(hp), _fireTime(ft), _fireTimer(ft), _wepSpriteScale(wScale), _spriteScale(sScale), _wepAngle(wAngle), _spriteAngle(sAngle), _scene(scene), _restitution(res), _friction(fr), _velocity(vel), _cat(cat), _hpVisible(hpV), _wepCat(wepCat) {
	}
};
class PlayerComponent : public Component {
protected:
	double _fireTime;
	Scene* _scene;
	textureHelper _spriteHelper;
	ls::Tile _tileType;
	textureHelper _weaponSpriteHelper;
	playerSettings _settings;

public:
	void fire();
	void Load();
	void render() override {};
	void update(double dt);

	PlayerComponent() = delete;
	explicit PlayerComponent(Entity* p, textureHelper spriteTexHelp, textureHelper wepSpriteTexHelp, playerSettings settings);
};