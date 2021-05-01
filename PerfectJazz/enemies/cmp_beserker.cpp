#include "cmp_beserker.h"
#include "levelManager.h"
#include "../movement/cmp_radar.h"

Beserker::Beserker(Entity* p, textureSettings enemyTextureHelper, textureSettings bulletTextureHelper, enemySettings enemySettings, weaponSettings weaponSettings, bulletSettings bulletSettings, int index)
	: EnemyComponent(p, enemyTextureHelper, bulletTextureHelper, enemySettings, weaponSettings, bulletSettings, index)
{
	beserkTime = 10.f;
	goneBeserk = false;
	deadEnemies = 0;
	damageMultiplier = 3;
	enemyCountAtLoad = LevelManager::enemyCount;
	moveCMP = p->addComponent<MovementComponent>(_enemySettings.velocity, p->getPosition(), false);
	goBeserk();
}

void Beserker::update(double dt)
{	
	if (_parent->getPosition().y < 50.f - Engine::getWindowSize().y /1.5f ) {
		//moveCMP->isLinger(true);
	}

	if (goneBeserk) {		
		beserkTime -= dt;
		if (beserkTime < 0) {
			//moveCMP->isLinger(false);
			weapon2->~WeaponComponent();
			weapon3->~WeaponComponent();
			moveCMP->~MovementComponent();
			moveCMP = _parent->addComponent<MissileMovementComponent>(_enemySettings.velocity, true, BESERKER);
			_parent->addComponent<RadarComponent>(8.f, ENEMY_MISSILE_RADAR);
		}
	}	
	_parent->setRotation(_parent->getRotation() + 2.f);
	EnemyComponent::update(dt);
}

void Beserker::goBeserk()
{
	goneBeserk = true;
	//add machine gun
	_weaponSettings = WeaponSettings::LoadSettings(MACHINE_GUN, _parent->scene);
	_weaponSettings.numBulletsUpgradeCount = 3;
	_bulletSettings = BulletSettings::LoadSettings(TYPE2, _parent->scene);
	_bulletTextureHelper = TextureHelpingSettings::LoadSettings(TYPE2, _parent->scene);
	_bulletSettings.damage = _bulletSettings.damage * damageMultiplier;			
	weapon2 = _parent->addComponent<WeaponComponent>(_weaponSettings, _bulletSettings, _bulletTextureHelper);

	//add missile launcher
	_weaponSettings = WeaponSettings::LoadSettings(ROCKET_LAUNCHER, _parent->scene);
	_bulletSettings = BulletSettings::LoadSettings(TYPE3, _parent->scene);
	_bulletTextureHelper = TextureHelpingSettings::LoadSettings(TYPE3, _parent->scene);
	_bulletSettings.damage = _bulletSettings.damage * damageMultiplier;	
	weapon3 = _parent->addComponent<WeaponComponent>(_weaponSettings, _bulletSettings, _bulletTextureHelper);

	hpCMP->setHP(hpCMP->getHP() * 3);
}
