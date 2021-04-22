#include "create_panels.h"
#include "../player/cmp_player.h"


double timer;
using namespace std;
using namespace sf;

shared_ptr<Entity> leftPanel;

static shared_ptr<SpriteComponent> spriteCMP;
static shared_ptr<HPComponent> hpCMP;
static shared_ptr<TextComponent> playerTxtCMP;
static shared_ptr<TextComponent> scoreTxtCMP;
static shared_ptr<TextComponent> coinsTxtCMP;
static shared_ptr<TextComponent> lifesTxtCMP;

void Panels::createPanels(Scene* _scene) {

	auto playerCMP = player->GetCompatibleComponent<PlayerComponent>()[0];
	
	//Left Panel
	{
		leftPanel = _scene->makeEntity();
		leftPanel->setView(leftView);
		//CARLOS - I had to add this sprite before so the HPComponent updates properly
		leftPanel->addComponent<SpriteComponent>();

		hpCMP = leftPanel->addComponent<HPComponent>(_scene, playerCMP->_playerSettings.maxHP);
		hpCMP->loadHP();		
		
		playerTxtCMP = leftPanel->addComponent<TextComponent>("PLAYER 1");
		scoreTxtCMP = leftPanel->addComponent<TextComponent>("Score: " + to_string(playerCMP->_playerSettings.score));
		coinsTxtCMP = leftPanel->addComponent<TextComponent>("Coins: " + to_string(playerCMP->_playerSettings.shopPoints));
		lifesTxtCMP = leftPanel->addComponent<TextComponent>("Lifes: " + to_string(playerCMP->_playerSettings.lifes));

		//Player name
		auto row = (round)(leftView.getSize().y / 30);
		auto col = (round)(leftView.getSize().x / 10);
		playerTxtCMP->setFontSize(50u);
		sf::FloatRect textRect = playerTxtCMP->getLocalBounds();
		playerTxtCMP->setOrigin(Vector2f((round)(textRect.left + textRect.width / 2.f), (round)(textRect.top + textRect.height / 2.f)));
		playerTxtCMP->setPosition(Vector2f((round)(leftView.getSize().x / 2), (round)(row * 2)));

		//Player score
		scoreTxtCMP->setPosition(Vector2f(col * 1, row * 4));
		scoreTxtCMP->setFontSize(40u);

		//Player coins
		coinsTxtCMP->setPosition(Vector2f(col * 2, row * 5));
		coinsTxtCMP->setFontSize(40u);

		//Player lifes
		lifesTxtCMP->setPosition(Vector2f(col * 2, row * 6));
		lifesTxtCMP->setFontSize(40u);

		//Player HP
		hpCMP->underHPBar->isFollowingParent(false);
		hpCMP->overHPBar->isFollowingParent(false);
		hpCMP->underHPBar->getSprite().setColor(Color::White);
		hpCMP->overHPBar->getSprite().setColor(Color(205, 0, 0));

		hpCMP->setDynamic(false);
		hpCMP->setScale(Vector2f(4.f, 3.f));

		hpCMP->underHPBar->getSprite().setPosition(Vector2f((round)(leftView.getSize().x / 2 - hpCMP->overHPBar->getSprite().getGlobalBounds().width / 2), row * 3));
		hpCMP->overHPBar->getSprite().setPosition(Vector2f((round)(leftView.getSize().x / 2 - hpCMP->overHPBar->getSprite().getGlobalBounds().width / 2), row * 3));

		hpCMP->textCMP->setText(to_string(playerCMP->_playerSettings.hp) + "/" + to_string(playerCMP->_playerSettings.maxHP));
		hpCMP->textCMP->setFontSize(34u);
		hpCMP->textCMP->setPosition(Vector2f((hpCMP->underHPBar->getSprite().getPosition().x + hpCMP->underHPBar->getSprite().getGlobalBounds().width / 2 - hpCMP->textCMP->getGlobalBounds().width / 2), (round)(hpCMP->underHPBar->getSprite().getPosition().y - hpCMP->textCMP->getGlobalBounds().height / 2)));
	}

	//Right Panel
	{
		//auto txt2 = _scene->makeEntity();
		//txt2->setView(rightView);
		//auto t2 = txt2->addComponent<TextComponent>("This is the right view");
		//t2->setFontSize(18u);
	}
}

void Panels::update(double dt) {
	timer += dt;

	if (timer > 0.1) {

		auto playerCMP = player->GetCompatibleComponent<PlayerComponent>()[0];

		hpCMP->setHP(playerCMP->hpCMP->getHP());
		scoreTxtCMP->setText("Score: " + to_string(playerCMP->_playerSettings.score));
		coinsTxtCMP	->setText("Coins: " + to_string(playerCMP->_playerSettings.shopPoints));
		hpCMP->textCMP->setText(to_string(playerCMP->hpCMP->getHP()) + "/" + to_string(playerCMP->_playerSettings.maxHP));
		hpCMP->textCMP->setPosition(Vector2f((round)((hpCMP->underHPBar->getSprite().getPosition().x + hpCMP->underHPBar->getSprite().getGlobalBounds().width / 2 - hpCMP->textCMP->getGlobalBounds().width / 2)), (round)(hpCMP->underHPBar->getSprite().getPosition().y - hpCMP->textCMP->getGlobalBounds().height / 2)));

		lifesTxtCMP->setText("Lifes: " + to_string(playerCMP->_playerSettings.lifes));

		timer = 0;
	}
}

void Panels::render() {
}

Panels::Panels() {}
