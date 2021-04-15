#pragma once
#include <ecm.h>
#include "cmp_damage.h"
#include "cmp_sprite.h"
#include "../game.h"
#include <system_renderer.h>

using namespace sf;
using namespace std;

struct wepSettings {
	float restitution;
	float friction;
	sf::Vector2f velocity;	
	_entityCategory wepCat;
	bool hpVisible;
	sf::Vector2f wepSpriteScale;	
	Scene* scene;	

	wepSettings() {}

	wepSettings(float res, float fr, sf::Vector2f vel, sf::Vector2f wScale, _entityCategory wepCat, Scene* scene)
		: wepSpriteScale(wScale), restitution(res), friction(fr), velocity(vel), wepCat(wepCat), scene(scene) {}
};

class WeaponComponent : public Component
{
protected:
	std::shared_ptr<DamageComponent> _damage;
	std::shared_ptr<SpriteComponent> _sprite;
	_entityCategory _category;
	double _firetime; 
	uint16_t _spread; //number to spawn
	sf::Vector2f _direction;
	textureHelper _wepHelper;
	wepSettings _wepSettings;

public:
	virtual void fire() = 0;
	virtual void update(double dt) = 0;
	virtual void render() = 0;

	WeaponComponent() = delete;
	WeaponComponent(Entity* const p);
	~WeaponComponent();

	std::shared_ptr<DamageComponent> getDamage() const;
	void setDamage(std::shared_ptr<DamageComponent> d);
	std::shared_ptr<SpriteComponent> getSprite() const;
	void setSprite(std::shared_ptr<SpriteComponent> s);
	_entityCategory getCategory() const;
	void setCategory(_entityCategory cat);
	double getFiretime() const;
	void setFiretime(double ft);
	uint16_t getSpread() const;
	void setSpread(uint16_t sp);
	Vector2f getDirection() const;
	void setDirection(Vector2f dir);
	wepSettings getSettings()  const;
};

