#include "create_player.h"
#include "cmp_player.h"
#include <LevelSystem.h>
#include "../game.h"

using namespace std;
using namespace sf;

void Player::createPlayer(Scene* _scene) {
	auto p = _scene->makeEntity();
	p->setView(mainView);
	playerSettings pSettings;
	pSettings.damage = 100;
	pSettings.hp = 100000;
	pSettings.scene = _scene;
	pSettings.restitution = 0.4f;
	pSettings.friction = 0.005f;
	pSettings.velocity = { 0.f,100.f };
	pSettings.category = PLAYER_BODY;
	pSettings.hpVisible = false;
	pSettings.scale = { 1.f,1.f };
	pSettings.angle = 0;
	
	auto playerSpriteTexture = make_shared<sf::Texture>();
	auto playerSpriteRectangle = make_shared<sf::IntRect>();
	textureSettings playerTextureHelper;
	playerTextureHelper.spriteFilename = "res/img/player/player_900.png";
	playerTextureHelper.spriteRows = 2;
	playerTextureHelper.spriteCols = 5;
	playerTextureHelper.desiredRow = 0;
	playerTextureHelper.desiredCol = 2;

	playerTextureHelper.spriteTexture = playerSpriteTexture;	
	playerTextureHelper.spriteRectangle = playerSpriteRectangle;
	playerTextureHelper.spriteTimer = 1.5;

	weaponSettings wSettings;
	wSettings.damage = 100;
	wSettings.fireTime = 1.5f;
	wSettings.fireTimer = 1.5f;
	wSettings.numBullets = 1;
	wSettings.scene = _scene;
	wSettings.direction = -1.f;

	bulletSettings bSettings;
	bSettings.damage = 100;
	bSettings.hp = 100;
	bSettings.lifetime = 10.f;
	bSettings.scene = _scene;
	bSettings.angle = 90.f;
	bSettings.category = FRIENDLY_BULLET;
	bSettings.direction = 1.f;
	bSettings.velocity = Vector2f(0.f, 100.f);


	auto bulletSpriteTexture = make_shared<sf::Texture>();
	auto bulletSpriteRectangle = make_shared<sf::IntRect>();
	textureSettings bulletTextureHelper;
	bulletTextureHelper.spriteFilename = "res/img/weapons/Fx_01.png";
	bulletTextureHelper.spriteRows = 1;
	bulletTextureHelper.spriteCols = 3;
	bulletTextureHelper.desiredRow = 0;
	bulletTextureHelper.desiredCol = 2;
	bulletTextureHelper.spriteTexture = bulletSpriteTexture;
	bulletTextureHelper.spriteRectangle = bulletSpriteRectangle;
	bulletTextureHelper.spriteTimer = 2.0;

	auto loadPlayer = p->addComponent<PlayerComponent>(playerTextureHelper, bulletTextureHelper, pSettings, wSettings, bSettings);
	loadPlayer->Load();
}
