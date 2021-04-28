#include "engine.h"
#include "game.h"
#include "scenes/scene_menu.h"
#include <LevelSystem.h>
#include "settings/player_settings.h"

using namespace std;

MenuScene menuScene;
MainMenu mainMenuScene;
PauseMenu pauseMenu;
TitleScene title;
Level1Scene level1;
Level2Scene level2;
Level3Scene level3;
Vector2f windowScale = { 1.0f, 1.0f };
unsigned int gameHeight = (round)(720);
unsigned int gameWidth = (round)(1280 );


// The grid size will be 15x16 tiles
int main() {
	Engine::Start(gameWidth, gameHeight, "Perfect Jazz", &title);
}