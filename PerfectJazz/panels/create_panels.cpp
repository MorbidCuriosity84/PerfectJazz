#include "create_panels.h"
#include "../player/cmp_player.h"
#include "../components/cmp_text.h"
#include "../components/cmp_hp.h"
#include "../components/cmp_sprite.h"

double timer;
using namespace std;
using namespace sf;

shared_ptr<Entity> leftPanel;

void Panels::createPanels(Scene* _scene) {


	auto currentPlayer = player->GetCompatibleComponent<PlayerComponent>()[0];
	//Left Panel
	{
		leftPanel = _scene->makeEntity();
		leftPanel->setView(leftView);
		//CARLOS - I had to add this sprite before so the HPComponent updates properly
		leftPanel->addComponent<SpriteComponent>();

		auto hp = leftPanel->addComponent<HPComponent>(_scene, currentPlayer->_playerSettings.maxHP);
		hp->loadHP();
		auto playerText = leftPanel->addComponent<TextComponent>("PLAYER 1");
		auto score = leftPanel->addComponent<TextComponent>("Score: " + to_string(currentPlayer->_playerSettings.score));
		auto coins = leftPanel->addComponent<TextComponent>("Coins: " + to_string(currentPlayer->_playerSettings.shopPoints));

		//Player name
		auto row = (round)(leftView.getSize().y / 30);
		auto col = (round)(leftView.getSize().x / 10);
		playerText->setFontSize(50u);
		playerText->setPosition(Vector2f((round)(leftView.getSize().x / 2 - playerText->getGlobalBounds().getSize().x / 2), (round)(row * 1 - row / 2)));

		//Player score
		score->setPosition(Vector2f(col * 1, row * 4));
		score->setFontSize(40u);

		//Player coins
		coins->setPosition(Vector2f(col * 2, row * 5));
		coins->setFontSize(40u);

		//Player HP
		auto hpText = leftPanel->GetCompatibleComponent<TextComponent>()[0];
		auto spr = leftPanel->GetCompatibleComponent<SpriteComponent>();
		spr[1]->isFollowingParent(false);
		spr[2]->isFollowingParent(false);
		spr[1]->getSprite().setColor(Color::White);
		spr[2]->getSprite().setColor(Color(205, 0, 0));

		hp->setDynamic(false);
		hp->setScale(Vector2f(4.f, 3.f));

		spr[1]->getSprite().setPosition(Vector2f((round)(leftView.getSize().x / 2 - spr[2]->getSprite().getGlobalBounds().width / 2), row * 3));
		spr[2]->getSprite().setPosition(Vector2f((round)(leftView.getSize().x / 2 - spr[2]->getSprite().getGlobalBounds().width / 2), row * 3));
		hpText->setText(to_string(currentPlayer->_playerSettings.hp) + "/" + to_string(currentPlayer->_playerSettings.maxHP));
		hpText->setFontSize(34u);
		hpText->setPosition(Vector2f((round)(spr[1]->getSprite().getPosition().x + spr[1]->getSprite().getGlobalBounds().width / 2 - hpText->getGlobalBounds().width / 2), (round)(spr[1]->getSprite().getPosition().y - hpText->getGlobalBounds().height / 2)));
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

		auto currentPlayer = player->GetCompatibleComponent<PlayerComponent>()[0];
		auto currentPlayerHP = player->GetCompatibleComponent<HPComponent>()[0];
		auto hpText = leftPanel->GetCompatibleComponent<TextComponent>()[0];
		auto score = leftPanel->GetCompatibleComponent<TextComponent>()[2];
		auto coins = leftPanel->GetCompatibleComponent<TextComponent>()[3];
		auto hp = leftPanel->GetCompatibleComponent<HPComponent>()[0];
		auto spr = leftPanel->GetCompatibleComponent<SpriteComponent>();

		hp->setHP(currentPlayerHP->getHP());
		score->setText("Score: " + to_string(currentPlayer->_playerSettings.score));
		coins->setText("Coins: " + to_string(currentPlayer->_playerSettings.shopPoints));
		hpText->setText(to_string(currentPlayerHP->getHP()) + "/" + to_string(currentPlayer->_playerSettings.maxHP));
		hpText->setPosition(Vector2f((round)((spr[1]->getSprite().getPosition().x + spr[1]->getSprite().getGlobalBounds().width / 2 - hpText->getGlobalBounds().width / 2)), (round)(spr[1]->getSprite().getPosition().y - hpText->getGlobalBounds().height / 2)));

		timer = 0;

	}
}

void Panels::render() {
}
