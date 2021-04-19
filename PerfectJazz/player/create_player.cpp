#include "create_player.h"
#include "cmp_player.h"
#include <LevelSystem.h>
#include "../game.h"
#include "../settings/player_settings.h"

using namespace std;
using namespace sf;

playerSettings _playerSettings;
textureSettings _playerBulletTextureHelper;
textureSettings _playerSpriteTextureHelper;
weaponSettings _playerWeaponSettings;
bulletSettings _playerBulletSettings;
shared_ptr<Entity> player;

void Player::createPlayer(Scene* _scene) {
	auto p = _scene->makeEntity();
	player = p;
	player->setView(mainView);

	_playerSettings = PlayerSettings::LoadSettings(PLAYER1, _scene);
	_playerSpriteTextureHelper = TextureHelpingSettings::LoadSettings(PLAYER1, _scene);
	_playerWeaponSettings = WeaponSettings::LoadSettings(GUN, _scene);
	_playerBulletSettings = BulletSettings::LoadSettings(TYPE1, _scene);
	_playerBulletSettings.direction = 1.f;
	_playerBulletSettings.category = FRIENDLY_BULLET;
	_playerWeaponSettings.direction = -1.f;
	_playerBulletTextureHelper = TextureHelpingSettings::LoadSettings(TYPE1, _scene);

	auto loadPlayer = player->addComponent<PlayerComponent>(_playerSpriteTextureHelper, _playerBulletTextureHelper, _playerSettings, _playerWeaponSettings, _playerBulletSettings);
	loadPlayer->Load();
}
