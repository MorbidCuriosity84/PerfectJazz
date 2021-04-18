#include "create_panels.h"
#include "../game.h"
#include "../components/cmp_text.h"
#include "../settings/player_settings.h"
#include "../player/cmp_player.h"
#include "../components/cmp_hp.h"

double timer;
shared_ptr<Entity> leftPanel;

void Panels::createPanels(Scene* _scene) {


	auto currentPlayer = player->GetCompatibleComponent<PlayerComponent>()[0];
	//Left Panel
	{
		leftPanel = _scene->makeEntity();
		leftPanel->setView(leftView);
		//CARLOS - I had to add this sprite before so the HPComponent updates properly
		leftPanel->addComponent<SpriteComponent>();
				
		auto HP = leftPanel->addComponent<HPComponent>(_scene, currentPlayer->_playerSettings.maxHP);
		auto playerName = leftPanel->addComponent<TextComponent>("PLAYER 1");
		auto score = leftPanel->addComponent<TextComponent>(to_string(currentPlayer->_playerSettings.score));

		//Player name
		auto row = leftView.getSize().y / playerName.get()->getLocalBounds().height;
		auto offset = playerName.get()->getLocalBounds().height / 2;
		playerName->setPosition(Vector2f(0.f + offset, row * 1));

		//Player score
		score->setPosition(Vector2f(0.f + offset * 3, row * 2));

		//Player HP
		auto HPText = leftPanel->GetCompatibleComponent<TextComponent>()[0];
		HP->setDynamic(false);
		HP->setPosition(Vector2f(0.f + offset * 3, row * 3 + offset));
		HP->setScale(Vector2f(4.f, 3.f));
		auto s = leftPanel->GetCompatibleComponent<SpriteComponent>()[1];
		HPText->setPosition(Vector2f((0.f + offset * 3 + s->getSprite().getTextureRect().getSize().x / 2), (HP->getPosition().y + s->getSprite().getTextureRect().getSize().y / 4)));
		HPText->setFontSize(20u);
		HPText->setText(to_string(currentPlayer->_playerSettings.hp) + " / " + to_string(currentPlayer->_playerSettings.maxHP));
		leftPanel->addComponent<SpriteComponent>();
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

	if (timer > 1) {

		auto currentPlayer = player->GetCompatibleComponent<PlayerComponent>()[0];
		auto currentPlayerHP = player->GetCompatibleComponent<HPComponent>()[0];
		auto hpText = leftPanel->GetCompatibleComponent<TextComponent>()[0];
		auto score = leftPanel->GetCompatibleComponent<TextComponent>()[2];
		auto hp = leftPanel->GetCompatibleComponent<HPComponent>()[0];
		auto spr = leftPanel->GetCompatibleComponent<SpriteComponent>();

		hp->setHP(currentPlayerHP->getHP());
		score ->setText(to_string(currentPlayer->_playerSettings.score));
		hpText->setText(to_string(currentPlayerHP->getHP()) + " / " + to_string(currentPlayer->_playerSettings.maxHP));
		timer = 0;
	}
}

void Panels::render() {
}
