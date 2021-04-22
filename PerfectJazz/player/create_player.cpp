#include "create_player.h"

using namespace std;
using namespace sf;
	playerSettings _playerSettings;
	textureSettings _playerBulletTextureHelper;
	textureSettings _playerSpriteTextureHelper;
	weaponSettings _playerWeaponSettings;
	bulletSettings _playerBulletSettings;
	shared_ptr<Entity> player;
void Player::createPlayer(Scene* _scene) {
	player = _scene->makeEntity();
	player->setView(mainView);

	_playerSettings = PlayerSettings::LoadSettings(PLAYER1, _scene);
	_playerSpriteTextureHelper = TextureHelpingSettings::LoadSettings(PLAYER1, _scene);
	_playerWeaponSettings = WeaponSettings::LoadSettings(GUN, _scene);
	_playerWeaponSettings.fireTimer = 0.25f;
	_playerWeaponSettings.fireTime = 0.25f;
	_playerBulletSettings = BulletSettings::LoadSettings(TYPE1, _scene);
	_playerBulletSettings.direction = 1.f;
	_playerBulletSettings.category = FRIENDLY_BULLET;
	_playerWeaponSettings.direction = -1.f;
	_playerBulletTextureHelper = TextureHelpingSettings::LoadSettings(TYPE1, _scene);

	auto loadPlayer = player->addComponent<PlayerComponent>(_playerSpriteTextureHelper, _playerBulletTextureHelper, _playerSettings, _playerWeaponSettings, _playerBulletSettings);
	//loadPlayer->Load();
}
