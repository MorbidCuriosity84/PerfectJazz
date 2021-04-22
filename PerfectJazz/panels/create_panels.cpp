#include "create_panels.h"
#include "../player/cmp_player.h"
#include "../components/cmp_text.h"
#include "../components/cmp_hp.h"
#include "../components/cmp_sprite.h"
#include "../settings/texture_helper_settings.h"


double timer;
using namespace std;
using namespace sf;

shared_ptr<Entity> leftPanel;
shared_ptr<SpriteComponent> playerLifeSpriteCMP1;
shared_ptr<SpriteComponent> playerLifeSpriteCMP2;
shared_ptr<SpriteComponent> playerLifeSpriteCMP3;
shared_ptr<SpriteComponent> playerLifeSpriteCMP4;
shared_ptr<SpriteComponent> playerLifeSpriteCMP5;
shared_ptr<SpriteComponent> tempSprite;
shared_ptr<HPComponent> hpCMP;
shared_ptr<PlayerComponent> playerCMP;
shared_ptr<TextComponent> playerTxtCMP;
shared_ptr<TextComponent> scoreTxtCMP;
shared_ptr<TextComponent> coinsTxtCMP;
shared_ptr<TextComponent> playerSpeedTxtCMP;
shared_ptr<TextComponent> playerBulletPowerTxtCMP;
shared_ptr<TextComponent> playerFireRateTxtCMP;
shared_ptr<TextComponent> playerBulletNumberTxtCMP;
textureSettings playerLifeTextureHelper;
Texture playerLifeTexture;
sf::IntRect playerLifeRec;
int currentLifes;


void Panels::createPanels(Scene* _scene) {

	auto playerCMP = player->GetCompatibleComponent<PlayerComponent>()[0];
	//Left Panel
	{
		leftPanel = _scene->makeEntity();
		leftPanel->setView(leftView);

		//Adding components
		//TO-DO: add title
		auto title = playerLifeSpriteCMP1 = leftPanel->addComponent<SpriteComponent>();
		hpCMP = leftPanel->addComponent<HPComponent>(_scene, playerCMP->_playerSettings.maxHP);
		hpCMP->loadHP();
		playerTxtCMP = leftPanel->addComponent<TextComponent>("PLAYER 1");
		scoreTxtCMP = leftPanel->addComponent<TextComponent>("Score: " + to_string(playerCMP->_playerSettings.score));
		coinsTxtCMP = leftPanel->addComponent<TextComponent>("Coins: " + to_string(playerCMP->_playerSettings.shopPoints));
		playerSpeedTxtCMP = leftPanel->addComponent<TextComponent>("Ship Speed: " + to_string(playerCMP->getFlySpeedUpdateState()));
		playerBulletPowerTxtCMP = leftPanel->addComponent<TextComponent>("Damage: " + to_string(playerCMP->getDamageUpdateState()));
		playerFireRateTxtCMP = leftPanel->addComponent<TextComponent>("Fire rate: " + to_string(playerCMP->getFireRateUpdateState()));
		playerBulletNumberTxtCMP = leftPanel->addComponent<TextComponent>("Spread: " + to_string(playerCMP->getBulletNumberUpdateState()));

		//Player name
		auto row = (round)(leftView.getSize().y / 30);
		auto col = (round)(leftView.getSize().x / 10);
		playerTxtCMP->setFontSize(50u);
		sf::FloatRect textRect = playerTxtCMP->getLocalBounds();
		playerTxtCMP->setOrigin(Vector2f((round)(textRect.left + textRect.width / 2.f), (round)(textRect.top + textRect.height / 2.f)));
		playerTxtCMP->setPosition(Vector2f((round)(leftView.getSize().x / 2), (round)(row * 2.5)));

		//Player life icons
		playerLifeTexture.loadFromFile("res/img/others/player_life.png");

		for (int i = 5; i > 0; i--) { //Setting 4 life sprites
			auto tempSprite = leftPanel->addComponent<SpriteComponent>();
			tempSprite->isFollowingParent(false);
			tempSprite->getSprite().setTexture(playerLifeTexture);
			tempSprite->getSprite().setTextureRect(playerLifeRec);
			tempSprite->getSprite().setPosition(Vector2f(col * (i)+i * 10, row * 0.5));
			tempSprite->getSprite().setColor(Color::Red);

			if (i == 5) { playerLifeSpriteCMP5 = tempSprite; }
			if (i == 4) { playerLifeSpriteCMP4 = tempSprite; }
			if (i == 3) { playerLifeSpriteCMP3 = tempSprite; }
			if (i == 2) { playerLifeSpriteCMP2 = tempSprite; }
			if (i == 1) { playerLifeSpriteCMP1 = tempSprite; }
		}
		currentLifes = playerCMP->_playerSettings.lifes;

		playerLifeRec.left = (round)(playerLifeTexture.getSize().x * 0);
		playerLifeRec.top = (round)(playerLifeTexture.getSize().y * 0);
		playerLifeRec.width = (round)(playerLifeTexture.getSize().x);
		playerLifeRec.height = (round)(playerLifeTexture.getSize().y);

		for (int i = 1; i <= playerCMP->getPlayerLifes(); i++) {

			if (i == 5) { playerLifeSpriteCMP5->getSprite().setTextureRect(playerLifeRec); }
			if (i == 4) { playerLifeSpriteCMP4->getSprite().setTextureRect(playerLifeRec); }
			if (i == 3) { playerLifeSpriteCMP3->getSprite().setTextureRect(playerLifeRec); }
			if (i == 2) { playerLifeSpriteCMP2->getSprite().setTextureRect(playerLifeRec); }
			if (i == 1) { playerLifeSpriteCMP1->getSprite().setTextureRect(playerLifeRec); }
		}


		//Player score
		scoreTxtCMP->setPosition(Vector2f(col * 1, row * 4));
		scoreTxtCMP->setFontSize(40u);

		//Player coins
		coinsTxtCMP->setPosition(Vector2f(col * 1, row * 5));
		coinsTxtCMP->setFontSize(40u);

		//Player PowerUps
		playerSpeedTxtCMP->setPosition(Vector2f(col * 6.5 + playerSpeedTxtCMP->_text.getGlobalBounds().left - playerSpeedTxtCMP->_text.getGlobalBounds().width, row * 10));
		playerSpeedTxtCMP->setFontSize(30u);

		//Bullets PowerUps
		playerBulletPowerTxtCMP->setPosition(Vector2f(col * 6.5 + playerBulletPowerTxtCMP->_text.getGlobalBounds().left - playerBulletPowerTxtCMP->_text.getGlobalBounds().width, row * 11));
		playerBulletPowerTxtCMP->setFontSize(30u);
		playerFireRateTxtCMP->setPosition(Vector2f(col * 6.5 + playerFireRateTxtCMP->_text.getGlobalBounds().left - playerFireRateTxtCMP->_text.getGlobalBounds().width, row * 12));
		playerFireRateTxtCMP->setFontSize(30u);
		playerBulletNumberTxtCMP->setPosition(Vector2f(col * 6.5 + playerBulletNumberTxtCMP->_text.getGlobalBounds().left - playerBulletNumberTxtCMP->_text.getGlobalBounds().width, row * 13));
		playerBulletNumberTxtCMP->setFontSize(30u);

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
	}
}

