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

//Creates a player entity, assigning the player settings, weapons settings, 
//bullets settings, and texture helper settings.
void Player::createPlayer(Scene* _scene) {

	player = _scene->makeEntity();
	player->setView(mainView);

	_playerSettings = PlayerSettings::LoadSettings(PLAYER1, _scene);
	_playerSpriteTextureHelper = TextureHelpingSettings::LoadSettings(PLAYER1, _scene);
	_playerWeaponSettings = WeaponSettings::LoadSettings(PLAYER_GUN, _scene);
	_playerWeaponSettings.sound = MISSILE_FIRE_2;
	_playerWeaponSettings.fireTimer = 0.f;
	_playerWeaponSettings.fireTime = 1.f;
	_playerWeaponSettings.volume = 0.35f;
	_playerBulletSettings = BulletSettings::LoadSettings(TYPE_PLAYER, _scene);
	_playerBulletTextureHelper = TextureHelpingSettings::LoadSettings(TYPE_PLAYER, _scene);

	//Add the player component
	player->addComponent<PlayerComponent>(_playerSpriteTextureHelper, _playerBulletTextureHelper, _playerSettings, _playerWeaponSettings, _playerBulletSettings);
}
//Creates a player component from settings. Loaded games will use this method
//to create a new player from saved settings
void Player::createPlayerFromSettings(Scene* _scene) {
	player.reset();
	player = _scene->makeEntity();
	player->setView(mainView);	

	player->addComponent<PlayerComponent>(SettingsHolder::pTexHelper, SettingsHolder::bTexHelper, SettingsHolder::pSettings, SettingsHolder::wSettings, SettingsHolder::bSettings);
}