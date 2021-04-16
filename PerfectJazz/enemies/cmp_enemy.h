#pragma once
#include <ecm.h>
#include <SFML/Graphics.hpp>
#include "LevelSystem.h"
#include "../components/cmp_sprite.h"
#include "../game.h"
#include "../components/cmp_missile.h"

using namespace sf;

/*
* @param int dam, int hp, double ft, Scene* scene, ls::Tile t, float res, float fr, sf::Vector2f vel, _entityCategory cat, bool hpV, sf::Vector2f wScale, sf::Vector2f sScale, float _wepAngle, float _spriteAngle, _entityCategory wepCat, wepSettings wSettings
*/
struct enemySettings {
	int _damage;
	int _hp;
	double _fireTime;
	double _fireTimer;
	Scene* _scene;
	ls::Tile _tile;	
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
	wepSettings weaponSettings;

	enemySettings(int dam, int hp, double ft, Scene* scene, ls::Tile t, float res, float fr, sf::Vector2f vel, _entityCategory cat, bool hpV, sf::Vector2f wScale, sf::Vector2f sScale, float wAngle, float sAngle, _entityCategory wepCat, wepSettings wSettings)
		: _damage(dam), _hp(hp), _fireTime(ft), _wepSpriteScale(wScale), _spriteScale(sScale), _wepAngle(wAngle), _spriteAngle(sAngle), _scene(scene), _tile(t), _restitution(res), _friction(fr), _velocity(vel), _cat(cat), _hpVisible(hpV), _wepCat(wepCat), weaponSettings(wSettings) {}


};

class EnemyComponent : public Component
{
protected:		
	double _fireTime;
	Scene* _scene;
	textureHelper _spriteHelper;	
	ls::Tile _tileType;
	textureHelper _weaponSpriteHelper;
	enemySettings _settings;
	shared_ptr<WeaponComponent> _weapon;	

public:
	void fire();
	void Load(int index);
	void render() override {};
	void update(double dt);

	EnemyComponent() = delete;	
	explicit EnemyComponent(Entity* p, textureHelper spriteTexHelp, textureHelper wepSpriteTexHelp, enemySettings settings);

	void addWeapon(shared_ptr<WeaponComponent> wep);
	shared_ptr<WeaponComponent> getWeapon() const;
};

