#include "scene_upgrade_menu.h"
#include <system_physics.h>
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include "../game.h"
#include "../components/cmp_sprite.h"
#include "../components/cmp_sound.h"
#include "../player/cmp_player.h"
#include "../player/creates_player.h"
#include "../services/load_save_game.h"

using namespace std;
using namespace sf;

std::shared_ptr<SpriteComponent> upgradeShipSprite;
std::shared_ptr<PlayerComponent> upgradedPlayerCMP;
std::shared_ptr<SpriteComponent> cointSprite;
std::shared_ptr<SpriteComponent> cointSprite2;
std::shared_ptr<SpriteComponent> cointSprite3;
std::shared_ptr<SpriteComponent> cointSprite4;
std::shared_ptr<SpriteComponent> cointSprite5;
std::vector<shared_ptr<SpriteComponent>> allCoinsSprite;
std::shared_ptr<Entity> upgradeView;

void UpgradeMenu::Load() {

	//Loading music
	for (int i = 0; i < 8; i++) {
		if (!musicArray[i].openFromFile(musicFiles[i])) {
		}
		else {
			cout << "Loaded music " << musicFiles[i] << endl;
		}
	}

	musicArray[MUSIC_UPGRADE_MENU].setPosition(0, 1, 50);
	musicArray[MUSIC_UPGRADE_MENU].setVolume(25);
	musicArray[MUSIC_UPGRADE_MENU].setLoop(true);
	musicArray[MUSIC_UPGRADE_MENU].play();

	//Creates a view for the menu
	cout << "Title load \n";
	sf::View tempMain(sf::FloatRect(0, 0, Engine::getWindowSize().x, Engine::getWindowSize().y));
	menuView = tempMain;
	menuView.setViewport(sf::FloatRect(0, 0, 1.f, 1.f));
	//Creates an entity and asgins it to the view
	upgradeView = makeEntity();
	upgradeView->setView(menuView);

	//Getting the player component
	upgradedPlayerCMP = player->GetCompatibleComponent<PlayerComponent>()[0];

	//Set up Column and Row size
	col = menuView.getSize().x / 20;
	row = menuView.getSize().y / 20;

	//Initializing timer and index
	selectedIndex = 0;
	timer = 0;

	//Setting up multipliers for upgrades
	fireRateMulti = 0.95;
	flySpeedMulti = 1.10;
	damageMulti = 1.20;
	maxHPMulti = 1.05;

	//Setting up max upgrades
	maxHPUpgrade = 999999;
	maxFlySpeed = 400;
	maxBulletDamage = 2500;
	maxFireRate = 0.1;

	//Adding Sprite component for the ship and coin
	upgradeShipSprite = upgradeView->addComponent<SpriteComponent>();
	_upgradeShipTex = make_shared<sf::Texture>();
	_upgradeShipRect = sf::IntRect();
	_upgradeShipTex->loadFromFile("res/img/player/upgrade_player.png");
	cointSprite = upgradeView->addComponent<SpriteComponent>();
	cointSprite2 = upgradeView->addComponent<SpriteComponent>();
	cointSprite3 = upgradeView->addComponent<SpriteComponent>();
	cointSprite4 = upgradeView->addComponent<SpriteComponent>();
	cointSprite5 = upgradeView->addComponent<SpriteComponent>();
	allCoinsSprite = upgradeView->GetCompatibleComponent <SpriteComponent>();
	_coinTex = make_shared<sf::Texture>();
	_coinRect = sf::IntRect();
	_coinTex->loadFromFile("res/img/powerups/coins.png");

	//Settign rectangle for the ship sprite, rotation and scale
	upgradeShipSprite->setTexure(_upgradeShipTex);
	upgradeShipSprite->getSprite().setScale(Vector2f(3.f, 3.f) * windowScale);
	_upgradeShipRect.left = (round)(_upgradeShipTex->getSize().x / 5 * 1);
	_upgradeShipRect.top = (round)(_upgradeShipTex->getSize().y / 2 * 0);
	_upgradeShipRect.width = (round)(_upgradeShipTex->getSize().x / 5);
	_upgradeShipRect.height = (round)(_upgradeShipTex->getSize().y / 1);
	upgradeShipSprite->getSprite().setTextureRect(_upgradeShipRect);
	upgradeShipSprite->getSprite().setOrigin(_upgradeShipRect.width / 2, _upgradeShipRect.height / 2);
	upgradeShipSprite->getSprite().setPosition(col * 2.5, row * 8);

	//Adding text components
	menuOption1 = upgradeView->addComponent<TextComponent>();
	menuOption2 = upgradeView->addComponent<TextComponent>();
	menuOption3 = upgradeView->addComponent<TextComponent>();
	menuOption4 = upgradeView->addComponent<TextComponent>();
	menuOption1Value = upgradeView->addComponent<TextComponent>();
	menuOption2Value = upgradeView->addComponent<TextComponent>();
	menuOption3Value = upgradeView->addComponent<TextComponent>();
	menuOption4Value = upgradeView->addComponent<TextComponent>();
	menuOption1NextValue = upgradeView->addComponent<TextComponent>();
	menuOption2NextValue = upgradeView->addComponent<TextComponent>();
	menuOption3NextValue = upgradeView->addComponent<TextComponent>();
	menuOption4NextValue = upgradeView->addComponent<TextComponent>();
	menuOption1Cost = upgradeView->addComponent<TextComponent>();
	menuOption2Cost = upgradeView->addComponent<TextComponent>();
	menuOption3Cost = upgradeView->addComponent<TextComponent>();
	menuOption4Cost = upgradeView->addComponent<TextComponent>();
	currentValueText = upgradeView->addComponent<TextComponent>();
	nextValueText = upgradeView->addComponent<TextComponent>();
	upgradeCostText = upgradeView->addComponent<TextComponent>();
	coinsTxtCMP = upgradeView->addComponent<TextComponent>();
	titleCMP = upgradeView->addComponent<TextComponent>();
	pressEnterText = upgradeView->addComponent<TextComponent>();
	noEnoughMoneyText = upgradeView->addComponent<TextComponent>();
	exitText = upgradeView->addComponent<TextComponent>();
	allTextCMP = upgradeView->GetCompatibleComponent<TextComponent>();

	//Setting up title scene
	titleCMP->setFontSize(70u);
	titleCMP->setText("- PERFECT JAZZ SHOP -");
	titleCMP->setOrigin(Vector2f((round)(titleCMP->getLocalBounds().left + titleCMP->_text.getLocalBounds().width / 2), (round)(titleCMP->getGlobalBounds().height / 2 - titleCMP->_text.getLocalBounds().height / 2)));
	titleCMP->setPosition(Vector2f(menuView.getSize().x / 2, row * 1));

	//Setting up coins text component
	coinsTxtCMP->setFontSize(50u);
	coinsTxtCMP->_text.setString("Coins: " + to_string(upgradedPlayerCMP->getShoppingCoins()));
	coinsTxtCMP->setOrigin(Vector2f((round)(coinsTxtCMP->getLocalBounds().left + coinsTxtCMP->getLocalBounds().width / 2), (round)(coinsTxtCMP->getLocalBounds().height / 2 - coinsTxtCMP->_text.getLocalBounds().height)));
	coinsTxtCMP->setPosition(Vector2f((round)(menuView.getSize().x / 2), row * 2.5));

	//Setting the exit text
	exitText->setFontSize(60u);
	exitText->_text.setString("LEAVE SHOP");
	exitText->setOrigin(Vector2f((round)(exitText->getLocalBounds().left + exitText->getLocalBounds().width / 2), (round)(exitText->getLocalBounds().height / 2 - exitText->_text.getLocalBounds().height)));
	exitText->setPosition(Vector2f((round)(menuView.getSize().x / 2), row * 16));

	//Settign rectangle for the coins sprite, rotation and scale
	_coinRect.left = (round)(_coinTex->getSize().x / 5 * 0);
	_coinRect.top = (round)(_coinTex->getSize().y / 2 * 0);
	_coinRect.width = (round)(_coinTex->getSize().x / 5);
	_coinRect.height = (round)(_coinTex->getSize().y / 1);
	for (int i = 1; i < allCoinsSprite.size(); i++) {
		allCoinsSprite[i]->setTexure(_coinTex);
		allCoinsSprite[i]->getSprite().setScale(Vector2f(1.5f, 1.5f) * windowScale);
		allCoinsSprite[i]->getSprite().setTextureRect(_coinRect);
		allCoinsSprite[i]->getSprite().setOrigin(Vector2f(_coinRect.width / 2, _coinRect.height / 2 - cointSprite->getSprite().getLocalBounds().height));
	}
	cointSprite->getSprite().setPosition(Vector2f(coinsTxtCMP->getPosition().x + coinsTxtCMP->_text.getLocalBounds().width / 2 + cointSprite->getSprite().getGlobalBounds().width, coinsTxtCMP->_text.getPosition().y + cointSprite->getSprite().getGlobalBounds().height / 2));

	//Adding initial texts for the menu into an array of strings
	s.clear();
	s.push_back("Bullet Damage");
	s.push_back("Fire Rate");
	s.push_back("Maximum HP");
	s.push_back("Ship Speed");
	changeMenuText(s);
	updatingCurrentValues();
	updatingNextValues();
	updatingCost();

	//Positioning value text components
	for (int i = 0; i < 4; i++) {
		allTextCMP[i + 4]->setFontSize(45u);
		allTextCMP[4]->_text.setColor(Color::Red);
		allTextCMP[i + 4]->setOrigin(Vector2f((round)(allTextCMP[i + 4]->getLocalBounds().width / 2), (round)(allTextCMP[i + 4]->getLocalBounds().top + allTextCMP[i + 4]->getLocalBounds().height / 2.f)));
		allTextCMP[i + 4]->setPosition(Vector2f(col * 9, (round)(menuView.getSize().y / 3) + (menuView.getSize().y / 14 * i)));
	}

	//Positioning upgraded value text components
	for (int i = 0; i < 4; i++) {
		allTextCMP[i + 8]->setFontSize(45u);
		allTextCMP[8]->_text.setColor(Color::Red);
		allTextCMP[i + 8]->setOrigin(Vector2f((round)(allTextCMP[i + 8]->getGlobalBounds().width / 2), (round)(allTextCMP[i + 8]->getGlobalBounds().top + allTextCMP[i + 8]->getGlobalBounds().height / 2.f)));
		allTextCMP[i + 8]->setPosition(Vector2f(col * 13, (round)(menuView.getSize().y / 3) + (menuView.getSize().y / 14 * i)));
	}

	//Positioning upgrades cost values
	for (int i = 0; i < 4; i++) {
		allTextCMP[i + 12]->setFontSize(45u);
		allTextCMP[12]->_text.setColor(Color::Red);
		allTextCMP[i + 12]->setOrigin(Vector2f((round)(allTextCMP[i + 12]->getGlobalBounds().width / 2), (round)(allTextCMP[i + 12]->getGlobalBounds().top + allTextCMP[i + 12]->getGlobalBounds().height / 2.f)));
		allTextCMP[i + 12]->setPosition(Vector2f(col * 17, (round)(menuView.getSize().y / 3) + (menuView.getSize().y / 14 * i)));
		allCoinsSprite[2 + i]->getSprite().setPosition(Vector2f(col * 17 + allTextCMP[i + 12]->_text.getLocalBounds().width, (round)(menuView.getSize().y / 3) + (menuView.getSize().y / 14 * i - allCoinsSprite[2 + i]->getSprite().getGlobalBounds().height)));
	}

	//Setting the no enough money text
	noEnoughMoneyText = upgradeView->addComponent<TextComponent>();
	noEnoughMoneyText->setFontSize(120u);
	noEnoughMoneyText->_text.setColor(Color::Red);
	noEnoughMoneyText->_text.setString("NOT ENOUGH COINS");
	noEnoughMoneyText->setOrigin(Vector2f((round)(noEnoughMoneyText->getLocalBounds().left + noEnoughMoneyText->getLocalBounds().width / 2), (round)(noEnoughMoneyText->getLocalBounds().top + noEnoughMoneyText->_text.getLocalBounds().height / 2)));
	noEnoughMoneyText->setPosition(Vector2f((round)(menuView.getSize().x / 2), (round)(menuOption1->getPosition().y + menuOption4->getPosition().y) / 2));
	noEnoughMoneyText->setVisible(false);

	//Setting header for current values, next values and cost
	currentValueText->setText("Current Value"); currentValueText->setFontSize(40u);
	nextValueText->setText("Upgraded Value"); nextValueText->setFontSize(40u);
	upgradeCostText->setText("Upgrade Cost"); upgradeCostText->setFontSize(40u);

	//Positioning the headers
	currentValueText->setOrigin(Vector2f((round)(currentValueText->getGlobalBounds().width / 2), (round)(currentValueText->getLocalBounds().height / 2.f)));
	currentValueText->setPosition(Vector2f(col * 9, row * 5));
	nextValueText->setOrigin(Vector2f((round)(nextValueText->getGlobalBounds().width / 2), (round)(currentValueText->getLocalBounds().height / 2.f)));
	nextValueText->setPosition(Vector2f(col * 13, row * 5));
	upgradeCostText->setOrigin(Vector2f((round)(upgradeCostText->getGlobalBounds().width / 2), (round)(currentValueText->getLocalBounds().height / 2.f)));
	upgradeCostText->setPosition(Vector2f(col * 17, row * 5));

	//Setting up press enter text
	pressEnterText->setFontSize(40u);
	pressEnterText->_text.setString("- PRESS ENTER TO BUY THE SELECTED UPGRADE -");
	pressEnterText->setOrigin(Vector2f((round)(pressEnterText->getLocalBounds().left + pressEnterText->getLocalBounds().width / 2), (round)(pressEnterText->getLocalBounds().height / 2 - pressEnterText->_text.getLocalBounds().height)));
	pressEnterText->setPosition(Vector2f((round)((currentValueText->getPosition().x + nextValueText->getPosition().x) / 2), row * 12));


	setLoaded(true);
}

