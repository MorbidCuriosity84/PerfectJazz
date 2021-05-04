#include "cmp_beserker.h"
#include "cmp_beserker.h"
#include "levelManager.h"
#include "../movement/cmp_radar.h"

//Constructor for beserker component.
Beserker::Beserker(Entity* p, textureSettings enemyTextureHelper, textureSettings bulletTextureHelper, enemySettings enemySettings, weaponSettings weaponSettings, bulletSettings bulletSettings, int index)
	: EnemyComponent(p, enemyTextureHelper, bulletTextureHelper, enemySettings, weaponSettings, bulletSettings, index), beserkTime(3.f), lifetime(15.f), goneBeserk(false), seeking(false)
{}

void Beserker::update(double dt)
{	
	//Triggers the goBeserk function when the counter is over 5
	if (Scene::deadEnemies > 5 && !goneBeserk) {
		goBeserk();
		//Scene::deadEnemies = 0;
	}

	_parent->setRotation(_parent->getRotation() + 2.f);
	//If the beseker enemy is out to the left or to the right, it's parent is cleared of components, and set not alive
	//the entity is then set off screen, ready to be used again for a new enemy
	if (_parent->getPosition().x > _parent->getView().getSize().x || _parent->getPosition().x < 0) {
		_parent->setAlive(false);
		_parent->setVisible(false);
		physicsCMP->getBody()->SetActive(false);
		physicsCMP->getBody()->SetUserData(nullptr);
		physicsCMP->teleport(Vector2f(-500.f, -500.f));
		_parent->clearComponents();		
		LevelManager::enemyCount--;				
		return;
	}
	EnemyComponent::update(dt);
}

//Adds a machine gun and rocket launcher weapon components to the beserker
void Beserker::goBeserk()
{
	goneBeserk = true;
	//add machine gun
	_weaponSettings = WeaponSettings::LoadSettings(MACHINE_GUN, _parent->scene);
	_weaponSettings.numBulletsUpgradeCount = 2;
	_bulletSettings = BulletSettings::LoadSettings(TYPE2, _parent->scene);
	_bulletTextureHelper = TextureHelpingSettings::LoadSettings(TYPE2, _parent->scene);
	_bulletSettings.damage = _bulletSettings.damage * 2;			
	weapon2 = _parent->addComponent<WeaponComponent>(_weaponSettings, _bulletSettings, _bulletTextureHelper);

	//add missile launcher
	_weaponSettings = WeaponSettings::LoadSettings(ROCKET_LAUNCHER, _parent->scene);
	_bulletSettings = BulletSettings::LoadSettings(TYPE3, _parent->scene);
	_bulletTextureHelper = TextureHelpingSettings::LoadSettings(TYPE3, _parent->scene);
	_bulletSettings.damage = _bulletSettings.damage * 2;	
	weapon3 = _parent->addComponent<WeaponComponent>(_weaponSettings, _bulletSettings, _bulletTextureHelper);
	//Set's hp to triple its initial value
	hpCMP->setHP(hpCMP->getHP() * 3);
}
