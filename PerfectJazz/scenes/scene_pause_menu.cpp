#include "scene_pause_menu.h"
#include "../game.h"
#include "../components/cmp_sprite.h"
#include "../components/cmp_sound.h"
#include "../pools/entityPool.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include <system_physics.h>
#include "../services/detecting_keys.h"


using namespace std;
using namespace sf;

std::shared_ptr<SpriteComponent> shipSpriteRight1;
std::shared_ptr<SpriteComponent> shipSpriteLeft1;
std::shared_ptr<Entity> pauseView;

void PauseMenu::Load() {
	cout << "Title load \n";
	sf::View tempMain(sf::FloatRect(0, 0, Engine::getWindowSize().x, Engine::getWindowSize().y));
	menuView = tempMain;
	menuView.setViewport(sf::FloatRect(0, 0, 1.f, 1.f));
	pauseView = makeEntity();
	pauseView->setView(menuView);

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

	selectedIndex = 0;
	timer = 0;

	menuOption1 = pauseView->addComponent<TextComponent>();
	menuOption2 = pauseView->addComponent<TextComponent>();
	menuOption3 = pauseView->addComponent<TextComponent>();
	menuOption4 = pauseView->addComponent<TextComponent>();
	menuOption = pauseView->GetCompatibleComponent<TextComponent>();

	s.clear();
	s.push_back("Continue");
	s.push_back("Save Game");
	s.push_back("Go to Main Menu");
	s.push_back("Exit Game");
	changeMenuText(s);

	setLoaded(true);
}

void PauseMenu::changeMenuText(std::vector<std::string> s) {
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

void PauseMenu::alignSprite() {
	shipSpriteLeft1->getSprite().setPosition((round)(menuOption[selectedIndex]->getGlobalBounds().left - 50.f), (round)(menuOption[selectedIndex]->getGlobalBounds().top + menuOption[selectedIndex]->getGlobalBounds().getSize().y / 2));
	shipSpriteRight1->getSprite().setPosition((round)(menuOption[selectedIndex]->getGlobalBounds().left + menuOption[selectedIndex]->getGlobalBounds().width + 50.f), (round)(menuOption[selectedIndex]->getGlobalBounds().top + menuOption[selectedIndex]->getGlobalBounds().getSize().y / 2));
}

void PauseMenu::moveUp() {
	if (selectedIndex - 1 >= 0) {
		menuOption[selectedIndex]->_text.setColor(Color::White);
		selectedIndex--;
		menuOption[selectedIndex]->_text.setColor(Color::Red);
	}

	alignSprite();
}

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
	if (sf::Keyboard::isKeyPressed(Keyboard::Up) && !detectingKeys.keyUp) { moveUp(); }
	if (sf::Keyboard::isKeyPressed(Keyboard::Down) && !detectingKeys.keyDown) { moveDown(); }
	if (sf::Keyboard::isKeyPressed(Keyboard::Enter) && !detectingKeys.keyEnter) {
		switch (selectedIndex) {
		case 0:
			Engine::isGamePaused = false;
			Engine::isMenu = false;
			Engine::isPausedMenu = false;
			musicArray[MUSIC_LEVEL_3].play();
			Engine::ChangeScene(Engine::_lastScene);
			break;
		case 1:
			cout << "Game saved" << endl;
			break;
		case 2:
			Engine::isPausedMenu = false;
			Engine::isMenu = true;
			Engine::isGamePaused = true;
			if (upgradeMenu.ents.list.size() != 0) {
				upgradeMenu.UnLoad();
			}
			Engine::_lastScene->UnLoad();
			moveUp();
			moveUp();
			musicArray[MUSIC_TITLE_SCREEN].play();
			Engine::ChangeScene(&mainMenuScene);
			break;
		case 3:
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

	timer += dt;
	if (timer > 0.12) {
		if (Engine::isMenu && Engine::isPausedMenu) {
			//Check if the loaded sprite is the bottom, if so, load the top. And viceversa
			if (_titleShipLeftRect.left == _titleShipLeftRect.getSize().y / 1) { _titleShipLeftRect.left = 0; }
			else { _titleShipLeftRect.left = _titleShipLeftRect.getSize().y / 1; }
			shipSpriteLeft1->getSprite().setTextureRect(_titleShipLeftRect);

			if (_titleShipRightRect.left == _titleShipRightRect.getSize().y / 1) { _titleShipRightRect.left = 0; }
			else { _titleShipRightRect.left = _titleShipRightRect.getSize().y / 1; }
			shipSpriteRight1->getSprite().setTextureRect(_titleShipRightRect);
		}
		timer = 0;
	}
}

void PauseMenu::UnLoad() {
	shipSpriteRight1.reset();
	shipSpriteLeft1.reset();
	pauseView->setForDelete();

	setLoaded(false);
}
