#include "creates_enemies.h"
#include "cmp_enemy.h"
#include "../pools/enemyPool.h"
#include "levelManager.h"
#include "../movement/cmp_move_sine.h"
#include "cmp_beserker.h"
#include "cmp_kamikaze.h"
#include "cmp_boss.h"

using namespace std;
using namespace sf;

textureSettings _enemyTextureHelper;
textureSettings _bulletTextureHelper;
enemySettings _enemySettings;
weaponSettings _weaponSettings;
bulletSettings _bulletSettings;

void Enemies::createEnemies(std::string _waveFile, Scene* _scene) {

	ls::loadLevelFile("res/levels/" + _waveFile + ".txt", (round)((mainView.getSize().x / 16)));
	auto ho = (round)(Engine::getWindowSize().y) - (round)((ls::getHeight() * mainView.getSize().y / 16));
	ls::setOffset(Vector2f((mainView.getSize().y) / 32, ho));

	int index = 0, airman_index = 0, sergeant_index = 0, colonel_index = 0, berserk_index = 0, kami_index = 0, boss_index = 0;

	//MARK - I was thinking this could be condensed into a single loop
	//If we get ls::_height and ls_width we can use that to loop through h x w
	// 
	//Assuming w = width and h = height then for( i = 0; i < w * h; i++)
	//   => ls::getTile ( i % w, floor( i / w) ) 
	//Apparently c++ handles integer division by doing floor anyway
	//At least i think so. Let me know what you think but I'm sure Thomas said something about
	//a double loop being bad for memory allocation/reads/writes. It seems to work anyway.

	for (int i = 0; i < ls::_height * ls::_width; i++) {
		ls::Tile t = ls::getTile({ i % ls::_width, i / ls::_width });
		if (t == ls::EMPTY) { continue; }

		auto en = EnemyPool::en_pool[EnemyPool::en_poolPointer++];
		en->setView(mainView);

		if (t == ls::AIRMAN) { setType(AIRMAN, _scene); index = airman_index++; }
		if (t == ls::SERGEANT) { setType(SERGEANT, _scene); index = sergeant_index++; }
		if (t == ls::COLONEL) { setType(COLONEL, _scene); index = colonel_index++; }		
		if (t == ls::KAMIKAZE) { setType(BANSAI, _scene); index = kami_index++; }
		if (t == ls::BESERKER) { setType(MADMAN, _scene); index = berserk_index++; }
		if (t == ls::BOSS) { setType(BOSS, _scene); index = boss_index++; }
	
		if (t == ls::BESERKER) {
			auto bes = en->addComponent<Beserker>(_enemyTextureHelper, _bulletTextureHelper, _enemySettings, _weaponSettings, _bulletSettings, index);
			bes->moveCMP = chooseMovement(t, en, ls::getTilePosition(ls::findTiles(_enemySettings.tile)[index]));
		}else if( t == ls::KAMIKAZE) {
			en->addComponent<Kamikaze>(_enemyTextureHelper, _bulletTextureHelper, _enemySettings, _weaponSettings, _bulletSettings, index);			
		}
		else if (t == ls::BOSS) {
			auto boss = en->addComponent<Boss>(_enemyTextureHelper, _bulletTextureHelper, _enemySettings, _weaponSettings, _bulletSettings, index);
			boss->moveCMP = chooseMovement(t, en, ls::getTilePosition(ls::findTiles(_enemySettings.tile)[index]));
			boss->moveCMP->isLinger(true);
		}
		else {
			en->addComponent<EnemyComponent>(_enemyTextureHelper, _bulletTextureHelper, _enemySettings, _weaponSettings, _bulletSettings, index);
			chooseMovement(t, en, ls::getTilePosition(ls::findTiles(_enemySettings.tile)[index]));
		}
		en->setAlive(true);
		LevelManager::enemyCount++;
	}
}

