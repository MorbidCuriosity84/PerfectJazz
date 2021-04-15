#include "load_enemies.h"
#include "../game.h"
#include <LevelSystem.h>
#include "cmp_enemy.h"
#include "../components/cmp_sprite.h"
#include "../components/cmp_weapon.h"

using namespace std;
using namespace sf;

void LoadEnemies::initiliseEnemies(std::string _waveFile, Scene* _scene) {

	ls::loadLevelFile("res/levels/" + _waveFile + ".txt", mainView.getSize().x / 16);
	auto ho = Engine::getWindowSize().y - (ls::getHeight() * mainView.getSize().x / 16);
	ls::setOffset(Vector2f(0, ho));

	for (int index = 0; index < ls::findTiles(ls::AIRMAN).size(); index++) {
		auto en = _scene->makeEntity();
		en->setView(mainView);

		wepSettings wepSettings(150, .4f, .005f, { 0.f,-300.f }, { 1.f,1.f }, ENEMY_MISSILE, _scene, 2.0f, 1, false, 0.f);
		enemySettings settings(100, 2000, 2.5, _scene, ls::AIRMAN, .4f, .005f, { 0.f,-300.f }, ENEMY, true, { 1.f,1.f }, { 1.f,1.f }, 0.f, 0.f, ENEMY_BULLET, wepSettings);

		auto spriteTexture = make_shared<sf::Texture>();
		auto spriteRectangle = make_shared<sf::IntRect>();
		textureHelper spriteHelp("res/img/enemies/enemy1_900.png", 1, 2, 0, 0, spriteTexture, spriteRectangle, 1.5);
		auto wepSpriteTexture = make_shared<sf::Texture>();
		auto wepSpriteRectangle = make_shared<sf::IntRect>();
		textureHelper wepHelp("res/img/weapons/Fx_01.png", 1, 3, 0, 2, wepSpriteTexture, wepSpriteRectangle, 2.0);

		auto loadEnemy = en->addComponent<EnemyComponent>(spriteHelp, wepHelp, settings);
		loadEnemy->Load(index);
	}

	for (int index = 0; index < ls::findTiles(ls::SERGEANT).size(); index++) {
		auto en = _scene->makeEntity();
		en->setView(mainView);

		wepSettings wepSettings(150, .4f, .005f, { 0.f,-300.f }, { 1.f,1.f }, ENEMY_MISSILE, _scene,2.0f, 1, false, 0.f);
		enemySettings settings(100, 2000, 2.5, _scene, ls::SERGEANT, .4f, .005f, { 0.f,-300.f }, ENEMY, true, { 1.f,1.f }, { 1.f,1.f }, 0.f, 0.f, ENEMY_BULLET, wepSettings);

		auto spriteTexture = make_shared<sf::Texture>();
		auto spriteRectangle = make_shared<sf::IntRect>();
		textureHelper spriteHelp("res/img/enemies/enemy2_900.png", 1, 2, 0, 0, spriteTexture, spriteRectangle, 1.5);
		auto wepSpriteTexture = make_shared<sf::Texture>();
		auto wepSpriteRectangle = make_shared<sf::IntRect>();
		textureHelper wepHelp("res/img/weapons/Fx_02.png", 1, 3, 0, 2, wepSpriteTexture, wepSpriteRectangle, 2.0);

		auto loadEnemy = en->addComponent<EnemyComponent>(spriteHelp, wepHelp, settings);
		loadEnemy->Load(index);
	}

	for (int index = 0; index < ls::findTiles(ls::COLONEL).size(); index++) {
		auto en = _scene->makeEntity();
		en->setView(mainView);

		wepSettings wepSettings(150, .4f, .005f, { 0.f,-300.f }, { 1.f,1.f }, ENEMY_MISSILE, _scene, 2.0f, 1, false, 0.f);
		enemySettings settings(100, 2000, 2.5, _scene, ls::COLONEL, .4f, .005f, { 0.f,-300.f }, ENEMY, true, { 1.f,1.f }, { 1.f,1.f }, 0.f, 0.f, ENEMY_BULLET, wepSettings);

		auto spriteTexture = make_shared<sf::Texture>();
		auto spriteRectangle = make_shared<sf::IntRect>();
		textureHelper spriteHelp("res/img/enemies/enemy3_900.png", 1, 2, 0, 0, spriteTexture, spriteRectangle, 1.5);
		auto wepSpriteTexture = make_shared<sf::Texture>();
		auto wepSpriteRectangle = make_shared<sf::IntRect>();
		textureHelper wepHelp("res/img/weapons/Fx_02.png", 1, 3, 0, 2, wepSpriteTexture, wepSpriteRectangle, 2.0);

		auto loadEnemy = en->addComponent<EnemyComponent>(spriteHelp, wepHelp, settings);
		loadEnemy->Load(index);
	}
}
