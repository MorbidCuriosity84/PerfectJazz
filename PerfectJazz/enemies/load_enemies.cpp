#include "load_enemies.h"
#include "../game.h"
#include <LevelSystem.h>
#include "cmp_enemy_airman.h"
#include "cmp_enemy_sergeant.h"
#include "cmp_enemy_colonel.h"
#include "cmp_enemy.h"
#include "../components/cmp_sprite.h"

using namespace std;
using namespace sf;



void LoadEnemies::initiliseEnemies(std::string _waveFile, Scene* _scene) {

	ls::loadLevelFile("res/levels/" + _waveFile + ".txt", mainView.getSize().x / 16);
	auto ho = Engine::getWindowSize().y - (ls::getHeight() * mainView.getSize().x / 16);
	ls::setOffset(Vector2f(0, ho));

	int index;
	for (int index = 0; index < ls::findTiles(ls::AIRMAN).size(); index++) {
		auto en = _scene->makeEntity();
		en->setView(mainView);
		/*en->addComponent<AirManEnemyComponent>(_scene);
		auto loadEnemy = en->GetCompatibleComponent<AirManEnemyComponent>();		*/
		
		auto spriteTexture = make_shared<sf::Texture>();
		auto spriteRectangle = make_shared<sf::IntRect>();
		textureHelper spriteHelp("res/img/enemies/enemy1_900.png", 1, 2, 0, 0, spriteTexture, spriteRectangle, 1.5);				
		auto _wepSpriteTexture = make_shared<sf::Texture>();
		auto _wepSpriteRectangle = make_shared<sf::IntRect>();
		textureHelper wepHelp("res/img/weapons/Fx_01.png", 1, 3, 0, 0, _wepSpriteTexture, _wepSpriteRectangle, 2.0);

		auto loadEnemy = en->addComponent<EnemyComponent>(1.5f, _scene, ls::AIRMAN, spriteHelp, wepHelp);		
		loadEnemy->Load(index);
	}

	for (int index = 0; index < ls::findTiles(ls::SERGEANT).size(); index++) {
		auto en = _scene->makeEntity();
		en->setView(mainView);

		auto spriteTexture = make_shared<sf::Texture>();
		auto spriteRectangle = make_shared<sf::IntRect>();
		textureHelper spriteHelp("res/img/enemies/enemy2_900.png", 1, 2, 0, 0, spriteTexture, spriteRectangle, 1.5);
		auto _wepSpriteTexture = make_shared<sf::Texture>();
		auto _wepSpriteRectangle = make_shared<sf::IntRect>();
		textureHelper wepHelp("res/img/weapons/Fx_02.png", 1, 3, 0, 0, _wepSpriteTexture, _wepSpriteRectangle, 2.0);

		auto loadEnemy = en->addComponent<EnemyComponent>(2.5f, _scene, ls::SERGEANT, spriteHelp, wepHelp);
		loadEnemy->Load(index);		

		/*en->addComponent<SergeantEnemyComponent>(_scene);
		auto loadEnemy = en->GetCompatibleComponent<SergeantEnemyComponent>();
		loadEnemy[0]->Load(index);*/
	}

	for (int index = 0; index < ls::findTiles(ls::COLONEL).size(); index++) {
		auto en = _scene->makeEntity();
		en->setView(mainView);
		en->addComponent<ColonelEnemyComponent>(_scene);

		auto spriteTexture = make_shared<sf::Texture>();
		auto spriteRectangle = make_shared<sf::IntRect>();
		textureHelper spriteHelp("res/img/enemies/enemy3_900.png", 1, 2, 0, 0, spriteTexture, spriteRectangle, 1.5);
		auto _wepSpriteTexture = make_shared<sf::Texture>();
		auto _wepSpriteRectangle = make_shared<sf::IntRect>();
		textureHelper wepHelp("res/img/weapons/Fx_02.png", 1, 3, 0, 0, _wepSpriteTexture, _wepSpriteRectangle, 2.0);

		auto loadEnemy = en->addComponent<EnemyComponent>(3.5f, _scene, ls::COLONEL, spriteHelp, wepHelp);
		loadEnemy->Load(index);

		/*auto loadEnemy = en->GetCompatibleComponent<ColonelEnemyComponent>();
		loadEnemy[0]->Load(index);*/
	}
}
