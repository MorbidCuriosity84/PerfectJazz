#include "create_enemies.h"
#include <LevelSystem.h>
#include "cmp_enemy.h"
#include "ecm.h"
#include "../game.h"
#include "../components/cmp_sprite.h"

using namespace std;
using namespace sf;

textureHelper _spriteHelp;
textureHelper _wepHelp;
enemySettings _settings;

void CreateEnemies::initiliseEnemies(std::string _waveFile, Scene* _scene) {

	ls::loadLevelFile("res/levels/" + _waveFile + ".txt", mainView.getSize().x / 16);
	auto ho = Engine::getWindowSize().y - (ls::getHeight() * mainView.getSize().x / 16);
	ls::setOffset(Vector2f(0, ho));

	for (int index = 0; index < ls::findTiles(ls::AIRMAN).size(); index++) {
		setType(AIRMAN, _scene);
		auto en = _scene->makeEntity();
		en->setView(mainView);
		auto loadEnemy = en->addComponent<EnemyComponent>(_spriteHelp, _settings);
		loadEnemy->Load(index);
	}
	for (int index = 0; index < ls::findTiles(ls::SERGEANT).size(); index++) {
		setType(SERGEANT, _scene);
		auto en = _scene->makeEntity();
		en->setView(mainView);
		auto loadEnemy = en->addComponent<EnemyComponent>(_spriteHelp, _settings);
		loadEnemy->Load(index);
	}	
	for (int index = 0; index < ls::findTiles(ls::COLONEL).size(); index++) {
		setType(COLONEL, _scene);
		auto en = _scene->makeEntity();
		en->setView(mainView);
		auto loadEnemy = en->addComponent<EnemyComponent>(_spriteHelp, _settings);
		loadEnemy->Load(index);
	}
}

void CreateEnemies::setType(_enemyType type, Scene* _scene) {

	auto spriteTexture = make_shared<sf::Texture>();
	auto spriteRectangle = make_shared<sf::IntRect>();

	switch (type) {
	case AIRMAN:
	{
		textureHelper spriteHelp("res/img/enemies/enemy1_900.png", 1, 2, 0, 0, spriteTexture, spriteRectangle, 1.5);
		enemySettings settings(100, 1000, _scene, ls::AIRMAN, .4f, .005f, { 0.f,-300.f }, ENEMY, true, { 1.f,1.f }, 0);
		_spriteHelp = spriteHelp;
		_settings = settings;
		break;
	}
	case SERGEANT:
	{
		textureHelper spriteHelp("res/img/enemies/enemy2_900.png", 1, 2, 0, 0, spriteTexture, spriteRectangle, 1.5);
		enemySettings settings(100, 2000, _scene, ls::SERGEANT, .4f, .005f, { 0.f,-300.f }, ENEMY, true, { 1.f,1.f }, 0);
		_spriteHelp = spriteHelp;
		_settings = settings;
		break;
	}
	case COLONEL:
	{
		textureHelper spriteHelp("res/img/enemies/enemy3_900.png", 1, 2, 0, 0, spriteTexture, spriteRectangle, 1.5);
		enemySettings settings(100, 3000, _scene, ls::COLONEL, .4f, .005f, { 0.f,-300.f }, ENEMY, true, { 1.f,1.f }, 0);
		_spriteHelp = spriteHelp;
		_settings = settings;
		break;
	}
	default:
		break;
	}
}

