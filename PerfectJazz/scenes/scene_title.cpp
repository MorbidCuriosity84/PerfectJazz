#include "scene_title.h"
#include "../game.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include "../components/cmp_sprite.h"

using namespace std;
using namespace sf;

std::shared_ptr<SpriteComponent> titleSpriteCMP;
std::shared_ptr<Entity> titleView;

//Loads the title scene
void TitleScene::Load() {
	titleView = makeEntity();
	titleView->setView(menuView);

	//Loads music
	for (int i = 0; i < 8; i++) {
		if (!musicArray[i].openFromFile(musicFiles[i])) {
		}
		else {
			cout << "Loaded music " << musicFiles[i] << endl;
		}
	}
	//Sets the music settings
	musicArray[MUSIC_TITLE_SCREEN].setPosition(0, 1, 50);	
	musicArray[MUSIC_TITLE_SCREEN].setVolume(25);
	musicArray[MUSIC_TITLE_SCREEN].setLoop(true);
	musicArray[MUSIC_TITLE_SCREEN].play();

	//Loads background and adds the sprite component to the titleview
	auto backSprite = titleView->addComponent<SpriteComponent>();
	auto backgroundTexture = make_shared<sf::Texture>();
	auto backgroundRectangle = make_shared<sf::IntRect>();
	backgroundTexture->loadFromFile("res/img/title/title_background2.png");
	backSprite->setTexure(backgroundTexture);
	backSprite->getSprite().setScale(windowScale);
	backSprite->getSprite().setOrigin(Vector2f((round)(backSprite->getSprite().getGlobalBounds().left + backSprite->getSprite().getGlobalBounds().width / 2), (round)(backSprite->getSprite().getGlobalBounds().height / 2)));
	backSprite->getSprite().setPosition(Vector2f(menuView.getSize().x/2, menuView.getSize().y / 2));


	//Loads the title animation sprite sheet
	titleSpriteCMP = titleView->addComponent<SpriteComponent>();
	_titleText = make_shared<sf::Texture>();
	_titleRect = sf::IntRect();
	_titleText->loadFromFile("res/img/title/title_sprite.png");
	titleSpriteCMP->setTexure(_titleText);
	_titleRect.left = (round)(_titleText->getSize().x / 8 * 0);
	_titleRect.top = (round)(_titleText->getSize().y / 5 * 0);
	_titleRect.width = (round)(_titleText->getSize().x / 8);
	_titleRect.height = (round)(_titleText->getSize().y / 5);
	titleSpriteCMP->getSprite().setScale(windowScale);
	titleSpriteCMP->getSprite().setTextureRect(_titleRect);
	titleSpriteCMP->getSprite().setOrigin(titleSpriteCMP->getSprite().getLocalBounds().width / 2, titleSpriteCMP->getSprite().getLocalBounds().height / 2);
	titleSpriteCMP->getSprite().setPosition(Vector2f(menuView.getSize().x / 2, menuView.getSize().y / 2));

	//Creates a text component
	txtCMP = titleView->addComponent<TextComponent>("Press ENTER");
	txtCMP->setFontSize(80u);
	txtCMP->_text.setColor(Color::Black);
	txtCMP->_text.setOutlineThickness(1);
	txtCMP->setPosition(Vector2f((round)(Engine::getWindowSize().x / 2 - txtCMP->getLocalBounds().width / 2), (round)(Engine::getWindowSize().y) - (round)(Engine::getWindowSize().y / 5)));
	setLoaded(true);

	//Sets up initial values for timers, titleCol and titleRow
	timer = 0;
	titleTimer = 0;
	titleCol = 0;
	titleRow = 0;	

	setLoaded(true);
}

void TitleScene::Update(const double& dt) {
	timer += dt;
	//Allows the text "Press ENTER" to appear and dissapear 
	if (timer <= 0.5f) { txtCMP->setVisible(true); }
	if (timer > 0.5f && timer <= 1.f) { txtCMP->setVisible(false); }
	if (timer > 1.f) { timer = 0; }

	//Allows the animation for the title to happens
	titleTimer += dt * 10;
	if (titleTimer > titleCol && titleRow < 5) {
		_titleRect.left = (round)(_titleText->getSize().x / 8 * titleCol);
		_titleRect.top = (round)(_titleText->getSize().y / 5 * titleRow);
		titleCol++;
		if (titleCol >= 8) { titleCol = 0; titleTimer = 0; titleRow++; }

		titleSpriteCMP->getSprite().setTextureRect(_titleRect);
	}

	//Enters the main menu scene
	if (sf::Keyboard::isKeyPressed(Keyboard::Enter) && !detectingKeys.keyEnter) {
		Engine::ChangeScene(&mainMenuScene);
	}
	detectingKeys.detectingKeys();
}

//Unloads the titleScene
void TitleScene::UnLoad() {
	titleSpriteCMP.reset();
	txtCMP.reset();
	titleView->setForDelete();
	Scene::UnLoad();
}