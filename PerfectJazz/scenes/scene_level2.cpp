#include "scene_level2.h"
#include "../components/cmp_player_physics.h"
#include "../components/cmp_background_physics.h"
#include "../components/cmp_sprite.h"
#include "../game.h"
#include <LevelSystem.h>
#include <iostream>
#include <thread>

using namespace std;
using namespace sf;

void Level2Scene::Load() {
}

void Level2Scene::UnLoad() {
}


void Level2Scene::Update(const double& dt) {
	Scene::Update(dt);
}

void Level2Scene::Render() {
	ls::render(Engine::GetWindow());
	Scene::Render();
}