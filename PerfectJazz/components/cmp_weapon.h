#pragma once
#include <ecm.h>
#include "cmp_damage.h"
#include "cmp_sprite.h"
#include "../game.h"
#include <system_renderer.h>

using namespace sf;
using namespace std;

/*
* @param uint16_t dam, float restitution, float firetime, sf::Vector2f vel, sf::Vector2f wScale, _entityCategory wepCat, Scene* scene, double firetime, uint16_t spread, bool seeking, float range;
*/
struct wepSettings {
	uint16_t damage;
	float restitution;
	float friction;
	sf::Vector2f velocity;	
	_entityCategory wepCat;	
	sf::Vector2f wepSpriteScale;	
	Scene* scene;	
	uint16_t spread;
	double firetime;
	bool seeking;
	float range;

	wepSettings() {}

	wepSettings(uint16_t dam, float res, float fr, sf::Vector2f vel, sf::Vector2f wScale, _entityCategory wepCat, Scene* scene, double ft, uint16_t sp, bool seek, float rng)
		: wepSpriteScale(wScale), restitution(res), friction(fr), velocity(vel), wepCat(wepCat), scene(scene), damage(dam), firetime(ft), spread(sp), seeking(seek), range(rng) {}
};

class WeaponComponent : public Component
{
protected:
	//std::shared_ptr<DamageComponent> _damage;
	//std::shared_ptr<SpriteComponent> _sprite;
	_entityCategory _category;
	double _firetime; 
	uint16_t _spread; //number to spawn
	sf::Vector2f _direction;
	textureHelper _wepHelper;
	wepSettings _wepSettings;

public:
	virtual void fire() = 0;
	void update(double dt) override;
	void render() override;

	WeaponComponent(Entity* p, wepSettings w);	
	~WeaponComponent();

	/*std::shared_ptr<DamageComponent> getDamage() const;
	void setDamage(std::shared_ptr<DamageComponent> d);
	std::shared_ptr<SpriteComponent> getSprite() const;
	void setSprite(std::shared_ptr<SpriteComponent> s);*/
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