//Iterates through thte string array and sets the settings of each of the text components
void UpgradeMenu::changeMenuText(std::vector<std::string> s) {
	for (int i = 0; i < s.size(); i++) {

		allTextCMP[i]->setFontSize(45u);
		allTextCMP[i]->_text.setString(s[i]);
		allTextCMP[i]->_text.setColor(Color::White);
		if (i == selectedIndex) { allTextCMP[i]->_text.setColor(Color::Red); }

		//Aligns text to the right
		sf::FloatRect textRect = allTextCMP[i]->getLocalBounds();
		allTextCMP[i]->setOrigin(Vector2f((round)(textRect.left + textRect.width), (round)(textRect.top + textRect.height / 2.f)));
		allTextCMP[i]->setPosition(Vector2f(col * 7, (round)(menuView.getSize().y / 3) + (menuView.getSize().y / 14 * i)));
	}
	alignSprite();
}

//Align sprites with the selected text
void UpgradeMenu::alignSprite() {
	_upgradeShipRect.left = (round)(_upgradeShipTex->getSize().x / 5 * (selectedIndex));
	upgradeShipSprite->getSprite().setTextureRect(_upgradeShipRect);
}

//Setting up values for the current values
void UpgradeMenu::updatingCurrentValues() {
	std::stringstream fireRate;
	fireRate << std::fixed << std::setprecision(2) << upgradedPlayerCMP->weaponCMP->_wSettings.fireTime;
	std::stringstream flySpeed;
	flySpeed << std::fixed << std::setprecision(2) << upgradedPlayerCMP->_playerSettings.flySpeed;

	menuOption1Value->setText(to_string(upgradedPlayerCMP->weaponCMP->_bSettings.damage));
	menuOption2Value->setText(fireRate.str());
	menuOption3Value->setText(to_string(upgradedPlayerCMP->hpCMP->getMaxHP()));
	menuOption4Value->setText(flySpeed.str());
}

