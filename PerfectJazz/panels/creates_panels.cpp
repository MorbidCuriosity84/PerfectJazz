#include "creates_panels.h"
#include "../player/cmp_player.h"
#include "../components/cmp_text.h"
#include "../components/cmp_hp.h"
#include "../components/cmp_sprite.h"
#include "../settings/texture_helper_settings.h"
#include <engine.h>
#include <math.h>


using namespace std;
using namespace sf;

shared_ptr<Entity> leftPanel;
shared_ptr<Entity> rightPanel;
shared_ptr<SpriteComponent> playerLifeSpriteCMP;
shared_ptr<SpriteComponent> upgradeDamageSpriteCMP;
shared_ptr<SpriteComponent> upgradeFlyeSpeedSpriteCMP;
shared_ptr<SpriteComponent> upgradeFirerateSpriteCMP;
shared_ptr<SpriteComponent> upgradeBulletsSpriteCMP;
shared_ptr<PlayerComponent> playerCMP;
shared_ptr<TextComponent> playerTxtCMP;
shared_ptr<TextComponent> scoreTxtCMP;
shared_ptr<TextComponent> coinsTxtCMP;
shared_ptr<TextComponent> playerSpeedTxtCMP;
shared_ptr<TextComponent> playerBulletPowerTxtCMP;
shared_ptr<TextComponent> playerFireRateTxtCMP;
shared_ptr<TextComponent> playerBulletNumberTxtCMP;
shared_ptr<TextComponent> FPStxtCMP;
shared_ptr<HPComponent> hpCMP;
textureSettings playerLifeTextureHelper;
Texture playerLifeTexture;
sf::IntRect playerLifeRec;
Texture upgradeCounterTexture;
sf::IntRect upgradeCounterRec;
int currentLifes;
int currentBulletSpread;
int currentBulletDamage;
int currentFirerate;
int currentFlySpeed;
int currentScore;
int currentCoins;
int currentHP;
int currentMaxHP;
double timer;
int row;
int col;

