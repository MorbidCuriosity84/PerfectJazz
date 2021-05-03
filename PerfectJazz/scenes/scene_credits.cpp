#include "scene_credits.h"
#include "../game.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include "../components/cmp_sprite.h"

using namespace std;
using namespace sf;

std::shared_ptr<SpriteComponent> creditSpriteCMP;
std::shared_ptr<Entity> creditView;

std::string texts[6] = {
	"We would also like to thank Tom",
	"And Graeme, of course",
	"We couldnt have done it without you",
	"Also the llama. Hidden in the code",
	"Thank you =)",
	"Press enter to return to main menu",
};

void CreditScene::Load()
{
	timer = 3.0;
	creditView = makeEntity();
	creditView->setView(menuView);

	//Loads music
	for (int i = 0; i < 8; i++) {
		if (!musicArray[i].openFromFile(musicFiles[i])) {
		}
		else {
			cout << "Loaded music " << musicFiles[i] << endl;
		}
	}
	//Sets the music settings
	musicArray[MUSIC_UPGRADE_MENU].setPosition(0, 1, 50);
	musicArray[MUSIC_UPGRADE_MENU].setVolume(25);
	musicArray[MUSIC_UPGRADE_MENU].setLoop(true);
	musicArray[MUSIC_UPGRADE_MENU].play();

	//Loads background and adds the sprite component to the titleview
	auto backSprite = creditView->addComponent<SpriteComponent>();
	auto backgroundTexture = make_shared<sf::Texture>();
	auto backgroundRectangle = make_shared<sf::IntRect>();
	backgroundTexture->loadFromFile("res/img/title/title_background2.png");
	backSprite->setTexure(backgroundTexture);
	backSprite->getSprite().setScale(windowScale);
	backSprite->getSprite().setOrigin(Vector2f((round)(backSprite->getSprite().getGlobalBounds().left + backSprite->getSprite().getGlobalBounds().width / 2), (round)(backSprite->getSprite().getGlobalBounds().height / 2)));
	backSprite->getSprite().setPosition(Vector2f(menuView.getSize().x / 2, menuView.getSize().y / 2));

	//Creates a text component
	txtCMP = creditView->addComponent<TextComponent>("Thank you for playing our game");
	txtCMP->setFontSize(80u);
	txtCMP->_text.setColor(Color::White);
	txtCMP->_text.setOutlineThickness(1);
	txtCMP->setPosition(Vector2f((round)(Engine::getWindowSize().x / 2 - txtCMP->getLocalBounds().width / 2), (round)(Engine::getWindowSize().y) - (round)(Engine::getWindowSize().y / 2)));
	setLoaded(true);

	setLoaded(true);
}

void CreditScene::UnLoad()
{
	creditSpriteCMP.reset();
	txtCMP.reset();
	creditView->setForDelete();
	Scene::UnLoad();
}

void CreditScene::Update(const double& dt)
{
	timer -= dt;
	if (timer < 0 && index < 6) {		
		txtCMP->setText(texts[index]);
		index++;
		timer = 3.0;
	}
	//Takes you back to the main menu
	if (sf::Keyboard::isKeyPressed(Keyboard::Enter) && !detectingKeys.keyEnter) {
		Engine::ChangeScene(&mainMenuScene);
	}
	detectingKeys.detectingKeys();
}