//Setting up values for the upgraded values
void UpgradeMenu::updatingNextValues() {
	std::stringstream fireRateNext;
	fireRateNext << std::fixed << std::setprecision(2) << (upgradedPlayerCMP->weaponCMP->_wSettings.fireTime * fireRateMulti);
	std::stringstream flySpeedNext;
	flySpeedNext << std::fixed << std::setprecision(2) << (upgradedPlayerCMP->_playerSettings.flySpeed * flySpeedMulti);

	if (menuOption1NextValue->_text.getString() != "MAX") { menuOption1NextValue->setText(to_string((int)(upgradedPlayerCMP->weaponCMP->_bSettings.damage * damageMulti))); }
	if (menuOption2NextValue->_text.getString() != "MAX") { menuOption2NextValue->setText(fireRateNext.str()); }
	if (menuOption3NextValue->_text.getString() != "MAX") { menuOption3NextValue->setText(to_string((int)(upgradedPlayerCMP->hpCMP->getMaxHP() * maxHPMulti))); }
	if (menuOption4NextValue->_text.getString() != "MAX") { menuOption4NextValue->setText(flySpeedNext.str()); }
}

//Setting up values for the upgrades cost
void UpgradeMenu::updatingCost() {
	std::stringstream fireRateCost;
	fireRateCost << std::fixed << std::setprecision(0) << (300 / upgradedPlayerCMP->weaponCMP->_wSettings.fireTime);
	std::stringstream flySpeedCost;
	flySpeedCost << std::fixed << std::setprecision(0) << (upgradedPlayerCMP->_playerSettings.flySpeed * 5);

	if (menuOption1NextValue->_text.getString() != "MAX") { menuOption1Cost->setText(to_string((int)(upgradedPlayerCMP->weaponCMP->_bSettings.damage * 1.5))); }
	if (menuOption2NextValue->_text.getString() != "MAX") { menuOption2Cost->setText(fireRateCost.str()); }
	if (menuOption3NextValue->_text.getString() != "MAX") { menuOption3Cost->setText(to_string((int)(upgradedPlayerCMP->hpCMP->getMaxHP() * 0.2))); }
	if (menuOption4NextValue->_text.getString() != "MAX") { menuOption4Cost->setText(flySpeedCost.str()); }
}