void Panels::createPanels(Scene* _scene) {

	playerCMP = player->GetCompatibleComponent<PlayerComponent>()[0];
	//Left Panel
	{	//Setting up initial values
		currentScore = -1;
		currentHP = -1;
		currentCoins = -1;
		currentLifes = -1;
		currentBulletSpread = -1;
		currentBulletDamage = -1;
		currentFirerate = -1;
		currentFlySpeed = -1;

		leftPanel = _scene->makeEntity();
		leftPanel->setView(leftView);

		//Adding components
		playerLifeSpriteCMP = leftPanel->addComponent<SpriteComponent>();
		hpCMP = leftPanel->addComponent<HPComponent>(_scene, playerCMP->_playerSettings.hp, playerCMP->_playerSettings.maxHP);
		hpCMP->loadHP();
		playerTxtCMP = leftPanel->addComponent<TextComponent>("PLAYER 1");
		scoreTxtCMP = leftPanel->addComponent<TextComponent>("Score: " + to_string(playerCMP->_playerSettings.score));
		coinsTxtCMP = leftPanel->addComponent<TextComponent>("Coins: " + to_string(playerCMP->_playerSettings.shopPoints));
		playerSpeedTxtCMP = leftPanel->addComponent<TextComponent>("Ship Speed: ");
		playerBulletPowerTxtCMP = leftPanel->addComponent<TextComponent>("Damage: ");
		playerFireRateTxtCMP = leftPanel->addComponent<TextComponent>("Fire rate: ");
		playerBulletNumberTxtCMP = leftPanel->addComponent<TextComponent>("Spread: ");

		//Player name
		row = (round)(leftView.getSize().y / 30);
		col = (round)(leftView.getSize().x / 10);
		playerTxtCMP->setFontSize(54u);
		sf::FloatRect textRect = playerTxtCMP->getLocalBounds();
		playerTxtCMP->setOrigin(Vector2f((round)(textRect.left + textRect.width / 2), (round)(textRect.top + textRect.height / 2)));
		playerTxtCMP->setPosition(Vector2f((round)(leftView.getSize().x / 2), (round)(row * 2.4)));

		//Player life icons
		playerLifeTexture.loadFromFile("res/img/others/player_life.png");
		playerLifeSpriteCMP->isFollowingParent(false);
		playerLifeSpriteCMP->getSprite().setTexture(playerLifeTexture);
		playerLifeSpriteCMP->getSprite().setColor(Color::Red);
		playerLifeSpriteCMP->getSprite().setPosition(Vector2f(col * 2, row * 0.5));
		playerLifeSpriteCMP->getSprite().setScale(windowScale);
		setLifeSprites();

		//Upgrades icons
		upgradeCounterTexture.loadFromFile("res/img/others/upgrade_counter.png");
		createUpgradeSprites();

		//Player score
		scoreTxtCMP->setPosition(Vector2f(col * 1, row * 4));
		scoreTxtCMP->setFontSize(40u);

		//Player coins
		coinsTxtCMP->setPosition(Vector2f(col * 1, row * 5));
		coinsTxtCMP->setFontSize(40u);

		//Player PowerUps
		playerSpeedTxtCMP->setFontSize(30u);
		auto pstRect = playerSpeedTxtCMP->getGlobalBounds();
		playerSpeedTxtCMP->setPosition(Vector2f((round)(col * 6 + pstRect.left - pstRect.width), (round)(row * 10)));

		//Bullets PowerUps
		playerBulletPowerTxtCMP->setFontSize(30u);
		auto pbpRec = playerBulletPowerTxtCMP->getGlobalBounds();
		playerBulletPowerTxtCMP->setPosition(Vector2f((round)(col * 6 + pbpRec.left - pbpRec.width), (round)(row * 11)));

		//Fire rate PowerUps
		playerFireRateTxtCMP->setFontSize(30u);
		auto pfRect = playerFireRateTxtCMP->getGlobalBounds();
		playerFireRateTxtCMP->setPosition(Vector2f((round)(col * 6 + pfRect.left - pfRect.width), (round)(row * 12)));

		//Bullet number PowerUp
		playerBulletNumberTxtCMP->setFontSize(30u);
		auto pbnRect = playerBulletNumberTxtCMP->getGlobalBounds();
		playerBulletNumberTxtCMP->setPosition(Vector2f((round)(col * 6) + pbnRect.left - pbnRect.width, (round)(row * 13)));

		//Player HP
		hpCMP->underHPBar->isFollowingParent(false);
		hpCMP->overHPBar->isFollowingParent(false);
		hpCMP->underHPBar->getSprite().setColor(Color::White);
		hpCMP->overHPBar->getSprite().setColor(Color(205, 0, 0));
		hpCMP->setDynamic(false);
		auto hpRect = hpCMP->underHPBar->getSprite().getGlobalBounds();
		auto hpPos = hpCMP->underHPBar->getSprite().getPosition();
		hpCMP->underHPBar->getSprite().setPosition(Vector2f((round)(leftView.getSize().x/2), row * 4));
		hpCMP->overHPBar->getSprite().setPosition(Vector2f((round)(leftView.getSize().x / 2), row * 4));
		hpCMP->textCMP->setText(to_string(playerCMP->_playerSettings.hp) + "/" + to_string(playerCMP->_playerSettings.maxHP));
		hpCMP->textCMP->setFontSize(34u);
		hpCMP->setScale(Vector2f(4.f, 3.f));
		hpCMP->textCMP->setOrigin(Vector2f((round)(hpCMP->textCMP->getGlobalBounds().width / 2), (round)(hpCMP->textCMP->getGlobalBounds().height / 2)));
		hpCMP->textCMP->setPosition(Vector2f((round)(leftView.getSize().x/2), (round)(hpCMP->overHPBar->getSprite().getPosition().y - hpCMP->textCMP->getGlobalBounds().height/2 - hpCMP->textCMP->getGlobalBounds().top)));
	}

	//Right Panel
	{
		//Creating entity and setting view
		rightPanel = _scene->makeEntity();
		rightPanel->setView(rightView);
		//Creating fps textcomponent and initializing its settings
		FPStxtCMP = rightPanel->addComponent<TextComponent>("FPS: " + toStrDecPt(2, Engine::FPS));		
		FPStxtCMP->setFontSize(40u);
		sf::FloatRect textRect = FPStxtCMP->getLocalBounds();
		FPStxtCMP->setOrigin(Vector2f((round)(textRect.left + textRect.width / 2), (round)(textRect.top + textRect.height / 2)));
		FPStxtCMP->setPosition(Vector2f((round)(rightView.getSize().x / 2), (round)(row * 2.4)));
	}
}

void Panels::setLifeSprites() {

	auto lifes = playerCMP->getPlayerLifes();

	if (lifes > 0) {
		playerLifeRec.left = (round)(playerLifeTexture.getSize().x * 0);
		playerLifeRec.top = (round)(playerLifeTexture.getSize().y * 0);
		playerLifeRec.width = (round)(playerLifeTexture.getSize().x / 5 * lifes);
		playerLifeRec.height = (round)(playerLifeTexture.getSize().y);
		playerLifeSpriteCMP->getSprite().setTextureRect(playerLifeRec);
	}

	currentLifes = lifes;
}

void Panels::createUpgradeSprites() {
	for (int i = 1; i < 5; i++) {
		upgradeBulletsSpriteCMP = leftPanel->addComponent<SpriteComponent>();
		upgradeBulletsSpriteCMP->isFollowingParent(false);
		upgradeBulletsSpriteCMP->getSprite().setTexture(upgradeCounterTexture);
		upgradeBulletsSpriteCMP->getSprite().setColor(Color::Red);
		upgradeBulletsSpriteCMP->getSprite().setScale(windowScale);

		upgradeBulletsSpriteCMP->getSprite().setPosition(Vector2f((round)(col * 5.5), (round)(row * (10 + i)) - (round)(upgradeBulletsSpriteCMP->getSprite().getGlobalBounds().height / 2)));
		upgradeBulletsSpriteCMP->getSprite().setTextureRect(upgradeCounterRec);

		if (i == 1) { upgradeFlyeSpeedSpriteCMP = upgradeBulletsSpriteCMP; };
		if (i == 2) { upgradeDamageSpriteCMP = upgradeBulletsSpriteCMP; };
		if (i == 3) { upgradeFirerateSpriteCMP = upgradeBulletsSpriteCMP; };
	}
}

