#include "scene_main_menu.h"
#include "../game.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include "../components/cmp_sprite.h"
#include "../components/cmp_sound.h"
#include "../player/cmp_player.h"
#include "../player/creates_player.h"
#include "../services/load_save_game.h"
#include "../background/create_background.h"

using namespace std;
using namespace sf;

std::shared_ptr<SpriteComponent> shipSpriteRight;
std::shared_ptr<SpriteComponent> shipSpriteLeft;
std::shared_ptr<Entity> mainMenuView;

//Loads the main menu, allowing the player to playe a new game, load a game, go to settings, 
//or exit the game
void MainMenu::Load() {
	mainMenuView = makeEntity();
	mainMenuView->setView(menuView);

	//Adds to sprites, rotating them to face the text on the menus
	for (int i = 0; i < 2; i++) {
		auto temp = mainMenuView->addComponent<SpriteComponent>();
		_titleShipTex = make_shared<sf::Texture>();
		auto rec = sf::IntRect();
		_titleShipTex->loadFromFile("res/img/player/player_900.png");

		temp->setTexure(_titleShipTex);
		rec.left = (round)(_titleShipTex->getSize().x / 5 * 2);
		rec.top = (round)(_titleShipTex->getSize().y / 2 * 0);
		rec.width = (round)(_titleShipTex->getSize().x / 5);
		rec.height = (round)(_titleShipTex->getSize().y / 2);
		temp->getSprite().setTextureRect(rec);
		temp->getSprite().setOrigin(rec.width / 2, rec.height / 2);
		if (i == 0) {
			shipSpriteRight = temp;
			_titleShipRightRect = rec;
			shipSpriteRight->getSprite().setRotation(-90.f);
		}
		if (i == 1) {
			shipSpriteLeft = temp;
			_titleShipLeftRect = rec;
			shipSpriteLeft->getSprite().setRotation(90.f);
		}
	}

	//Creating textcomponents and initializing menu index
	selectedIndex = 0;
	menuOption1 = mainMenuView->addComponent<TextComponent>();
	menuOption2 = mainMenuView->addComponent<TextComponent>();
	menuOption3 = mainMenuView->addComponent<TextComponent>();
	menuOption4 = mainMenuView->addComponent<TextComponent>();
	menuOption4 = mainMenuView->addComponent<TextComponent>();
	menuOption = mainMenuView->GetCompatibleComponent<TextComponent>();
	loadGameTxt = mainMenuView->addComponent<TextComponent>();

	//Setting up format and values for loadGame text component
	loadGameTxt->setFontSize(180u);
	loadGameTxt->_text.setColor(Color::White);
	loadGameTxt->_text.setOutlineColor(Color::Red);
	loadGameTxt->_text.setOutlineThickness(2);
	loadGameTxt->_text.setString("LOADING GAME");
	loadGameTxt->setOrigin(Vector2f((round)(loadGameTxt->getLocalBounds().left + loadGameTxt->getLocalBounds().width / 2), (round)(loadGameTxt->getLocalBounds().top + loadGameTxt->_text.getLocalBounds().height / 2)));
	loadGameTxt->setPosition(Vector2f((round)(menuView.getSize().x / 2), (round)(menuView.getSize().y / 2)));
	loadGameTxt->setVisible(false);

	//Assigning and initializing the default text for the menus
	switchSceneText(MAIN_MENU);
	//Updates the position of the text to align it properly
	changeMenuText(s);

	//Set initial values
	isMainMenuScreen = true;
	isSettingsScreen = false;
	isResolutionScreen = false;
	timer = 0;

	setLoaded(true);
}

//Sets the text on the pause menu with the giving strings
void MainMenu::changeMenuText(std::vector<std::string> s) {
	for (int i = 0; i < s.size(); i++) {

		menuOption[i]->setFontSize(60u);
		menuOption[i]->_text.setString(s[i]);
		menuOption[i]->_text.setColor(Color::White);
		if (i == selectedIndex) { menuOption[i]->_text.setColor(Color::Red); }

		sf::FloatRect textRect = menuOption[i]->getLocalBounds();
		menuOption[i]->setOrigin(Vector2f((round)(textRect.left + textRect.width / 2.f), (round)(textRect.top + textRect.height / 2.f)));
		menuOption[i]->setPosition(Vector2f(menuView.getCenter().x, (round)(menuView.getSize().y / 3) + (menuView.getSize().y / 10 * i)));
	}

	alignSprite();
}
//Aligns the sprites depending on the selectied menu option
void MainMenu::alignSprite() {
	shipSpriteLeft->getSprite().setPosition((round)(menuOption[selectedIndex]->getGlobalBounds().left - 50.f), (round)(menuOption[selectedIndex]->getGlobalBounds().top + menuOption[selectedIndex]->getGlobalBounds().getSize().y / 2));
	shipSpriteRight->getSprite().setPosition((round)(menuOption[selectedIndex]->getGlobalBounds().left + menuOption[selectedIndex]->getGlobalBounds().width + 50.f), (round)(menuOption[selectedIndex]->getGlobalBounds().top + menuOption[selectedIndex]->getGlobalBounds().getSize().y / 2));
}

