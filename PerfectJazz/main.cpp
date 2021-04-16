#include "engine.h"
#include "game.h"
#include "scenes/scene_menu.h"
#include <LevelSystem.h>

using namespace std;

MenuScene menu;
Level1Scene level1;
Level2Scene level2;
Level3Scene level3;
unsigned int gameWidth = 1280;
unsigned int gameHeight = 720;

int main() {
	Engine::Start(gameWidth, gameHeight, "Perfect Jazz", &menu);
}