void UpgradeMenu::centeringText() {

	//Recentering text
	for (int i = 0; i < 4; i++) {
		allTextCMP[i + 4]->setOrigin(Vector2f((round)(allTextCMP[i + 4]->getLocalBounds().width / 2), (round)(allTextCMP[i + 4]->getLocalBounds().top + allTextCMP[i + 4]->getLocalBounds().height / 2.f)));
		allTextCMP[i + 4]->setPosition(Vector2f(col * 9, (round)(menuView.getSize().y / 3) + (menuView.getSize().y / 14 * i)));
	}
	for (int i = 0; i < 4; i++) {
		allTextCMP[i + 8]->setOrigin(Vector2f((round)(allTextCMP[i + 8]->getLocalBounds().width / 2), (round)(allTextCMP[i + 8]->getLocalBounds().top + allTextCMP[i + 8]->getLocalBounds().height / 2.f)));
		allTextCMP[i + 8]->setPosition(Vector2f(col * 13, (round)(menuView.getSize().y / 3) + (menuView.getSize().y / 14 * i)));
	}
	for (int i = 0; i < 4; i++) {
		allTextCMP[i + 12]->setOrigin(Vector2f((round)(allTextCMP[i + 12]->getLocalBounds().width / 2), (round)(allTextCMP[i + 12]->getLocalBounds().top + allTextCMP[i + 12]->getLocalBounds().height / 2.f)));
		allTextCMP[i + 12]->setPosition(Vector2f(col * 17, (round)(menuView.getSize().y / 3) + (menuView.getSize().y / 14 * i)));
	}
	for (int i = 0; i < 4; i++) {
		allCoinsSprite[2 + i]->getSprite().setPosition(Vector2f(col * 17 + allTextCMP[i + 12]->_text.getLocalBounds().width, (round)(menuView.getSize().y / 3) + (menuView.getSize().y / 14 * i - allCoinsSprite[2 + i]->getSprite().getGlobalBounds().height)));
	}
}

