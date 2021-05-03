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

//Creates the enemies based on a txt file with the wave
void Enemies::createEnemies(std::string _waveFile, Scene* _scene) {

	//Reads the file and, with the help of the level system, gets a position for each of the enemies on the file
	ls::loadLevelFile("res/levels/" + _waveFile + ".txt", (round)((mainView.getSize().x / 16)));
	auto ho = (round)(Engine::getWindowSize().y) - (round)((ls::getHeight() * mainView.getSize().y / 16));
	ls::setOffset(Vector2f((mainView.getSize().y) / 32, ho));

	int index = 0, airman_index = 0, sergeant_index = 0, colonel_index = 0, berserk_index = 0, kami_index = 0, boss_index = 0;

	//Using the height and width of the wave file, assign one the entities from the enemy pool to a type of enemy
	//depending on the enemy type.
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
		//If enemy of type beserker, add component beserker and movement component
		if (t == ls::BESERKER) {
			auto bes = en->addComponent<Beserker>(_enemyTextureHelper, _bulletTextureHelper, _enemySettings, _weaponSettings, _bulletSettings, index);
			en->addComponent<MovementComponent>(_enemySettings.velocity, ls::getTilePosition(ls::findTiles(_enemySettings.tile)[index]), true);
		}
		//If enemy of type kamikaze, add component kamikaze and movement component
		else if (t == ls::KAMIKAZE) {
			en->addComponent<Kamikaze>(_enemyTextureHelper, _bulletTextureHelper, _enemySettings, _weaponSettings, _bulletSettings, index);
			en->addComponent<MovementComponent>(_enemySettings.velocity, ls::getTilePosition(ls::findTiles(_enemySettings.tile)[index]), true);
		}
		//If enemy of type boss, add component boss and movement component. Sets linger to true
		else if (t == ls::BOSS) {
			auto boss = en->addComponent<Boss>(_enemyTextureHelper, _bulletTextureHelper, _enemySettings, _weaponSettings, _bulletSettings, index);
			boss->moveCMP = chooseMovement(t, en, ls::getTilePosition(ls::findTiles(_enemySettings.tile)[index]));
			boss->moveCMP->isLinger(true);
		}
		//Else, add an enemy and also movement component
		else {
			en->addComponent<EnemyComponent>(_enemyTextureHelper, _bulletTextureHelper, _enemySettings, _weaponSettings, _bulletSettings, index);
			en->addComponent<MovementComponent>(_enemySettings.velocity, ls::getTilePosition(ls::findTiles(_enemySettings.tile)[index]), true);
		}
		//Sets the entites alive and increases the enemy count
		en->setAlive(true);
		LevelManager::enemyCount++;
	}
}

//Sets the different settings for each of the enemy types, depending on the type of enemy
void Enemies::setType(_enemyType type, Scene* _scene) {

	switch (type) {
	case AIRMAN: {
		_enemySettings = EnemySettings::LoadSettings(AIRMAN, _scene);
		_enemyTextureHelper = TextureHelpingSettings::LoadSettings(AIRMAN, _scene);
		_weaponSettings = WeaponSettings::LoadSettings(GUN, _scene);
		_bulletSettings = BulletSettings::LoadSettings(TYPE1, _scene);
		_bulletTextureHelper = TextureHelpingSettings::LoadSettings(TYPE1, _scene);
		break;
	}

	case SERGEANT: {
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
	case BANSAI: {
		_enemySettings = EnemySettings::LoadSettings(BANSAI, _scene);
		_enemyTextureHelper = TextureHelpingSettings::LoadSettings(BANSAI, _scene);
		_weaponSettings = WeaponSettings::LoadSettings(EMPTY, _scene);
		_bulletSettings = BulletSettings::LoadSettings(TYPE3, _scene);
		_bulletTextureHelper = TextureHelpingSettings::LoadSettings(TYPE3, _scene);
		break;
	}
	case MADMAN: {
		_enemySettings = EnemySettings::LoadSettings(MADMAN, _scene);
		_enemyTextureHelper = TextureHelpingSettings::LoadSettings(MADMAN, _scene);
		_weaponSettings = WeaponSettings::LoadSettings(MACHINE_GUN, _scene);
		_bulletSettings = BulletSettings::LoadSettings(TYPE2, _scene);
		_bulletTextureHelper = TextureHelpingSettings::LoadSettings(TYPE2, _scene);
		break;
	}
	case BOSS: {
		_enemySettings = EnemySettings::LoadSettings(BOSS, _scene);
		_enemyTextureHelper = TextureHelpingSettings::LoadSettings(BOSS, _scene);
		_weaponSettings = WeaponSettings::LoadSettings(MACHINE_GUN, _scene);
		_bulletSettings = BulletSettings::LoadSettings(TYPE2, _scene);
		_bulletTextureHelper = TextureHelpingSettings::LoadSettings(TYPE2, _scene);
		break;
	}
	default:
		break;
	}
}

//Sets the movement component depending on the type of enemy
shared_ptr<MovementComponent> Enemies::chooseMovement(ls::Tile tile, shared_ptr<Entity> en, Vector2f initPos) {
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
		return en->addComponent<SineMovementComponent>(_enemySettings.velocity, 60.f, initPos, true);
		break;
	case ls::BOSS:
		return en->addComponent<MovementComponent>(_enemySettings.velocity, initPos, true);
		break;
	}
}



