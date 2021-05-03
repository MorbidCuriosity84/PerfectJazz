#include "scene_pause_menu.h"
#include "../game.h"
#include "../components/cmp_sprite.h"
#include "../components/cmp_sound.h"
#include "../pools/entityPool.h"
#include "../services/detecting_keys.h"
#include "../services/load_save_game.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include <system_physics.h>

using namespace std;
using namespace sf;

std::shared_ptr<SpriteComponent> shipSpriteRight1;
std::shared_ptr<SpriteComponent> shipSpriteLeft1;
std::shared_ptr<Entity> pauseView;

//Loads the pause menu allowing the player to go back to the main menu,
//save the game, or exit the game
void PauseMenu::Load() {
	pauseView = makeEntity();
	pauseView->setView(menuView);

	//Adds to sprites, rotating them to face the text on the menus
	for (int i = 0; i < 2; i++) {
		auto temp = pauseView->addComponent<SpriteComponent>();
		_titleShipTex = make_shared<sf::Texture>();
		auto rec = sf::IntRect();
		_titleShipTex->loadFromFile("res/img/enemies/enemy1_900.png");
		temp->setTexure(_titleShipTex);
		rec.left = (round)(_titleShipTex->getSize().x / 2 * 0);
		rec.top = (round)(_titleShipTex->getSize().y / 2 * 0);
		rec.width = (round)(_titleShipTex->getSize().x / 2);
		rec.height = (round)(_titleShipTex->getSize().y / 1);
		temp->getSprite().setTextureRect(rec);
		temp->getSprite().setOrigin(rec.width / 2, rec.height / 2);
		if (i == 0) {
			shipSpriteRight1 = temp;
			_titleShipRightRect = rec;
			shipSpriteRight1->getSprite().setRotation(-270.f);
			shipSpriteRight1->getSprite().setScale(Vector2f(1.2f, 1.2f));
		}
		if (i == 1) {
			shipSpriteLeft1 = temp;
			_titleShipLeftRect = rec;
			shipSpriteLeft1->getSprite().setRotation(270.f);
			shipSpriteLeft1->getSprite().setScale(Vector2f(1.2f, 1.2f));
		}
	}

	//Setting up textcomponents
	menuOption1 = pauseView->addComponent<TextComponent>();
	menuOption2 = pauseView->addComponent<TextComponent>();
	menuOption3 = pauseView->addComponent<TextComponent>();
	menuOption4 = pauseView->addComponent<TextComponent>();
	menuOption = pauseView->GetCompatibleComponent<TextComponent>();
	savingGameTxt = pauseView->addComponent<TextComponent>();
	cantSaveTxt = pauseView->addComponent<TextComponent>();

	//Setting up format and values for savingGame text component
	savingGameTxt->setFontSize(180u);
	savingGameTxt->_text.setColor(Color::White);
	savingGameTxt->_text.setOutlineColor(Color::Red);
	savingGameTxt->_text.setOutlineThickness(2);
	savingGameTxt->_text.setString("GAME SAVED");
	savingGameTxt->setOrigin(Vector2f((round)(savingGameTxt->getLocalBounds().left + savingGameTxt->getLocalBounds().width / 2), (round)(savingGameTxt->getLocalBounds().top + savingGameTxt->_text.getLocalBounds().height / 2)));
	savingGameTxt->setPosition(Vector2f((round)(menuView.getSize().x / 2), (round)(menuView.getSize().y / 2)));
	savingGameTxt->setVisible(false);

	//Setting up format and values for cantSaveTxt text component
	cantSaveTxt->setFontSize(110u);
	cantSaveTxt->_text.setColor(Color::White);
	cantSaveTxt->_text.setOutlineColor(Color::Red);
	cantSaveTxt->_text.setOutlineThickness(2);
	cantSaveTxt->_text.setString("CANNOT SAVE IN INFINITE MODE");
	cantSaveTxt->setOrigin(Vector2f((round)(cantSaveTxt->getLocalBounds().left + cantSaveTxt->getLocalBounds().width / 2), (round)(cantSaveTxt->getLocalBounds().top + cantSaveTxt->_text.getLocalBounds().height / 2)));
	cantSaveTxt->setPosition(Vector2f((round)(menuView.getSize().x / 2), (round)(menuView.getSize().y / 2)));
	cantSaveTxt->setVisible(false);

	//Clearning vector of strings and initializing it to default menu	
	s.clear();
	s.push_back("Continue");
	s.push_back("Save Game");
	s.push_back("Go to Main Menu");
	s.push_back("Exit Game");
	changeMenuText(s);

	//Setting up variables
	selectedIndex = 0;
	timer = 0;
	savingTimer = 0;
	notSavingTimer = 0;
	savingGame = false;
	notSavingTimer = false;
	setLoaded(true);
}

