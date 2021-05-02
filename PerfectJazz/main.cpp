#include "engine.h"
#include "game.h"
#include "scenes/scene_menu.h"
#include <LevelSystem.h>

using namespace std;

MenuScene menuScene;
MainMenu mainMenuScene;
PauseMenu pauseMenu;
UpgradeMenu upgradeMenu;
shared_ptr<Entity> player;
int currentLvlMusicIndex;
TitleScene title;
Level1Scene level1;
Level2Scene level2;
Level3Scene level3;
sf::View leftView;
sf::View rightView;
sf::View mainView;
sf::View menuView;
Vector2f windowScale = { 1.0f, 1.0f };
unsigned int gameHeight = (round)(720);
unsigned int gameWidth = (round)(1280);

// The grid size will be 15x16 tiles
int main() {
	Engine::Start(gameWidth, gameHeight, "Perfect Jazz", &title);
}