//Updates the values after an upgrade
void UpgradeMenu::purchasingUpgrade(int type) {

	upgradeCost = allTextCMP[12 + type]->_text.getString();

	//Check if enough coins to do the purchase
	if (upgradeCost != "MAX" && upgradedPlayerCMP->_playerSettings.shopPoints < std::stoi(upgradeCost)) {
		noEnoughMoneyText->setVisible(true);
		notEnoughTimer = 0;
	}
	//Update the values in the player settings
	else if (upgradeCost != "MAX" && upgradedPlayerCMP->_playerSettings.shopPoints >= std::stoi(upgradeCost)) {
		if (type == 0) {
			if (upgradedPlayerCMP->weaponCMP->_bSettings.damage >= maxBulletDamage) {
				menuOption1NextValue->setText("MAX");
				menuOption1Cost->setText("MAX");
			}
			else { upgradedPlayerCMP->weaponCMP->_bSettings.damage = upgradedPlayerCMP->weaponCMP->_bSettings.damage * damageMulti; }
		}
		if (type == 1) {
			if (upgradedPlayerCMP->weaponCMP->_wSettings.fireTime <= maxFireRate) {
				menuOption2NextValue->setText("MAX");
				menuOption2Cost->setText("MAX");
			}
			else { upgradedPlayerCMP->weaponCMP->_wSettings.fireTime = upgradedPlayerCMP->weaponCMP->_wSettings.fireTime * fireRateMulti; }
		}
		if (type == 2) {
			if (upgradedPlayerCMP->hpCMP->getMaxHP() >= maxHPUpgrade) {
				menuOption3NextValue->setText("MAX");
				menuOption3Cost->setText("MAX");
			}
			else { 
				upgradedPlayerCMP->hpCMP->setMaxHP(upgradedPlayerCMP->hpCMP->getMaxHP() * maxHPMulti); 
				upgradedPlayerCMP->_playerSettings.maxHP = upgradedPlayerCMP->hpCMP->getMaxHP();
			}
		}
		if (type == 3) {
			if (upgradedPlayerCMP->_playerSettings.flySpeed >= maxFlySpeed) {
				menuOption4NextValue->setText("MAX");
				menuOption4Cost->setText("MAX");
			}
			else { upgradedPlayerCMP->_playerSettings.flySpeed = upgradedPlayerCMP->_playerSettings.flySpeed * flySpeedMulti; }
		}

		upgradedPlayerCMP->_playerSettings.shopPoints -= std::stoi(upgradeCost);
		coinsTxtCMP->_text.setString("Coins: " + to_string(upgradedPlayerCMP->getShoppingCoins()));
		updatingCurrentValues();
		updatingNextValues();
		updatingCost();
		centeringText();
	}
}

