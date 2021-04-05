#include "engine.h"
#include "game.h"
#include "scenes/scene_menu.h"
#include <LevelSystem.h>

using namespace std;

MenuScene menu;
Level1Scene level1;
Level2Scene level2;

int main() {
	Engine::Start(1280, 720, "Perfect Jazz", &menu);
}