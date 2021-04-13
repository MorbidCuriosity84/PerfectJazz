#pragma once
#include <ecm.h>
#include <SFML/Graphics.hpp>
#include "LevelSystem.h"
#include "../components/cmp_sprite.h"

using namespace sf;

struct enemySettings {
	int _damage;
	int _hp;
	sf::Vector2f _wepSpriteScale;
	sf::Vector2f _spriteScale;

	enemySettings(int damage, int hp, sf::Vector2f wepSpriteScale, sf::Vector2f spriteScale)
		: _damage(damage), _hp(hp), _wepSpriteScale(wepSpriteScale), _spriteScale(spriteScale) {}
};

class EnemyComponent : public Component
{
protected:		
	double _fireTime;
	Scene* _scene;
	textureHelper _spriteHelper;	
	ls::Tile _tileType;
	textureHelper _weaponSpriteHelper;

public:
	void fire();
	void Load(int index);
	void render() override {};
	void update(double dt);

	EnemyComponent() = delete;
	explicit EnemyComponent(Entity* p, double fireTime, Scene* scene, ls::Tile tileType, textureHelper spriteTexHelp, textureHelper wepSpriteTexHelp);	
};