//Moves up the selection and changes the colour of the text to red while selected, and while while not
void UpgradeMenu::moveUp() {

	if (selectedIndex - 1 >= 0) {
		allTextCMP[selectedIndex]->_text.setColor(Color::White);
		allTextCMP[selectedIndex + 4]->_text.setColor(Color::White);
		allTextCMP[selectedIndex + 8]->_text.setColor(Color::White);
		allTextCMP[selectedIndex + 12]->_text.setColor(Color::White);
		exitText->_text.setColor(Color::White);
		selectedIndex--;
		allTextCMP[selectedIndex]->_text.setColor(Color::Red);
		allTextCMP[selectedIndex + 4]->_text.setColor(Color::Red);
		allTextCMP[selectedIndex + 8]->_text.setColor(Color::Red);
		allTextCMP[selectedIndex + 12]->_text.setColor(Color::Red);
		alignSprite();
	}
}

//Moves down the selection and changes the colour of the text to red while selected, and while while not
void UpgradeMenu::moveDown() {

	if (selectedIndex + 1 < s.size()) {
		allTextCMP[selectedIndex]->_text.setColor(Color::White);
		allTextCMP[selectedIndex + 4]->_text.setColor(Color::White);
		allTextCMP[selectedIndex + 8]->_text.setColor(Color::White);
		allTextCMP[selectedIndex + 12]->_text.setColor(Color::White);
		selectedIndex++;
		allTextCMP[selectedIndex]->_text.setColor(Color::Red);
		allTextCMP[selectedIndex + 4]->_text.setColor(Color::Red);
		allTextCMP[selectedIndex + 8]->_text.setColor(Color::Red);
		allTextCMP[selectedIndex + 12]->_text.setColor(Color::Red);
		alignSprite();
	}

	else if (selectedIndex + 1 == s.size()) {
		allTextCMP[selectedIndex]->_text.setColor(Color::White);
		allTextCMP[selectedIndex + 4]->_text.setColor(Color::White);
		allTextCMP[selectedIndex + 8]->_text.setColor(Color::White);
		allTextCMP[selectedIndex + 12]->_text.setColor(Color::White);
		exitText->_text.setColor(Color::Red);
		selectedIndex++;
		alignSprite();
	}
}

