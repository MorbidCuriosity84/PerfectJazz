#include "load_enemies.h"
#include "../game.h"
#include <LevelSystem.h>
#include "cmp_enemy_airman.h"

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
		en->addComponent<AirManEnemyComponent>();
		auto loadEnemy = en->GetCompatibleComponent<AirManEnemyComponent>();
		loadEnemy[0]->Load(index);
	}
}