void Enemies::setType(_enemyType type, Scene* _scene) {

	switch (type) {
	case AIRMAN:
	{
		_enemySettings = EnemySettings::LoadSettings(AIRMAN, _scene);
		_enemyTextureHelper = TextureHelpingSettings::LoadSettings(AIRMAN, _scene);
		_weaponSettings = WeaponSettings::LoadSettings(GUN, _scene);
		_bulletSettings = BulletSettings::LoadSettings(TYPE1, _scene);
		_bulletTextureHelper = TextureHelpingSettings::LoadSettings(TYPE1, _scene);
		break;
	}

	case SERGEANT:
	{
		_enemySettings = EnemySettings::LoadSettings(SERGEANT, _scene);		
		_enemyTextureHelper = TextureHelpingSettings::LoadSettings(SERGEANT, _scene);
		_weaponSettings = WeaponSettings::LoadSettings(MACHINE_GUN, _scene);		
		_bulletSettings = BulletSettings::LoadSettings(TYPE2, _scene);
		_bulletTextureHelper = TextureHelpingSettings::LoadSettings(TYPE2, _scene);
		break;
	}
	case COLONEL:
	{
		_enemySettings = EnemySettings::LoadSettings(COLONEL, _scene);
		_enemyTextureHelper = TextureHelpingSettings::LoadSettings(COLONEL, _scene);
		_weaponSettings = WeaponSettings::LoadSettings(ROCKET_LAUNCHER, _scene);
		_bulletSettings = BulletSettings::LoadSettings(TYPE3, _scene);
		_bulletTextureHelper = TextureHelpingSettings::LoadSettings(TYPE3, _scene);
		break;
	}
	case BANSAI:
		_enemySettings = EnemySettings::LoadSettings(BANSAI, _scene);
		_enemyTextureHelper = TextureHelpingSettings::LoadSettings(BANSAI, _scene);
		_weaponSettings = WeaponSettings::LoadSettings(EMPTY, _scene);
		_bulletSettings = BulletSettings::LoadSettings(TYPE3, _scene);
		_bulletTextureHelper = TextureHelpingSettings::LoadSettings(TYPE3, _scene);
	case MADMAN:
		_enemySettings = EnemySettings::LoadSettings(MADMAN, _scene);
		_enemyTextureHelper = TextureHelpingSettings::LoadSettings(MADMAN, _scene);
		_weaponSettings = WeaponSettings::LoadSettings(MACHINE_GUN, _scene);
		_bulletSettings = BulletSettings::LoadSettings(TYPE2, _scene);
		_bulletTextureHelper = TextureHelpingSettings::LoadSettings(TYPE2, _scene);
	case BOSS:
		_enemySettings = EnemySettings::LoadSettings(BOSS, _scene);
		_enemyTextureHelper = TextureHelpingSettings::LoadSettings(BOSS, _scene);
		_weaponSettings = WeaponSettings::LoadSettings(MACHINE_GUN, _scene);
		_bulletSettings = BulletSettings::LoadSettings(TYPE2, _scene);
		_bulletTextureHelper = TextureHelpingSettings::LoadSettings(TYPE2, _scene);
	default:
		break;
	}
}

shared_ptr<MovementComponent> Enemies::chooseMovement(ls::Tile tile, shared_ptr<Entity> en, Vector2f initPos)
{
	switch (tile) {
	case ls::AIRMAN:
		return en->addComponent<MovementComponent>(_enemySettings.velocity, initPos, true);		
		break;
	case ls::SERGEANT:
		return en->addComponent<SineMovementComponent>(Vector2f(_enemySettings.velocity), 45.f, initPos, true);
		break;
	case ls::COLONEL:
		return en->addComponent<MovementComponent>(_enemySettings.velocity, initPos, true);
		break;
	case ls::KAMIKAZE:
		return en->addComponent<MissileMovementComponent>(_enemySettings.velocity, true, _enemySettings.category);
		break;
	case ls::BESERKER:
		return en->addComponent<SineMovementComponent>(_enemySettings.velocity, 60.f,  initPos, true);
		break;
	case ls::BOSS:
		return en->addComponent<MovementComponent>(_enemySettings.velocity, initPos, true);
		break;
	}
}



