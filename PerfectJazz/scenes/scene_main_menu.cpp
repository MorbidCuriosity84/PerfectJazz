#include "scene_main_menu.h"
#include "../game.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include "../components/cmp_sprite.h"
#include "../components/cmp_sound.h"

using namespace std;
using namespace sf;

std::shared_ptr<SpriteComponent> shipSpriteRight;
std::shared_ptr<SpriteComponent> shipSpriteLeft;

void MainMenu::Load() {
	cout << "Title load \n";
	sf::View tempMain(sf::FloatRect(0, 0, Engine::getWindowSize().x, Engine::getWindowSize().y));
	menuView = tempMain;
	menuView.setViewport(sf::FloatRect(0, 0, 1.f, 1.f));
	auto titleView = makeEntity();
	titleView->setView(menuView);

	for (int i = 0; i < 2; i++) {
		auto temp = titleView->addComponent<SpriteComponent>();
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

	selectedIndex = 0;
	timer = 0;

	menuOption1 = titleView->addComponent<TextComponent>();
	menuOption2 = titleView->addComponent<TextComponent>();
	menuOption3 = titleView->addComponent<TextComponent>();
	menuOption4 = titleView->addComponent<TextComponent>();
	menuOption = titleView->GetCompatibleComponent<TextComponent>();

	switchSceneText(MAIN_MENU);
	changeMenuText(s);

	isMainMenuScreen = true;
	isSettingsScreen = false;
	isResolutionScreen = false;

	setLoaded(true);
}

void MainMenu::changeMenuText(std::vector<std::string> s) {
	for (int i = 0; i < s.size(); i++) {

		menuOption[i]->setFontSize(60u / windowScale.x);
		menuOption[i]->_text.setString(s[i]);
		menuOption[i]->_text.setColor(Color::White);
		if (i == selectedIndex) { menuOption[i]->_text.setColor(Color::Red); }

		sf::FloatRect textRect = menuOption[i]->getLocalBounds();
		menuOption[i]->setOrigin(Vector2f((round)(textRect.left + textRect.width / 2.f), (round)(textRect.top + textRect.height / 2.f)));
		menuOption[i]->setPosition(Vector2f(menuView.getCenter().x, (round)(menuView.getSize().y / 3) + (menuView.getSize().y / 10 * i)));
	}

	alignSprite();
}

void MainMenu::alignSprite() {
	shipSpriteLeft->getSprite().setPosition((round)(menuOption[selectedIndex]->getGlobalBounds().left - 50.f), (round)(menuOption[selectedIndex]->getGlobalBounds().top + menuOption[selectedIndex]->getGlobalBounds().getSize().y / 2));
	shipSpriteRight->getSprite().setPosition((round)(menuOption[selectedIndex]->getGlobalBounds().left + menuOption[selectedIndex]->getGlobalBounds().width + 50.f), (round)(menuOption[selectedIndex]->getGlobalBounds().top + menuOption[selectedIndex]->getGlobalBounds().getSize().y / 2));
}


void MainMenu::switchSceneText(_menuType scene) {

	menuOption[3]->setVisible(false);
	menuOption[3]->setAlive(false);

	switch (scene) {
	case MAIN_MENU: {
		s.clear();
		s.push_back("Start Game");
		s.push_back("Settings");
		s.push_back("Exit");
		if (selectedIndex >= s.size()) { selectedIndex--; }
		changeMenuText(s);
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
		s.clear();
		s.push_back("Resolution");
		s.push_back("Something else");
		s.push_back("Back");
		if (selectedIndex >= s.size()) { selectedIndex--; }
		changeMenuText(s);
		changeBools(false, false, true, false);
		break;
	}
	case RESOLUTION_MENU: {
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

void MainMenu::changeResolution(int type) {
	if (type == 1) { Engine::GetWindow().setSize(Vector2u(1024, 576)); windowScale = { 0.8f , 0.8f }; }
	if (type == 2) { Engine::GetWindow().setSize(Vector2u(1280, 720)); windowScale = { 1.0f, 1.0f }; }
	if (type == 3) { Engine::GetWindow().setSize(Vector2u(1920, 1080)); windowScale = { 1.5f, 1.5f }; }
	auto desktop = sf::VideoMode::getDesktopMode();

	Engine::GetWindow().setPosition(Vector2i(desktop.width / 2 - Engine::GetWindow().getSize().x / 2, desktop.height / 2 - Engine::GetWindow().getSize().y / 2));
}


void MainMenu::changeBools(bool _isMainMenuScreen, bool _isLevelMenuScreen, bool _isSettingsScreen, bool _isResolutionScreen) {
	isMainMenuScreen = _isMainMenuScreen;
	isLevelMenuScreen = _isLevelMenuScreen;
	isSettingsScreen = _isSettingsScreen;
	isResolutionScreen = _isResolutionScreen;
}

void MainMenu::moveUp() {
	if (selectedIndex - 1 >= 0) {
		menuOption[selectedIndex]->_text.setColor(Color::White);
		selectedIndex--;
		menuOption[selectedIndex]->_text.setColor(Color::Red);
	}

	alignSprite();
}

void MainMenu::moveDown() {
	int index = s.size();

	if (selectedIndex + 1 < index) {
		menuOption[selectedIndex]->_text.setColor(Color::White);
		selectedIndex++;
		menuOption[selectedIndex]->_text.setColor(Color::Red);
	}
	alignSprite();
}


void MainMenu::Update(const double& dt) {
	timer += dt;

	if (timer > 0.12) {
		if (sf::Keyboard::isKeyPressed(Keyboard::Up)) { moveUp(); }
		if (sf::Keyboard::isKeyPressed(Keyboard::Down)) { moveDown(); }
		if (sf::Keyboard::isKeyPressed(Keyboard::Enter)) {
			switch (selectedIndex) {
			case 0:
				if (isMainMenuScreen) { switchSceneText(LEVEL_MENU); break; };
				if (isLevelMenuScreen) { 
					Engine::isGamePaused = false; 
					Engine::isMenu = false; 
					Engine::ChangeScene(&level3);  
					break; };
				if (isSettingsScreen) { switchSceneText(RESOLUTION_MENU); break; }
				if (isResolutionScreen) { changeResolution(1); break; }
				break;
			case 1:
				if (isMainMenuScreen) { switchSceneText(SETTINGS_MENU); break; }
				if (isLevelMenuScreen) { cout << "Infinite" << endl; break; }
				if (isResolutionScreen) { changeResolution(2); break; }
				break;
			case 2:
				if (isMainMenuScreen) { Engine::GetWindow().close(); break; }
				if (isLevelMenuScreen) { switchSceneText(MAIN_MENU); break; }
				if (isSettingsScreen) { switchSceneText(MAIN_MENU); break; }
				if (isResolutionScreen) { changeResolution(3); break; }
				break;
			case 3:
				if (isResolutionScreen) { switchSceneText(SETTINGS_MENU);  break; }
				break;
			default:
				break;
			}
		}
		if (sf::Keyboard::isKeyPressed(Keyboard::Escape)) {
			if (isSettingsScreen) { switchSceneText(MAIN_MENU); }
			else if (isResolutionScreen) { switchSceneText(SETTINGS_MENU); }
		}


		if (Engine::isMenu) {
			//Check if the loaded sprite is the bottom, if so, load the top. And viceversa
			if (_titleShipLeftRect.top == _titleShipLeftRect.getSize().y / 1) { _titleShipLeftRect.top = 0; }
			else { _titleShipLeftRect.top = _titleShipLeftRect.getSize().y / 1; }
			shipSpriteLeft->getSprite().setTextureRect(_titleShipLeftRect);

			if (_titleShipRightRect.top == _titleShipRightRect.getSize().y / 1) { _titleShipRightRect.top = 0; }
			else { _titleShipRightRect.top = _titleShipRightRect.getSize().y / 1; }
			shipSpriteRight->getSprite().setTextureRect(_titleShipRightRect);
		}
		timer = 0;
	}
}

void MainMenu::UnLoad() {
	if (Engine::isMenu && Engine::_lastScreen != nullptr) {
		Engine::_lastScreen->UnLoad();
	}

	switchSceneText(MAIN_MENU);

	isMainMenuScreen = true;
	isSettingsScreen = false;
	isResolutionScreen = false;
}