void Panels::setUpgradesSprites(string type, int counter) {

	upgradeCounterRec.left = (round)(upgradeCounterTexture.getSize().x * 0);
	upgradeCounterRec.top = (round)(upgradeCounterTexture.getSize().y * 0);
	upgradeCounterRec.width = (round)((upgradeCounterTexture.getSize().x / 5) * counter);
	upgradeCounterRec.height = (round)(upgradeCounterTexture.getSize().y);

	if (type == "damage") {
		currentBulletDamage = counter;
		upgradeDamageSpriteCMP->getSprite().setTextureRect(upgradeCounterRec);
	};
	if (type == "flySpeed") {
		currentFlySpeed = counter;
		upgradeFlyeSpeedSpriteCMP->getSprite().setTextureRect(upgradeCounterRec);
	};
	if (type == "firerate") {
		currentFirerate = counter;
		upgradeFirerateSpriteCMP->getSprite().setTextureRect(upgradeCounterRec);
	};
	if (type == "bullets") {
		currentBulletSpread = counter;
		upgradeBulletsSpriteCMP->getSprite().setTextureRect(upgradeCounterRec);
	};
	if (type == "score") {
		currentScore = counter;
		scoreTxtCMP->setText("Score: " + to_string(playerCMP->_playerSettings.score));
	};
	if (type == "coin") {
		currentCoins = counter;
		coinsTxtCMP->setText("Coins: " + to_string(playerCMP->_playerSettings.shopPoints));
	};	
	if (type == "hp") {
		currentHP = playerCMP->hpCMP->getHP();
		hpCMP->setHP(playerCMP->hpCMP->getHP());
		currentMaxHP = playerCMP->hpCMP->getMaxHP();
		hpCMP->setMaxHP(playerCMP->hpCMP->getMaxHP());
		hpCMP->textCMP->setText(to_string(playerCMP->hpCMP->getHP()) + "/" + to_string(playerCMP->hpCMP->getMaxHP()));
		hpCMP->textCMP->setOrigin(Vector2f((round)(hpCMP->textCMP->getGlobalBounds().width / 2), (round)(hpCMP->textCMP->getGlobalBounds().height / 2)));
		hpCMP->textCMP->setPosition(Vector2f((round)(leftView.getSize().x / 2), (round)(hpCMP->textCMP->getPosition().y)));
	};
}


void Panels::update(double dt) {
	timer += dt;

	if (timer > 0.1 && playerCMP != nullptr) {

		if (currentLifes != playerCMP->_playerSettings.lifes) { setLifeSprites(); }

		if (currentBulletDamage != playerCMP->weaponCMP->_bSettings.damageUpgradeCount) {
			setUpgradesSprites("damage", playerCMP->weaponCMP->_bSettings.damageUpgradeCount);
		}
		if (currentFlySpeed != playerCMP->_playerSettings.flySpeedUpgradeCount) {
			setUpgradesSprites("flySpeed", playerCMP->_playerSettings.flySpeedUpgradeCount);
		}
		if (currentFirerate != playerCMP->weaponCMP->_wSettings.firerateUpgradeCount) {
			setUpgradesSprites("firerate", playerCMP->weaponCMP->_wSettings.firerateUpgradeCount);
		}
		if (currentBulletSpread != playerCMP->weaponCMP->_wSettings.numBulletsUpgradeCount) {
			setUpgradesSprites("bullets", playerCMP->weaponCMP->_wSettings.numBulletsUpgradeCount);
		}
		if (currentScore != playerCMP->_playerSettings.score) {
			setUpgradesSprites("score", playerCMP->_playerSettings.score);
		}
		if (currentCoins != playerCMP->_playerSettings.shopPoints) {
			setUpgradesSprites("coin", playerCMP->_playerSettings.shopPoints);
		}
		if (currentHP != playerCMP->hpCMP->getHP() || currentMaxHP != playerCMP->hpCMP->getMaxHP()) {
			setUpgradesSprites("hp", playerCMP->hpCMP->getHP());
		}
		timer = 0;
		FPStxtCMP->setText("FPS: " + toStrDecPt(2, Engine::FPS));
	}	
}

void Panels::render() {}

Panels::~Panels() { 
	playerLifeSpriteCMP.reset();
	upgradeDamageSpriteCMP.reset();
	upgradeFlyeSpeedSpriteCMP.reset();
	upgradeFirerateSpriteCMP.reset();
	upgradeBulletsSpriteCMP.reset();
	playerTxtCMP.reset();
	scoreTxtCMP.reset();
	coinsTxtCMP.reset();
	FPStxtCMP.reset();
	playerSpeedTxtCMP.reset();
	playerBulletPowerTxtCMP.reset();
	playerFireRateTxtCMP.reset();
	playerBulletNumberTxtCMP.reset();
	hpCMP.reset();
	playerCMP.reset();
}