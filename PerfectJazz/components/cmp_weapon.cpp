#include <math.h>
#include "cmp_weapon.h"
#include "cmp_bullet.h"
#include "../pools/entityPool.h"
#include "../game.h"
#include "../services/sound_Queue.h"
#include "../lib_maths/maths.h"
#include "../services/randomNumber.h"

// Fires the weapon, using a bullet from the entity and updating its settings
// according to the type of bullet and weapon
void WeaponComponent::fire() {

	// Checks whehter the entity is within the screen boundaries, other wise it won't fire
	if (_parent->getPosition().y > 0) {
		// Sets values for the degradation, spread angle needed in order to shoot more than one bullet with different angles
		int odd = _wSettings.numBulletsUpgradeCount * 2 + 1;
		float deg = 30.f / (float)odd;
		float spread = 1.f;
		float angleStart = _parent->getRotation();
		// If the bullet upgrade is bigger than 1, means there are more than 1 bullet
		// The odd value will set the bullet count as 1, 3, 5, 7, 9 or 11, when the upgrade count is 0, 1, 2, 3, 4 or 5 
		if (_wSettings.numBulletsUpgradeCount + 1 > 1) {
			for (int i = 0; i < odd; i++) {
				if (i % 2 != 0) {
					deg *= i;
				}
				// Creates a reference to a bullet from the pool entity and sets the position, rotation and view
				// using its parent's values.
				auto pS = _parent->GetCompatibleComponent<SpriteComponent>();
				shared_ptr<Entity> bullet = EntityPool::pool[EntityPool::poolPointer++];
				bullet->clearComponents();
				bullet->setView(_parent->getView());
				bullet->setPosition({ _parent->getPosition().x, _parent->getPosition().y + (pS[0]->getSprite().getTextureRect().height / 2 * _wSettings.direction) });
				bullet->setRotation(_parent->getRotation());
				bullet->addTag("Bullet");
				// Adds a bullet component and a physics component to the bullet entity
				// and sets the direction and the alive and visible state to true.
				auto bul = bullet->addComponent<BulletComponent>(_bSettings, _bulletTextureHelper);
				float len = length(bul->physicsCMP->getVelocity());
				Vector2f direction = Vector2f(len * spread * cos(deg), bul->physicsCMP->getVelocity().y);
				bul->physicsCMP->setVelocity(direction);
				bullet->setAlive(true);
				bullet->setVisible(true);
				spread *= -1.f;
			}
			// Plays a sound with different pitch when the bullet is fired
			sounds[_wSettings.sound].setPitch(1.f + sin(accumulation) * .025f);
			sounds[_wSettings.sound].setVolume(15.f);
			sounds[_wSettings.sound].play();
		}

		// Creates a reference to a bullet from the pool entity and sets the position, rotation and view
		// using its parent's values. This bullet will always be in the middle
		auto pS = _parent->GetCompatibleComponent<SpriteComponent>();
		shared_ptr<Entity> bullet = EntityPool::pool[EntityPool::poolPointer++];
		bullet->clearComponents();
		bullet->setView(_parent->getView());
		bullet->setPosition({ _parent->getPosition().x, _parent->getPosition().y + (pS[0]->getSprite().getTextureRect().height / 2 * _wSettings.direction) });
		bullet->setRotation(_parent->getRotation());
		bullet->addTag("Bullet");
		auto bul = bullet->addComponent<BulletComponent>(_bSettings, _bulletTextureHelper);
		bullet->setView(_parent->getView());
		bullet->setAlive(true);
		bullet->setVisible(true);

		sounds[_wSettings.sound].setPitch(1.f + sin(accumulation) * .025f);
		sounds[_wSettings.sound].setVolume(15.f);
		sounds[_wSettings.sound].play();
	}	
}

// Updates the weapon component, firing the weapon when the timer is equal or below 0
void WeaponComponent::update(double dt) {
	accumulation += dt;
	_wSettings.fireTimer -= dt;
	if (_wSettings.fireTimer <= 0.f) {
		fire();
		_wSettings.fireTimer = _wSettings.fireTime - (_wSettings.fireTime * 0.15 * _wSettings.firerateUpgradeCount);
	}
}
// Sets the damage for the weapon component
void WeaponComponent::setDamage(uint16_t damage) {
	_bSettings.damage = damage;
}
// Gets the damage for the weapon component
uint16_t WeaponComponent::getDamage() const {
	return _bSettings.damage;
}
// Constructor for the weapon component
WeaponComponent::WeaponComponent(Entity* p, weaponSettings wSettings, bulletSettings bSettings, textureSettings bTextureHelper)
	: Component(p), _wSettings(wSettings), _bSettings(bSettings), _bulletTextureHelper(bTextureHelper), accumulation(0.f) {}