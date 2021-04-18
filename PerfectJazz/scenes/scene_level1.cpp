#include "scene_level1.h"
#include "../components/cmp_player_physics.h"
#include "../components/cmp_background_physics.h"
#include "../components/cmp_sprite.h"
#include "../game.h"
#include <LevelSystem.h>
#include <iostream>
#include <thread>

using namespace std;
using namespace sf;

void Level1Scene::Load() {

}

void Level1Scene::UnLoad() {
}

void Level1Scene::Update(const double& dt) {
	Scene::Update(dt);
}

void Level1Scene::Render() {
	ls::render(Engine::GetWindow());
	Scene::Render();
}