void Panels::setLifeSprites() {

	auto playerCMP = player->GetCompatibleComponent<PlayerComponent>()[0];

	if (currentLifes < playerCMP->getPlayerLifes()) {
		playerLifeRec.width = (round)(playerLifeTexture.getSize().x);
		playerLifeRec.height = (round)(playerLifeTexture.getSize().y);

		if (currentLifes == 5) { playerLifeSpriteCMP5->getSprite().setTextureRect(playerLifeRec); }
		if (currentLifes == 4) { playerLifeSpriteCMP4->getSprite().setTextureRect(playerLifeRec); }
		if (currentLifes == 3) { playerLifeSpriteCMP3->getSprite().setTextureRect(playerLifeRec); }
		if (currentLifes == 2) { playerLifeSpriteCMP2->getSprite().setTextureRect(playerLifeRec); }
		if (currentLifes == 1) { playerLifeSpriteCMP1->getSprite().setTextureRect(playerLifeRec); }
	}

	if (currentLifes > playerCMP->getPlayerLifes()) {
		playerLifeRec.width = (round)(playerLifeTexture.getSize().x * 0);
		playerLifeRec.height = (round)(playerLifeTexture.getSize().y * 0);

		if (currentLifes == 5) { playerLifeSpriteCMP5->getSprite().setTextureRect(playerLifeRec); }
		if (currentLifes == 4) { playerLifeSpriteCMP4->getSprite().setTextureRect(playerLifeRec); }
		if (currentLifes == 3) { playerLifeSpriteCMP3->getSprite().setTextureRect(playerLifeRec); }
		if (currentLifes == 2) { playerLifeSpriteCMP2->getSprite().setTextureRect(playerLifeRec); }
		if (currentLifes == 1) { playerLifeSpriteCMP1->getSprite().setTextureRect(playerLifeRec); }
	}

	currentLifes = playerCMP->_playerSettings.lifes;
}

void Panels::update(double dt) {
	timer += dt;

	if (timer > 0.1) {

		auto playerCMP = player->GetCompatibleComponent<PlayerComponent>()[0];

		hpCMP->setHP(playerCMP->hpCMP->getHP());
		hpCMP->textCMP->setText(to_string(playerCMP->hpCMP->getHP()) + "/" + to_string(playerCMP->_playerSettings.maxHP));
		hpCMP->textCMP->setPosition(Vector2f((round)((hpCMP->underHPBar->getSprite().getPosition().x + hpCMP->underHPBar->getSprite().getGlobalBounds().width / 2 - hpCMP->textCMP->getGlobalBounds().width / 2)), (round)(hpCMP->underHPBar->getSprite().getPosition().y - hpCMP->textCMP->getGlobalBounds().height / 2)));

		scoreTxtCMP->setText("Score: " + to_string(playerCMP->_playerSettings.score));
		coinsTxtCMP->setText("Coins: " + to_string(playerCMP->_playerSettings.shopPoints));
		playerSpeedTxtCMP->setText("Ship Speed: " + to_string(playerCMP->getFlySpeedUpdateState()));
		playerBulletPowerTxtCMP->setText("Damage: " + to_string(playerCMP->getDamageUpdateState()));
		playerFireRateTxtCMP->setText("Fire rate: " + to_string(playerCMP->getFireRateUpdateState()));
		playerBulletNumberTxtCMP->setText("Spread: " + to_string(playerCMP->getBulletNumberUpdateState()));

		if (currentLifes != playerCMP->_playerSettings.lifes) {
			setLifeSprites();
		}

		timer = 0;
	}
}

void Panels::render() {
}
