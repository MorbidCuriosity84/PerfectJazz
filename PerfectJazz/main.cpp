#include "engine.h"
#include "scenes/scene_level.h"
#include "game.h"
#include <LevelSystem.h>

using namespace std;

MainMenu mainMenuScene;
PauseMenu pauseMenu;
UpgradeMenu upgradeMenu;
LevelScene levelScene;
TitleScene title;
shared_ptr<Entity> player;
int currentLvlMusicIndex;
sf::View leftView;
sf::View rightView;
sf::View mainView;
sf::View menuView;
Vector2f windowScale = { 1.0f, 1.0f };
unsigned int gameHeight = (round)(720);
unsigned int gameWidth = (round)(1280);

//Starts the engine of the game, with the with, height, title and scene for the windows creation.
int main() {
	Engine::Start(gameWidth, gameHeight, "Perfect Jazz", &mainMenuScene);
}