//Depending on the scene, switches the text to display the current menu
void MainMenu::switchSceneText(_menuType scene) {

	menuOption[3]->setVisible(false);
	menuOption[3]->setAlive(false);
	selectedIndex = 0;
	//Sets the options text depending on the type of menu
	switch (scene) {
	case MAIN_MENU: {
		menuOption[3]->setVisible(true);
		menuOption[3]->setAlive(true);	
		menuOption[2]->setVisible(true);
		menuOption[2]->setAlive(true);
		s.clear();
		s.push_back("Start Game");
		s.push_back("Load Game");
		s.push_back("Settings");
		s.push_back("Exit");
		if (selectedIndex >= s.size()) { selectedIndex--; }
		changeMenuText(s);
		//Changes the bools to indicate the current menu
		changeBools(true, false, false, false);
		break;
	}
	case LEVEL_MENU: {
		s.clear();
		s.push_back("Solo");
		s.push_back("Infite run");
		s.push_back("Back");
		if (selectedIndex >= s.size()) { selectedIndex--; }
		changeMenuText(s);
		changeBools(false, true, false, false);
		break;
	}
	case SETTINGS_MENU: {
		menuOption[2]->setVisible(false);
		menuOption[2]->setAlive(false);
		s.clear();
		s.push_back("Resolution");
		s.push_back("Back");
		if (selectedIndex >= s.size()) { selectedIndex--; }
		changeMenuText(s);
		changeBools(false, false, true, false);
		break;
	}
	case RESOLUTION_MENU: {
		menuOption[2]->setVisible(true);
		menuOption[2]->setAlive(true);
		menuOption[3]->setVisible(true);
		menuOption[3]->setAlive(true);
		s.clear();
		s.push_back("1024 x 576");
		s.push_back("1280 x 720");
		s.push_back("1920 x 1080");
		s.push_back("Back");
		changeMenuText(s);
		changeBools(false, false, false, true);
		break;
	}
	default:
		break;
	}
}
//Allows the user to change the resolution, and applies a window scale for sprites and text components
void MainMenu::changeResolution(int type) {
	if (type == 1) { Engine::GetWindow().setSize(Vector2u(1024, 576)); windowScale = { 0.8f , 0.8f }; }
	if (type == 2) { Engine::GetWindow().setSize(Vector2u(1280, 720)); windowScale = { 1.0f, 1.0f }; }
	if (type == 3) { Engine::GetWindow().setSize(Vector2u(1920, 1080)); windowScale = { 1.5f, 1.5f }; }
	auto desktop = sf::VideoMode::getDesktopMode();

	Engine::GetWindow().setPosition(Vector2i(desktop.width / 2 - Engine::GetWindow().getSize().x / 2, desktop.height / 2 - Engine::GetWindow().getSize().y / 2));
	MainMenu::UnLoad();
	Engine::ChangeScene(&title);
}

//Changes bools values
void MainMenu::changeBools(bool _isMainMenuScreen, bool _isLevelMenuScreen, bool _isSettingsScreen, bool _isResolutionScreen) {
	isMainMenuScreen = _isMainMenuScreen;
	isLevelMenuScreen = _isLevelMenuScreen;
	isSettingsScreen = _isSettingsScreen;
	isResolutionScreen = _isResolutionScreen;
}