void UpgradeMenu::Update(const double& dt) {
	//Performs the coin animation
	{
		timer += dt;

		if (timer < 0.1) { _coinRect.left = (_coinTex->getSize().x / 5) * 0; }
		if (timer >= 0.1 && timer < 0.2) { _coinRect.left = (_coinTex->getSize().x / 5) * 1; }
		if (timer >= 0.2 && timer < 0.3) { _coinRect.left = (_coinTex->getSize().x / 5) * 2; }
		if (timer >= 0.3 && timer < 0.4) { _coinRect.left = (_coinTex->getSize().x / 5) * 3; }
		if (timer >= 0.4 && timer < 0.5) { _coinRect.left = (_coinTex->getSize().x / 5) * 4; }
		if (timer >= 0.5) { timer = 0.0; }

		for (int i = 1; i < allCoinsSprite.size(); i++) {
			allCoinsSprite[i]->getSprite().setTextureRect(_coinRect);
		}
	}

	//Sets press enter text to visible or non visible over time
	pressTextTimer += dt;
	if (pressTextTimer <= 1.5f) { pressEnterText->setVisible(true); }
	if (pressTextTimer > 1.5f && timer <= 2.f) { pressEnterText->setVisible(false); }
	if (pressTextTimer > 2.f) { pressTextTimer = 0; }

	notEnoughTimer += dt;
	//Checks for key pressed to go up or down the menu
	if (sf::Keyboard::isKeyPressed(Keyboard::Up) && !detectingKeys.keyUp) { moveUp(); }
	if (sf::Keyboard::isKeyPressed(Keyboard::Down) && !detectingKeys.keyDown) { moveDown(); }
	//Switches between 4 cases, depending on which element of the menu has been selected
	if (sf::Keyboard::isKeyPressed(Keyboard::Enter) /*&& !detectingKeys.keyEnter*/) {
		switch (selectedIndex) {
		case 0:
			purchasingUpgrade(0);
			break;
		case 1:
			purchasingUpgrade(1);
			break;
		case 2:
			purchasingUpgrade(2);
			break;
		case 3:
			purchasingUpgrade(3);
			break;
		case 4:
			Engine::isGamePaused = false;
			Engine::isMenu = false;
			Engine::isPausedMenu = true;
			musicArray[MUSIC_UPGRADE_MENU].pause();
			musicArray[currentLvlMusicIndex].play();
			selectedIndex = 1;
			moveUp();
			if (Engine::isLevelComplete) {
				Engine::isPausedMenu = false;
				PlayerComponent::clonePlayer(player);
				Engine::_lastScene->UnLoad();
				Engine::ChangeScene(Engine::_nextScene);
				break;					
			}
			Engine::ChangeScene(Engine::_lastScene);
			break;
		default:
			break;
		}
	}

	detectingKeys.detectingKeys();

	if (notEnoughTimer > 2) {
		noEnoughMoneyText->setVisible(false);
		notEnoughTimer = 0;
	}
}

void UpgradeMenu::UnLoad() {
	upgradedPlayerCMP.reset();
	upgradeShipSprite.reset();
	cointSprite.reset();
	cointSprite2.reset();
	cointSprite3.reset();
	cointSprite4.reset();
	cointSprite5.reset();
	allCoinsSprite.clear();
	upgradeView->setForDelete();

	setLoaded(false);
}