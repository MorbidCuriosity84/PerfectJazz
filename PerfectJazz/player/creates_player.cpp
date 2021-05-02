#include "creates_player.h"
#include "../settings/settings_holder.h"
#include "../services/load_save_game.h"

using namespace std;
using namespace sf;
playerSettings _playerSettings;
textureSettings _playerBulletTextureHelper;
textureSettings _playerSpriteTextureHelper;
weaponSettings _playerWeaponSettings;
bulletSettings _playerBulletSettings;
void Player::createPlayer(Scene* _scene) {

	player = _scene->makeEntity();
	player->setView(mainView);

	_playerSettings = PlayerSettings::LoadSettings(PLAYER1, _scene);
	_playerSpriteTextureHelper = TextureHelpingSettings::LoadSettings(PLAYER1, _scene);
	_playerWeaponSettings = WeaponSettings::LoadSettings(MACHINE_GUN, _scene);
	_playerWeaponSettings.fireTimer = 0.f;
	_playerWeaponSettings.fireTime = 1.f;
	_playerBulletSettings = BulletSettings::LoadSettings(TYPE1, _scene);
	_playerBulletSettings.direction = 1.f;
	_playerBulletSettings.category = FRIENDLY_BULLET;
	_playerWeaponSettings.direction = -1.f;
	_playerBulletTextureHelper = TextureHelpingSettings::LoadSettings(TYPE1, _scene);

	if (Engine::isLoading) {
		LoadSaveGame::loadGame();
		_playerSettings = SettingsHolder::pSettings;
		_playerWeaponSettings = SettingsHolder::wSettings;
		_playerBulletSettings = SettingsHolder::bSettings;
		_playerBulletTextureHelper = SettingsHolder::bTexHelper;
		_playerSpriteTextureHelper = SettingsHolder::pTexHelper;
	}

	player->addComponent<PlayerComponent>(_playerSpriteTextureHelper, _playerBulletTextureHelper, _playerSettings, _playerWeaponSettings, _playerBulletSettings);
}

void Player::createPlayerFromSettings(Scene* _scene) {
	player.reset();
	player = _scene->makeEntity();
	player->setView(mainView);	

	player->addComponent<PlayerComponent>(SettingsHolder::pTexHelper, SettingsHolder::bTexHelper, SettingsHolder::pSettings, SettingsHolder::wSettings, SettingsHolder::bSettings);
}