//Moves up the selection on the menu
void MainMenu::moveUp() {
	if (selectedIndex - 1 >= 0) {
		menuOption[selectedIndex]->_text.setColor(Color::White);
		selectedIndex--;
		menuOption[selectedIndex]->_text.setColor(Color::Red);
	}

	alignSprite();
}
//Moves down the selection on the menu
void MainMenu::moveDown() {
	int index = s.size();

	if (selectedIndex + 1 < index) {
		menuOption[selectedIndex]->_text.setColor(Color::White);
		selectedIndex++;
		menuOption[selectedIndex]->_text.setColor(Color::Red);
	}
	alignSprite();
}
//Loads the game from the file, unloading the last scene
void MainMenu::loadGame() {
	Engine::isGamePaused = false;
	Engine::isMenu = false;
	Engine::isPausedMenu = false;
	Engine::_lastScene->UnLoad();
	Engine::isLoading = true;
	musicArray[MUSIC_TITLE_SCREEN].pause();
	LoadSaveGame::loadGame();
	//In order to load a game, background and player has to be created before
	Background::createBackground(dynamic_cast<Scene*>(&levelScene));
	Player::createPlayerFromSettings(dynamic_cast<Scene*>(&levelScene));
	Engine::ChangeScene(&levelScene);
}
void MainMenu::Update(const double& dt) {
	//Checks if the game is not loading, and detects the different key strokes
	if (!isGameLoading) {
		if (sf::Keyboard::isKeyPressed(Keyboard::Up) && !detectingKeys.keyUp) { moveUp(); }
		if (sf::Keyboard::isKeyPressed(Keyboard::Down) && !detectingKeys.keyDown) { moveDown(); }
		if (sf::Keyboard::isKeyPressed(Keyboard::Enter) && !detectingKeys.keyEnter) {
			switch (selectedIndex) {
			case 0:
				//Switches menu options
				if (isMainMenuScreen) { switchSceneText(LEVEL_MENU); break; };
				//Sets all the bools to false and starts a new game
				if (isLevelMenuScreen) {
					Engine::isGamePaused = false;
					Engine::isPausedMenu = false;
					Engine::isMenu = false;
					Engine::currentPlayerLevel = 0;
					musicArray[MUSIC_TITLE_SCREEN].pause();					
					Engine::ChangeScene(&levelScene);
					break;
				};
				//Updates the menu options
				if (isSettingsScreen) { switchSceneText(RESOLUTION_MENU); break; }
				//Sets to the selected resolution
				if (isResolutionScreen) { changeResolution(1); break; }
				break;
			case 1:
				if (isSettingsScreen) { switchSceneText(MAIN_MENU); break; }
				//Starts a game in infinite mode
				if (isLevelMenuScreen) { 
					Engine::isGamePaused = false;
					Engine::isPausedMenu = false;
					Engine::isMenu = false;
					musicArray[MUSIC_TITLE_SCREEN].pause();
					Engine::currentPlayerLevel = -1;
					Engine::isInfiniteLevel = true;
					Engine::ChangeScene(&levelScene);
					break;
				}
				//Loads a game from file
				if (isMainMenuScreen) {
					isGameLoading = true;
					loadingTimer = 0;
					loadGameTxt->setVisible(true);
					break;
				}
				//Sets to the selected resolution
				if (isResolutionScreen) { changeResolution(2); break; }
				break;
			case 2:
				//Updates the menu options
				if (isMainMenuScreen) { switchSceneText(SETTINGS_MENU); break; }
				//Updates the menu options
				if (isLevelMenuScreen) { switchSceneText(MAIN_MENU); break; }
				//Sets to the selected resolution
				if (isResolutionScreen) { changeResolution(3); break; }
				break;
			case 3:
				//Closes the game
				if (isMainMenuScreen) { Engine::GetWindow().close(); break; }
				//Updates the menu options
				if (isResolutionScreen) { switchSceneText(SETTINGS_MENU);  break; }
				break;
			default:
				break;
			}
		}
	}
	//While loading the game, displays a text.
	//Once the timer is bigger than 2, loads the game
	if (isGameLoading) {
		loadingTimer += dt;
		if (loadingTimer > 2) {
			isGameLoading = false;
			loadingTimer = 0;
			loadGameTxt->setVisible(false);
			moveUp();
			moveUp();
			loadGame();
		}
	}

	//Allows to go back on the menus by pressing escape
	if (sf::Keyboard::isKeyPressed(Keyboard::Escape) && !detectingKeys.keyEscape) {
		if (isSettingsScreen) { switchSceneText(MAIN_MENU); }
		else if (isResolutionScreen) { switchSceneText(SETTINGS_MENU); }
		else if (isLevelMenuScreen) { switchSceneText(MAIN_MENU); }
	}

	timer += dt;

	if (Engine::isMenu && timer > 0.15) {
		//Check if the loaded sprite is the bottom, if so, load the top. And viceversa
		if (_titleShipLeftRect.top == _titleShipLeftRect.getSize().y / 1) { _titleShipLeftRect.top = 0; }
		else { _titleShipLeftRect.top = _titleShipLeftRect.getSize().y / 1; }
		shipSpriteLeft->getSprite().setTextureRect(_titleShipLeftRect);

		if (_titleShipRightRect.top == _titleShipRightRect.getSize().y / 1) { _titleShipRightRect.top = 0; }
		else { _titleShipRightRect.top = _titleShipRightRect.getSize().y / 1; }
		shipSpriteRight->getSprite().setTextureRect(_titleShipRightRect);
		timer = 0;
	}

	detectingKeys.detectingKeys();
}

//Unloads the main menu
void MainMenu::UnLoad() {
	switchSceneText(MAIN_MENU);
	mainMenuView->setForDelete();
	isMainMenuScreen = true;
	isSettingsScreen = false;
	isResolutionScreen = false;

	Scene::setLoaded(false);
}
