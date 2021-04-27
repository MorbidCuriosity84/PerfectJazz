#include <LevelSystem.h>
#include "creates_enemies.h"
#include "cmp_enemy.h"

using namespace std;
using namespace sf;

textureSettings _enemyTextureHelper;
textureSettings _bulletTextureHelper;
enemySettings _enemySettings;
weaponSettings _weaponSettings;
bulletSettings _bulletSettings;

void Enemies::createEnemies(std::string _waveFile, Scene* _scene) {

	// CARLOS TO-DO windows resolution
	ls::loadLevelFile("res/levels/" + _waveFile + ".txt", (round)((mainView.getSize().x / 15)));
	auto ho = (round)(Engine::getWindowSize().y) - (round)((ls::getHeight() * mainView.getSize().y / 16));
	ls::setOffset(Vector2f((mainView.getSize().y) / 32, ho));

	int index = 0, airman_index = 0, sergeant_index = 0, colonel_index = 0;
	for (size_t y = 0; y < ls::_height; ++y) {
		for (size_t x = 0; x < ls::_width; ++x) {
			ls::Tile t = ls::getTile({ x, y });
			if (t == ls::EMPTY) {continue;}

			auto en = _scene->makeEntity();
			en->setView(mainView);

			if (t == ls::AIRMAN) { setType(AIRMAN, _scene); index = airman_index++; }
			if (t == ls::SERGEANT) { setType(SERGEANT, _scene); index = sergeant_index++;}
			if (t == ls::COLONEL) {	setType(COLONEL, _scene); index = colonel_index++;}

			en->addComponent<EnemyComponent>(_enemyTextureHelper, _bulletTextureHelper, _enemySettings, _weaponSettings, _bulletSettings, index);
		}
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
	default:
		break;
	}
}

