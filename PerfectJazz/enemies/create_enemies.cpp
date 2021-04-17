#include "create_enemies.h"
#include <LevelSystem.h>
#include "cmp_enemy.h"
#include "ecm.h"
#include "../game.h"
#include "../components/cmp_sprite.h"

using namespace std;
using namespace sf;

textureHelper _enemyTextureHelper;
textureHelper _bulletTextureHelper;
enemySettings _enemySettings;
wepSettings _weaponSettings;
bulletSettings _bulletSettings;

void CreateEnemies::initiliseEnemies(std::string _waveFile, Scene* _scene) {

	ls::loadLevelFile("res/levels/" + _waveFile + ".txt", mainView.getSize().x / 16);
	auto ho = Engine::getWindowSize().y - (ls::getHeight() * mainView.getSize().x / 16);
	ls::setOffset(Vector2f(0, ho));

	wepSettings wSettings;
	wSettings.damage = 100;
	wSettings.fireTime = 1.5f;
	wSettings.fireTimer = 1.5f;
	wSettings.numBullets = 1;
	wSettings.scene = _scene;
	wSettings.direction = 1;

	bulletSettings bSettings;
	bSettings.damage = 100;
	bSettings.hp = 100;
	bSettings.lifetime = 10.f;
	bSettings.scene = _scene;
	bSettings.angle = 90.f;
	bSettings.category = ENEMY_BULLET;
	bSettings.direction = -1;
	bSettings.velocity = Vector2f(0.f, 100.f);

	int index = 0, airman_index = 0, sergeant_index = 0, colonel_index = 0;
	for (size_t y = 0; y < ls::_height; ++y) {
		for (size_t x = 0; x < ls::_width; ++x) {
			ls::Tile t = ls::getTile({ x, y });
			if (t == ls::EMPTY) {continue;}

			auto en = _scene->makeEntity();
			en->setView(mainView);

			if (t == ls::AIRMAN) { setType(AIRMAN, _scene); index = airman_index++; }
			if (t == ls::SERGEANT) {setType(SERGEANT, _scene); index = sergeant_index++;}
			if (t == ls::COLONEL) {	setType(COLONEL, _scene); index = colonel_index++;}

			auto loadEnemy = en->addComponent<EnemyComponent>(_enemyTextureHelper, _bulletTextureHelper, _enemySettings, wSettings, bSettings);
			loadEnemy->Load(index);
		}
	}
}

