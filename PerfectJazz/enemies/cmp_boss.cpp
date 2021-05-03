#include "cmp_boss.h"
#include "../pools/enemyPool.h"
#include "cmp_kamikaze.h"
#include "levelManager.h"
#include "../player/cmp_player.h"

textureSettings boss_eTexHelper;
textureSettings boss_bTexHelper;
enemySettings boss_eSettings;
weaponSettings boss_wSettings;
bulletSettings boss_bSettings;

//Updates the behaviour of the boss enemy
void Boss::update(double dt) {
	spriteCMP->getSprite().setRotation(boss_eSettings.angle);
	trigger += dt;
	//At 0.75, 0.5 and 0.25 of the max hp, the boss enemy gets invisible
	if (hpCMP->getHP() < 0.75 * hpCMP->getMaxHP() && inv1) {
		invincible = true;
		inv1 = false;
	}

	if (hpCMP->getHP() < 0.5 * hpCMP->getMaxHP() && inv2) {
		invincible = true;
		inv2 = false;
	}
	if (hpCMP->getHP() < 0.25 * hpCMP->getMaxHP() && inv3) {
		invincible = true;
		inv3 = false;
	}	

	//If invicible is up, set the body of the boss to not collide
	//and sets the player visible/invisible to perform a flickering animation
	if (invincible) {
		invTimer -= dt;
		physicsCMP->setCategory(NO_COLLIDE);	
		if (trigger < 0.2) {
			_parent->setVisible(false);
		}
		if (trigger >= 0.2 && trigger < 0.4) {
			_parent->setVisible(true);
		}
		if (trigger >= 0.4) {
			trigger = 0;
		}
	}
	//IF timer is below 0, spawn kamikazes
	if (invTimer < 0) {
		invTimer = 5.f;
		for (int i = 0; i < numKamikazes; i++) {
			spawnKamikazes(i);
		}				
		physicsCMP->setCategory(ENEMY_BODY);
		invincible = false;		
	}
	//If the boss hp is equal or below 0, sets the enemy to not alive and innactive, and clear the components.
	//Sends the entity off screen so it's ready to be use again by the enemy pool.
	if (hpCMP->getHP() <= 0) {
		_parent->setAlive(false);
		_parent->setVisible(false);
		physicsCMP->getBody()->SetActive(false);
		physicsCMP->getBody()->SetUserData(nullptr);
		_parent->setPosition(Vector2f(-100.f, -100.f));
		player->GetCompatibleComponent<PlayerComponent>()[0].get()->_playerSettings.score += 5000;
		sounds[_enemySettings.sound].setPitch(1.f + sin(accumulation) * .025f);
		sounds[_enemySettings.sound].setVolume(35.f);
		sounds[_enemySettings.sound].play();
		_parent->clearComponents();
		LevelManager::enemyCount--;
	}
}
//Spawns a kamikaze enemy. 
void Boss::spawnKamikazes(int i) {
	auto en = EnemyPool::en_pool[EnemyPool::en_poolPointer++];
	en->setView(mainView);
	boss_eSettings = EnemySettings::LoadSettings(BANSAI, _parent->scene);
	boss_eTexHelper = TextureHelpingSettings::LoadSettings(BANSAI, _parent->scene);
	boss_wSettings = WeaponSettings::LoadSettings(EMPTY, _parent->scene);
	boss_bSettings = BulletSettings::LoadSettings(TYPE3, _parent->scene);
	boss_bTexHelper = TextureHelpingSettings::LoadSettings(TYPE3, _parent->scene);
	auto kam = en->addComponent<Kamikaze>(boss_eTexHelper, boss_bTexHelper, boss_eSettings, boss_wSettings, boss_bSettings, 0);
	en->setPosition(_parent->getPosition());
	en->setAlive(true);
	//Sets the angle and direction of the kamikaze
	float len = length(kam->physicsCMP->getVelocity());
	float deg = 60.f / (float)(60.f / numKamikazes);
	Vector2f direction = Vector2f(len * cos(deg * i), kam->physicsCMP->getVelocity().y);
	kam->physicsCMP->setVelocity(direction);
	LevelManager::enemyCount++;
}

void Boss::switchSprite(double trigger)
{
	if (trigger < 0.2) {
		_parent->setVisible(false);
	}
	if (trigger >= 0.2 && trigger < 0.4) {
		_parent->setVisible(true);
	}
	if (trigger >= 0.4) {
		trigger = 0;
	}
}

//Constructor for boss component.
//Sets two weapons, a machine gun and a missile launcher with its own settings each of them
Boss::Boss(Entity* p, textureSettings enemyTextureHelper, textureSettings bulletTextureHelper, enemySettings enemySettings, weaponSettings weaponSettings, bulletSettings bulletSettings, int index)
	: EnemyComponent(p, enemyTextureHelper, bulletTextureHelper, enemySettings, weaponSettings, bulletSettings, index), invTimer(5.f), invincible(false), numKamikazes(4) {
	//add machine gun
	_weaponSettings = WeaponSettings::LoadSettings(MACHINE_GUN, _parent->scene);
	_weaponSettings.numBulletsUpgradeCount = 2;
	_bulletSettings = BulletSettings::LoadSettings(TYPE2, _parent->scene);
	_bulletTextureHelper = TextureHelpingSettings::LoadSettings(TYPE2, _parent->scene);
	_parent->addComponent<WeaponComponent>(_weaponSettings, _bulletSettings, _bulletTextureHelper);

	//add missile launcher
	_weaponSettings = WeaponSettings::LoadSettings(ROCKET_LAUNCHER, _parent->scene);
	_weaponSettings.fireTime = 2.f;
	_weaponSettings.numBulletsUpgradeCount = 2;
	_bulletSettings = BulletSettings::LoadSettings(TYPE3, _parent->scene);
	_bulletTextureHelper = TextureHelpingSettings::LoadSettings(TYPE3, _parent->scene);
	_parent->addComponent<WeaponComponent>(_weaponSettings, _bulletSettings, _bulletTextureHelper);

	physicsCMP->setCategory(ENEMY_BODY);

}
