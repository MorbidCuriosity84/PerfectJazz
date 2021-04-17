#pragma once
#include <ecm.h>
#include <SFML/Graphics.hpp>
#include "../components/cmp_sprite.h"
#include "../components/cmp_weapon.h"
#include "../components/cmp_bullet.h"
#include "../game.h"
using namespace sf;

/*
* @param int _damage, int _hp, Scene* _scene, float _restitution, float _friction, sf::Vector2f _velocity, _entityCategory _category, bool _hpVisible, sf::Vector2f _scale, float _angle;
*/
struct playerSettings {
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

	playerSettings() {};
	playerSettings(int _damage, int _hp, Scene* _scene, float _restitution, float _friction, sf::Vector2f _velocity, _entityCategory _category, bool _hpVisible, sf::Vector2f _scale, float _angle)
		: damage(_damage), hp(_hp), scene(_scene), restitution(_restitution), friction(_friction), velocity(_velocity), category(_category), hpVisible(_hpVisible), scale(_scale), angle(_angle) {
	}
};
class PlayerComponent : public Component {
protected:
	textureSettings _playerTextureHelper;
	textureSettings _bulletTextureHelper;
	playerSettings _playerSettings;
	weaponSettings _weaponSettings;
	bulletSettings _bulletSettings;

public:
	void Load();
	void render() override {};
	void update(double dt);

	PlayerComponent() = delete;
	explicit PlayerComponent(Entity* p, textureSettings playerTextureHelper, textureSettings bulletTextureHelper, playerSettings playerSettings, weaponSettings weaponSettings, bulletSettings bulletSettings);
};