#include "scene_pause_menu.h"
#include "../game.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include "../components/cmp_sprite.h"
#include "../components/cmp_sound.h"
#include <system_physics.h>
#include "../pools/entityPool.h"

using namespace std;
using namespace sf;

std::shared_ptr<SpriteComponent> shipSpriteRight1;
std::shared_ptr<SpriteComponent> shipSpriteLeft1;

void PauseMenu::Load() {
	cout << "Title load \n";
	auto titleView = makeEntity();
	titleView->setView(mainView);

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
			shipSpriteRight1 = temp;
			_titleShipRightRect = rec;
			shipSpriteRight1->getSprite().setRotation(-90.f);
		}
		if (i == 1) {
			shipSpriteLeft1 = temp;
			_titleShipLeftRect = rec;
			shipSpriteLeft1->getSprite().setRotation(90.f);
		}
	}

	selectedIndex = 0;
	timer = 0;

	menuOption1 = titleView->addComponent<TextComponent>();
	menuOption2 = titleView->addComponent<TextComponent>();
	menuOption3 = titleView->addComponent<TextComponent>();
	menuOption = titleView->GetCompatibleComponent<TextComponent>();

	s.clear();
	s.push_back("Continue");
	s.push_back("Go to Main Menu");
	s.push_back("Exit Game");
	changeMenuText(s, 3);
}

void PauseMenu::changeMenuText(std::vector<std::string> s, int index) {
	for (int i = 0; i < index; i++) {

		menuOption[i]->setFontSize(60u / windowScale.x);
		menuOption[i]->_text.setString(s[i]);
		menuOption[i]->_text.setColor(Color::White);
		if (i == selectedIndex) { menuOption[i]->_text.setColor(Color::Red); }

		sf::FloatRect textRect = menuOption[i]->getLocalBounds();
		menuOption[i]->setOrigin(Vector2f((round)(textRect.left + textRect.width / 2.f), (round)(textRect.top + textRect.height / 2.f)));
		menuOption[i]->setPosition(Vector2f(mainView.getCenter().x, (round)(mainView.getSize().y / 3) + (mainView.getSize().y / 10 * i)));
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

int PauseMenu::getPressedItem() { return selectedIndex; }

void PauseMenu::Update(const double& dt) {
	timer += dt;

	if (timer > 0.15) {
		if (sf::Keyboard::isKeyPressed(Keyboard::Up)) { moveUp(); }
		if (sf::Keyboard::isKeyPressed(Keyboard::Down)) { moveDown(); }
		if (sf::Keyboard::isKeyPressed(Keyboard::Enter)) {
			switch (getPressedItem()) {
			case 0:				
				Engine::ChangeScene(Engine::_pausedScene);
				Engine::isGamePaused = false;
				break;
			case 1:
				Engine::ChangeScene(&mainMenuScene);
				break;
			case 2:
				Engine::isGamePaused = false;
				Engine::GetWindow().close();
				break;
			default:
				break;
			}
		}

		//Check if the loaded sprite is the bottom, if so, load the top. And viceversa
		if (_titleShipLeftRect.top == _titleShipLeftRect.getSize().y / 1) { _titleShipLeftRect.top = 0; }
		else { _titleShipLeftRect.top = _titleShipLeftRect.getSize().y / 1; }
		shipSpriteLeft1->getSprite().setTextureRect(_titleShipLeftRect);

		if (_titleShipRightRect.top == _titleShipRightRect.getSize().y / 1) { _titleShipRightRect.top = 0; }
		else { _titleShipRightRect.top = _titleShipRightRect.getSize().y / 1; }
		shipSpriteRight1->getSprite().setTextureRect(_titleShipRightRect);

		timer = 0;
	}
}

void PauseMenu::UnLoad() {
	Engine::_pausedScene->UnLoad();
	shipSpriteRight1.reset();
	shipSpriteLeft1.reset();
}
