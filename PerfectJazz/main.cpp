#include "engine.h"
#include "game.h"
#include "scenes/scene_menu.h"
#include <LevelSystem.h>
#include "settings/player_settings.h"

using namespace std;

MenuScene menuScene;
MainMenu mainMenuScene;
TitleScene title;
Level1Scene level1;
Level2Scene level2;
Level3Scene level3;
unsigned int gameWidth = 1280;
unsigned int gameHeight = 720;

// The grid size will be 15x16 tiles
int main() {
	Engine::Start(gameWidth, gameHeight, "Perfect Jazz", &mainMenuScene);
}