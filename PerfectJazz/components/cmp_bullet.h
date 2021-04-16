#pragma once
#include "cmp_physics.h"
#include "cmp_damage.h"
#include "../game.h"
#include <ecm.h>

struct bulletSettings {
	float lifetime;
	int damage;
	int hp;
	_entityCategory category;
	float angle;
	float direction;
	Scene* scene;
	sf::Vector2f velocity;
	sf::Vector2f spriteScale;

	bulletSettings() {};
	bulletSettings(float _lifeTime, int _damage, int _hp, float _angle, float _direction, Scene* _scene, sf::Vector2f _velocity, sf::Vector2f _spriteScale, _entityCategory _category)
		: lifetime(_lifeTime), damage(_damage), hp(_hp), angle(_angle), direction(_direction), scene(_scene), velocity(_velocity), spriteScale(_spriteScale), category(_category) {
	}
};

class BulletComponent : public Component {
protected:
	shared_ptr<SpriteComponent> _bulletSprite;
	textureHelper _bulletTextHelper;
	bulletSettings _settings;
public:
	void update(double dt) override;
	void render() override {}
	void createBullet();

	explicit BulletComponent(Entity* p, bulletSettings settings, textureHelper bulletTexHelper);
	BulletComponent() = delete;
};


