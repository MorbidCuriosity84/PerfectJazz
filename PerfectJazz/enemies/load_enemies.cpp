#include "load_enemies.h"
#include "../game.h"
#include <LevelSystem.h>
#include "cmp_enemy_airman.h"
#include "cmp_enemy_sergeant.h"
#include "cmp_enemy_colonel.h"

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
		en->addComponent<AirManEnemyComponent>(_scene);
		auto loadEnemy = en->GetCompatibleComponent<AirManEnemyComponent>();
		loadEnemy[0]->Load(index);
	}

	for (int index = 0; index < ls::findTiles(ls::SERGEANT).size(); index++) {
		auto en = _scene->makeEntity();
		en->setView(mainView);
		en->addComponent<SergeantEnemyComponent>(_scene);
		auto loadEnemy = en->GetCompatibleComponent<SergeantEnemyComponent>();
		loadEnemy[0]->Load(index);
	}

	for (int index = 0; index < ls::findTiles(ls::COLONEL).size(); index++) {
		auto en = _scene->makeEntity();
		en->setView(mainView);
		en->addComponent<ColonelEnemyComponent>(_scene);
		auto loadEnemy = en->GetCompatibleComponent<ColonelEnemyComponent>();
		loadEnemy[0]->Load(index);
	}
}