void CreateEnemies::setType(_enemyType type, Scene* _scene) {

	auto enemySpriteTexture = make_shared<sf::Texture>();
	auto enemySpriteRectangle = make_shared<sf::IntRect>();
	auto bulletSpriteTexture = make_shared<sf::Texture>();
	auto bulletSpriteRectangle = make_shared<sf::IntRect>();

	switch (type) {
	case AIRMAN:
	{
		_enemySettings.damage = 100;
		_enemySettings.hp = 1000;
		_enemySettings.scene = _scene;
		_enemySettings.restitution = 0.4f;
		_enemySettings.friction = 0.005f;
		_enemySettings.velocity = { 0.f,-300.f };
		_enemySettings.tile = ls::AIRMAN;
		_enemySettings.category = ENEMY;
		_enemySettings.hpVisible = true;
		_enemySettings.scale = { 1.f,1.f };
		_enemySettings.angle = 0;

		_enemyTextureHelper.spriteFilename = "res/img/enemies/enemy1_900.png";
		_enemyTextureHelper.spriteRows = 1;
		_enemyTextureHelper.spriteCols = 2;
		_enemyTextureHelper.desiredRow = 0;
		_enemyTextureHelper.desiredCol = 0;
		_enemyTextureHelper.spriteTexture = enemySpriteTexture;
		_enemyTextureHelper.spriteRectangle = enemySpriteRectangle;
		_enemyTextureHelper.spriteTimer = 1.5;

		_weaponSettings.damage = 100;
		_weaponSettings.fireTime = 1.5f;
		_weaponSettings.fireTimer = 1.5f;
		_weaponSettings.numBullets = 1;
		_weaponSettings.scene = _scene;
		_weaponSettings.direction = 1.f;

		_bulletSettings.damage = 100;
		_bulletSettings.hp = 100;
		_bulletSettings.lifetime = 10.f;
		_bulletSettings.scene = _scene;
		_bulletSettings.angle = 0;
		_bulletSettings.category = ENEMY_BULLET;
		_bulletSettings.direction = -1.f;
		_bulletSettings.velocity = Vector2f(0.f, 100.f);

		_bulletTextureHelper.spriteFilename = "res/img/weapons/Fx_01.png";
		_bulletTextureHelper.spriteRows = 1;
		_bulletTextureHelper.spriteCols = 3;
		_bulletTextureHelper.desiredRow = 0;
		_bulletTextureHelper.desiredCol = 2;
		_bulletTextureHelper.spriteTexture = bulletSpriteTexture;
		_bulletTextureHelper.spriteRectangle = bulletSpriteRectangle;
		_bulletTextureHelper.spriteTimer = 2.0;
		break;
	}

	case SERGEANT:
	{
		_enemySettings.damage = 200;
		_enemySettings.hp = 2500;
		_enemySettings.scene = _scene;
		_enemySettings.restitution = 0.4f;
		_enemySettings.friction = 0.005f;
		_enemySettings.velocity = { 0.f,-300.f };
		_enemySettings.tile = ls::SERGEANT;
		_enemySettings.category = ENEMY;
		_enemySettings.hpVisible = true;
		_enemySettings.scale = { 1.f,1.f };
		_enemySettings.angle = 0;

		_enemyTextureHelper.spriteFilename = "res/img/enemies/enemy2_900.png";
		_enemyTextureHelper.spriteRows = 1;
		_enemyTextureHelper.spriteCols = 2;
		_enemyTextureHelper.desiredRow = 0;
		_enemyTextureHelper.desiredCol = 0;
		_enemyTextureHelper.spriteTexture = enemySpriteTexture;
		_enemyTextureHelper.spriteRectangle = enemySpriteRectangle;
		_enemyTextureHelper.spriteTimer = 1.5;

		_weaponSettings.damage = 100;
		_weaponSettings.fireTime = 1.5f;
		_weaponSettings.fireTimer = 1.5f;
		_weaponSettings.numBullets = 1;
		_weaponSettings.scene = _scene;
		_weaponSettings.direction = 1.f;

		_bulletSettings.damage = 100;
		_bulletSettings.hp = 100;
		_bulletSettings.lifetime = 10.f;
		_bulletSettings.scene = _scene;
		_bulletSettings.angle = 0;
		_bulletSettings.category = ENEMY_BULLET;
		_bulletSettings.direction = -1.f;
		_bulletSettings.velocity = Vector2f(0.f, 100.f);

		_bulletTextureHelper.spriteFilename = "res/img/weapons/Fx_02.png";
		_bulletTextureHelper.spriteRows = 1;
		_bulletTextureHelper.spriteCols = 3;
		_bulletTextureHelper.desiredRow = 0;
		_bulletTextureHelper.desiredCol = 2;
		_bulletTextureHelper.spriteTexture = bulletSpriteTexture;
		_bulletTextureHelper.spriteRectangle = bulletSpriteRectangle;
		_bulletTextureHelper.spriteTimer = 2.0;
		break;
	}
	case COLONEL:
	{
		_enemySettings.damage = 300;
		_enemySettings.hp = 3500;
		_enemySettings.scene = _scene;
		_enemySettings.restitution = 0.4f;
		_enemySettings.friction = 0.005f;
		_enemySettings.velocity = { 0.f,-300.f };
		_enemySettings.tile = ls::COLONEL;
		_enemySettings.category = ENEMY;
		_enemySettings.hpVisible = true;
		_enemySettings.scale = { 1.f,1.f };
		_enemySettings.angle = 0;

		_enemyTextureHelper.spriteFilename = "res/img/enemies/enemy3_900.png";
		_enemyTextureHelper.spriteRows = 1;
		_enemyTextureHelper.spriteCols = 2;
		_enemyTextureHelper.desiredRow = 0;
		_enemyTextureHelper.desiredCol = 0;
		_enemyTextureHelper.spriteTexture = enemySpriteTexture;
		_enemyTextureHelper.spriteRectangle = enemySpriteRectangle;
		_enemyTextureHelper.spriteTimer = 1.5;

		_weaponSettings.damage = 100;
		_weaponSettings.fireTime = 1.5f;
		_weaponSettings.fireTimer = 1.5f;
		_weaponSettings.numBullets = 1;
		_weaponSettings.scene = _scene;
		_weaponSettings.direction = 1.f;

		_bulletSettings.damage = 100;
		_bulletSettings.hp = 100;
		_bulletSettings.lifetime = 10.f;
		_bulletSettings.scene = _scene;
		_bulletSettings.angle = 0;
		_bulletSettings.category = ENEMY_BULLET;
		_bulletSettings.direction = -1.f;
		_bulletSettings.velocity = Vector2f(0.f, 100.f);

		_bulletTextureHelper.spriteFilename = "res/img/weapons/Fx_01.png";
		_bulletTextureHelper.spriteRows = 1;
		_bulletTextureHelper.spriteCols = 3;
		_bulletTextureHelper.desiredRow = 0;
		_bulletTextureHelper.desiredCol = 2;
		_bulletTextureHelper.spriteTexture = bulletSpriteTexture;
		_bulletTextureHelper.spriteRectangle = bulletSpriteRectangle;
		_bulletTextureHelper.spriteTimer = 2.0;
		break;
	}
	default:
		break;
	}
}

