#include "scene_settings.h"
#include "../game.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include "../components/cmp_sprite.h"

using namespace std;
using namespace sf;

std::shared_ptr<SpriteComponent> shipSpriteRight1;
std::shared_ptr<SpriteComponent> shipSpriteLeft1;

void MenuSettings::Load() {
	cout << "Title load \n";
	sf::View mainView(sf::FloatRect(0, 0, Engine::getWindowSize().x, Engine::getWindowSize().y));
	mainView.setViewport(sf::FloatRect(0, 0, 1, 1));
	//views.push_back(mainView);
	auto titleView = makeEntity();
	titleView->setView(mainView);


	for (int i = 0; i < 3; i++) {
		auto temp = titleView->addComponent<TextComponent>();
		temp->_text.setCharacterSize(80u);
		if (i == 0) { temp->_text.setString("Resolution"); temp->_text.setColor(Color::Red); };
		if (i == 1) { temp->_text.setString("Something Here"); temp->_text.setColor(Color::White); };
		if (i == 2) { temp->_text.setString("Back"); temp->_text.setColor(Color::White); };

		sf::FloatRect textRect = temp->getLocalBounds();
		temp->setOrigin(Vector2f((round)(textRect.left + textRect.width / 2.f), (round)(textRect.top + textRect.height / 2.f)));
		temp->setPosition(Vector2f((round)(mainView.getSize().x / 2), (round)(mainView.getSize().y / 3) + (mainView.getSize().y / 10 * i)));
	}

	menuOption = titleView->GetCompatibleComponent<TextComponent>();

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

	shipSpriteLeft1->getSprite().setPosition((round)(menuOption[selectedIndex]->getGlobalBounds().left - 50.f), (round)(menuOption[selectedIndex]->getGlobalBounds().top + menuOption[selectedIndex]->getGlobalBounds().getSize().y / 2));
	shipSpriteRight1->getSprite().setPosition((round)(menuOption[selectedIndex]->getGlobalBounds().left + menuOption[selectedIndex]->getGlobalBounds().width + 50.f), (round)(menuOption[selectedIndex]->getGlobalBounds().top + menuOption[selectedIndex]->getGlobalBounds().getSize().y / 2));


	selectedIndex = 0;
	timer = 0;
}

void MenuSettings::moveUp() {
	if (selectedIndex - 1 >= 0) {
		menuOption[selectedIndex]->_text.setColor(Color::White);
		selectedIndex--;
		menuOption[selectedIndex]->_text.setColor(Color::Red);
	}

	shipSpriteLeft1->getSprite().setPosition((round)(menuOption[selectedIndex]->getGlobalBounds().left - 50.f), (round)(menuOption[selectedIndex]->getGlobalBounds().top + menuOption[selectedIndex]->getGlobalBounds().getSize().y / 2));
	shipSpriteRight1->getSprite().setPosition((round)(menuOption[selectedIndex]->getGlobalBounds().left + menuOption[selectedIndex]->getGlobalBounds().width + 50.f), (round)(menuOption[selectedIndex]->getGlobalBounds().top + menuOption[selectedIndex]->getGlobalBounds().getSize().y / 2));
}

void MenuSettings::moveDown() {
	if (selectedIndex + 1 < 3) {
		menuOption[selectedIndex]->_text.setColor(Color::White);
		selectedIndex++;
		menuOption[selectedIndex]->_text.setColor(Color::Red);
	}
	shipSpriteLeft1->getSprite().setPosition((round)(menuOption[selectedIndex]->getGlobalBounds().left - 50.f), (round)(menuOption[selectedIndex]->getGlobalBounds().top + menuOption[selectedIndex]->getGlobalBounds().getSize().y / 2));
	shipSpriteRight1->getSprite().setPosition((round)(menuOption[selectedIndex]->getGlobalBounds().left + menuOption[selectedIndex]->getGlobalBounds().width + 50.f), (round)(menuOption[selectedIndex]->getGlobalBounds().top + menuOption[selectedIndex]->getGlobalBounds().getSize().y / 2));
}

int MenuSettings::getPressedItem() { return selectedIndex; }

void MenuSettings::UnLoad() {
}

void MenuSettings::Update(const double& dt) {
	timer += dt;

	if (timer > 0.15) {
		if (sf::Keyboard::isKeyPressed(Keyboard::Up)) { moveUp(); }
		if (sf::Keyboard::isKeyPressed(Keyboard::Down)) { moveDown(); }
		if (sf::Keyboard::isKeyPressed(Keyboard::Enter)) {
			switch (getPressedItem()) {
			case 0:
				break;
			case 1:
				break;
			case 2:
				Engine::ChangeScene(&mainMenuScene);
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
