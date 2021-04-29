#include "scene_title.h"
#include "../game.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include "../components/cmp_sprite.h"

using namespace std;
using namespace sf;

std::shared_ptr<SpriteComponent> titleSpriteCMP;

void TitleScene::Load() {
	cout << "Title load \n";
	sf::View mainView(sf::FloatRect(0, 0, Engine::getWindowSize().x, Engine::getWindowSize().y));
	mainView.setViewport(sf::FloatRect(0, 0, 1, 1));
	auto titleView = makeEntity();
	titleView->setView(mainView);

	//load music
	for (int i = 0; i < 8; i++) {
		if (!musicArray[i].openFromFile(musicFiles[i])) {
		}
		else {
			cout << "Loaded music " << musicFiles[i] << endl;
		}
	}

	musicArray[MUSIC_TITLE_SCREEN].setPosition(0, 1, 50);	
	musicArray[MUSIC_TITLE_SCREEN].setVolume(25);
	musicArray[MUSIC_TITLE_SCREEN].setLoop(true);
	musicArray[MUSIC_TITLE_SCREEN].play();

	//Load background
	auto backSprite = titleView->addComponent<SpriteComponent>();
	auto backgroundTexture = make_shared<sf::Texture>();
	auto backgroundRectangle = make_shared<sf::IntRect>();
	backgroundTexture->loadFromFile("res/img/title/title_background2.png");
	backSprite->setTexure(backgroundTexture);
	backSprite->getSprite().setOrigin(backSprite->getSprite().getGlobalBounds().width / 2, backSprite->getSprite().getGlobalBounds().height / 2 - (mainView.getSize().y / 2 - backSprite->getSprite().getGlobalBounds().height / 2));
	backSprite->getSprite().setPosition(Vector2f(mainView.getSize().x / 2, mainView.getSize().y / 2));


	//Load title animation sprite sheet
	titleSpriteCMP = titleView->addComponent<SpriteComponent>();
	_titleText = make_shared<sf::Texture>();
	_titleRect = sf::IntRect();
	_titleText->loadFromFile("res/img/title/title_sprite.png");
	titleSpriteCMP->setTexure(_titleText);
	_titleRect.left = (round)(_titleText->getSize().x / 8 * 0);
	_titleRect.top = (round)(_titleText->getSize().y / 5 * 0);
	_titleRect.width = (round)(_titleText->getSize().x / 8);
	_titleRect.height = (round)(_titleText->getSize().y / 5);

	titleSpriteCMP->getSprite().setTextureRect(_titleRect);
	titleSpriteCMP->getSprite().setOrigin(titleSpriteCMP->getSprite().getGlobalBounds().width / 2, titleSpriteCMP->getSprite().getGlobalBounds().height / 2);
	titleSpriteCMP->getSprite().setPosition(Vector2f(mainView.getSize().x / 2, mainView.getSize().y / 2));

	//Load ENTER text
	txtCMP = titleView->addComponent<TextComponent>("Press ENTER");
	txtCMP->setFontSize(80u);
	txtCMP->_text.setColor(Color::Black);
	txtCMP->_text.setOutlineThickness(1);
	txtCMP->setPosition(Vector2f((round)(Engine::getWindowSize().x / 2 - txtCMP->getLocalBounds().width / 2), (round)(Engine::getWindowSize().y) - (round)(Engine::getWindowSize().y / 5)));
	setLoaded(true);
	timer = 0;
	titleTimer = 0;
	titleCol = 0;
	titleRow = 0;	

	setLoaded(true);
}

void TitleScene::Update(const double& dt) {
	timer += dt;
	if (timer <= 0.5f) { txtCMP->setVisible(true); }
	if (timer > 0.5f && timer <= 1.f) { txtCMP->setVisible(false); }
	if (timer > 1.f) { timer = 0; }

	titleTimer += dt * 10;
	if (titleTimer > titleCol && titleRow < 5) {
		_titleRect.left = (round)(_titleText->getSize().x / 8 * titleCol);
		_titleRect.top = (round)(_titleText->getSize().y / 5 * titleRow);
		titleCol++;
		if (titleCol >= 8) { titleCol = 0; titleTimer = 0; titleRow++; }

		titleSpriteCMP->getSprite().setTextureRect(_titleRect);
	}

	if (sf::Keyboard::isKeyPressed(Keyboard::Enter)) {
		Engine::ChangeScene(&mainMenuScene);
	}
}

void TitleScene::UnLoad() {
	cout << "Scene Title Unload" << endl;
	titleSpriteCMP.reset();
	txtCMP.reset();
	Scene::UnLoad();
}