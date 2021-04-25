#include "scene_title.h"
#include "../game.h"
#include "../components/cmp_sprite.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>

using namespace std;
using namespace sf;

void TitleScene::Load() {
	cout << "Title load \n";
	sf::View mainView(sf::FloatRect(0, 0, Engine::getWindowSize().x, Engine::getWindowSize().y));
	mainView.setViewport(sf::FloatRect(0, 0, 1, 1));
	//views.push_back(mainView);
	auto titleView = makeEntity();
	titleView->setView(mainView);

	auto backSprite = titleView->addComponent<SpriteComponent>();
	auto backgroundTexture = make_shared<sf::Texture>();
	auto backgroundRectangle = make_shared<sf::IntRect>();
	backgroundTexture->loadFromFile("res/img/title/title_background2.png");
	backSprite->setTexure(backgroundTexture);
	backSprite->getSprite().setOrigin(backSprite->getSprite().getGlobalBounds().width / 2, backSprite->getSprite().getGlobalBounds().height / 2 - (mainView.getSize().y / 2 - backSprite->getSprite().getGlobalBounds().height / 2));
	backSprite->getSprite().setPosition(Vector2f(mainView.getSize().x / 2, mainView.getSize().y / 2));

	txtCMP = titleView->addComponent<TextComponent>("Press ENTER");
	txtCMP->setFontSize(80u);
	txtCMP->_text.setColor(Color::Black);
	txtCMP->_text.setOutlineThickness(1);
	txtCMP->setPosition(Vector2f((round)(Engine::getWindowSize().x / 2 - txtCMP->getLocalBounds().width / 2), (round)(Engine::getWindowSize().y) - (round)(Engine::getWindowSize().y / 5)));
	setLoaded(true);
	timer = 0;
}

void TitleScene::Update(const double& dt) {
	timer += dt;
	if (timer <= 0.5f) { txtCMP->setVisible(true); }
	if (timer > 0.5f && timer <= 1.f) { txtCMP->setVisible(false); }
	if (timer > 1.f){ timer = 0; }

	if (sf::Keyboard::isKeyPressed(Keyboard::Enter)) {
		Engine::ChangeScene(&menu);
	}
}

void TitleScene::UnLoad() {
	cout << "Scene Title Unload" << endl;

	txtCMP.reset();
	Scene::UnLoad();
}