//Sets the text on the pause menu with the giving strings
void PauseMenu::changeMenuText(std::vector<std::string> s) {
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
void PauseMenu::alignSprite() {
	shipSpriteLeft1->getSprite().setPosition((round)(menuOption[selectedIndex]->getGlobalBounds().left - 50.f), (round)(menuOption[selectedIndex]->getGlobalBounds().top + menuOption[selectedIndex]->getGlobalBounds().getSize().y / 2));
	shipSpriteRight1->getSprite().setPosition((round)(menuOption[selectedIndex]->getGlobalBounds().left + menuOption[selectedIndex]->getGlobalBounds().width + 50.f), (round)(menuOption[selectedIndex]->getGlobalBounds().top + menuOption[selectedIndex]->getGlobalBounds().getSize().y / 2));
}
//Moves up the selection on the menu
void PauseMenu::moveUp() {
	if (selectedIndex - 1 >= 0) {
		menuOption[selectedIndex]->_text.setColor(Color::White);
		selectedIndex--;
		menuOption[selectedIndex]->_text.setColor(Color::Red);
	}

	alignSprite();
}
//Moves down the selection on the menu
void PauseMenu::moveDown() {
	int index = s.size();

	if (selectedIndex + 1 < index) {
		menuOption[selectedIndex]->_text.setColor(Color::White);
		selectedIndex++;
		menuOption[selectedIndex]->_text.setColor(Color::Red);
	}
	alignSprite();
}

void PauseMenu::Update(const double& dt) {
	//Checks if the game is not saving, and detects the different key strokes
	if (!savingGame && !notSavingGame) {
		if (sf::Keyboard::isKeyPressed(Keyboard::Up) && !detectingKeys.keyUp) { moveUp(); }
		if (sf::Keyboard::isKeyPressed(Keyboard::Down) && !detectingKeys.keyDown) { moveDown(); }
		if (sf::Keyboard::isKeyPressed(Keyboard::Enter) && !detectingKeys.keyEnter) {
			switch (selectedIndex) {
			case 0:
				//Sets all the bools to false and comes back to the game
				Engine::isGamePaused = false;
				Engine::isMenu = false;
				Engine::isPausedMenu = false;
				musicArray[currentLvlMusicIndex].play();
				Engine::ChangeScene(Engine::_lastScene);
				break;
			case 1:
				//Saves the game only if the player playing normal mode (>=0)
				if (Engine::currentPlayerLevel >= 0) {
					savingGame = true;
					savingTimer = 0;
					LoadSaveGame::saveGame();
				}
				//Shows text saying it's not able to save the game
				else {
					notSavingGame = true;
					notSavingTimer = 0;
				}
				break;
			case 2:
				Engine::isPausedMenu = true;
				Engine::isMenu = true;
				Engine::isGamePaused = true;
				Engine::isLoading = false;
				//Unloads the upgrade menu and goes back to the main menu
				if (upgradeMenu.ents.list.size() != 0) {
					upgradeMenu.UnLoad();
				}
				Engine::_lastScene->UnLoad();
				musicArray[MUSIC_TITLE_SCREEN].play();
				Engine::currentPlayerLevel = 0;
				Engine::ChangeScene(&mainMenuScene);
				break;
			case 3:
				//Exits the game
				Engine::isPausedMenu = false;
				Engine::isMenu = false;
				Engine::isGamePaused = false;
				if (upgradeMenu.ents.list.size() != 0) {
					upgradeMenu.UnLoad();
				}
				Engine::_lastScene->UnLoad();
				Engine::GetWindow().close();
				break;
			default:
				break;
			}
		}
		detectingKeys.detectingKeys();
	}

	timer += dt;
	if (timer > 0.12) {
		//Check if the loaded sprite is the bottom one, if so, load the top. And viceversa
		if (Engine::isMenu && Engine::isPausedMenu) {
			if (_titleShipLeftRect.left == _titleShipLeftRect.getSize().y / 1) { _titleShipLeftRect.left = 0; }
			else { _titleShipLeftRect.left = _titleShipLeftRect.getSize().y / 1; }
			shipSpriteLeft1->getSprite().setTextureRect(_titleShipLeftRect);

			if (_titleShipRightRect.left == _titleShipRightRect.getSize().y / 1) { _titleShipRightRect.left = 0; }
			else { _titleShipRightRect.left = _titleShipRightRect.getSize().y / 1; }
			shipSpriteRight1->getSprite().setTextureRect(_titleShipRightRect);
		}

		timer = 0;
		//While saving the game, displays a text
		if (savingGame) {
			savingGameTxt->setVisible(true);
			savingTimer += dt;
			if (savingTimer > 0.2) {
				savingGame = false;
				savingGameTxt->setVisible(false);
			}
		}		
		//If not able to save the game, displays a text
		if (notSavingGame) {
			cantSaveTxt->setVisible(true);
			notSavingTimer += dt;
			if (notSavingTimer > 0.2) {
				notSavingGame = false;
				cantSaveTxt->setVisible(false);
			}
		}
	}
}
//Unloads the pause scene
void PauseMenu::UnLoad() {
	shipSpriteRight1.reset();
	shipSpriteLeft1.reset();
	pauseView->setForDelete();

	setLoaded(false);
}
