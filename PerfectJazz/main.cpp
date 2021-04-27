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
//Vector2f windowScale = { 1.2f, 1.2f };
Vector2f windowScale = { 1.f, 1.f };
//Vector2f windowScale = { 0.8f, 0.8f };
unsigned int gameWidth = (round)(1280 * windowScale.x);
unsigned int gameHeight = (round)(720 * windowScale.y);

// The grid size will be 15x16 tiles
int main() {
	Engine::Start(gameWidth, gameHeight, "Perfect Jazz", &title);
}