#include "cmp_beserker.h"
#include "levelManager.h"
#include "../movement/cmp_radar.h"

Beserker::Beserker(Entity* p, textureSettings enemyTextureHelper, textureSettings bulletTextureHelper, enemySettings enemySettings, weaponSettings weaponSettings, bulletSettings bulletSettings, int index)
	: EnemyComponent(p, enemyTextureHelper, bulletTextureHelper, enemySettings, weaponSettings, bulletSettings, index), beserkTime(3.f), lifetime(15.f), goneBeserk(false), seeking(false)
{}

void Beserker::update(double dt)
{	
	if (Scene::deadEnemies > 5) {
		goBeserk();
		//Scene::deadEnemies = 0;
	}

	_parent->setRotation(_parent->getRotation() + 2.f);

	if (_parent->getPosition().x > _parent->getView().getSize().x || _parent->getPosition().x < 0) {
		_parent->setAlive(false);
		_parent->setVisible(false);
		physicsCMP->getBody()->SetActive(false);
		physicsCMP->getBody()->SetUserData(nullptr);
		_parent->setPosition(Vector2f(-100.f, -100.f));
		_parent->clearComponents();		
		LevelManager::enemyCount--;				
		return;
	}
	EnemyComponent::update(dt);
}

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

	hpCMP->setHP(hpCMP->getHP() * 3);
}
