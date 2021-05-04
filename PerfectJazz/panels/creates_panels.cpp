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
shared_ptr<TextComponent> currentModeCMP;
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

//Creates the panels with the components
void Panels::createPanels(Scene* _scene) {

	//Gets player component from the player
	playerCMP = player->GetCompatibleComponent<PlayerComponent>()[0];
	//Left Panel
	{	//Sets up initial values
		currentScore = -1;
		currentHP = -1;
		currentCoins = -1;
		currentLifes = -1;
		currentBulletSpread = -1;
		currentBulletDamage = -1;
		currentFirerate = -1;
		currentFlySpeed = -1;

		//Creates the lefpanel scene and assigning a view
		leftPanel = _scene->makeEntity();
		leftPanel->setView(leftView);

		//Adds components
		playerLifeSpriteCMP = leftPanel->addComponent<SpriteComponent>();
		hpCMP = leftPanel->addComponent<HPComponent>(_scene, playerCMP->_playerSettings.hp, playerCMP->_playerSettings.maxHP);
		hpCMP->loadHP();
		playerTxtCMP = leftPanel->addComponent<TextComponent>("PLAYER 1");
		scoreTxtCMP = leftPanel->addComponent<TextComponent>("SCORE: " + to_string(playerCMP->_playerSettings.score));
		coinsTxtCMP = leftPanel->addComponent<TextComponent>("COINS: " + to_string(playerCMP->_playerSettings.shopPoints));
		playerSpeedTxtCMP = leftPanel->addComponent<TextComponent>("SHIP SPEED: ");
		playerBulletPowerTxtCMP = leftPanel->addComponent<TextComponent>("DAMAGE: ");
		playerFireRateTxtCMP = leftPanel->addComponent<TextComponent>("FIRE RATE: ");
		playerBulletNumberTxtCMP = leftPanel->addComponent<TextComponent>("SPREAD: ");

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
		playerSpeedTxtCMP->setFontSize(32u);
		auto pstRect = playerSpeedTxtCMP->getGlobalBounds();
		playerSpeedTxtCMP->setPosition(Vector2f((round)(col * 6 + pstRect.left - pstRect.width), (round)(row * 10)));

		//Bullets PowerUps
		playerBulletPowerTxtCMP->setFontSize(32u);
		auto pbpRec = playerBulletPowerTxtCMP->getGlobalBounds();
		playerBulletPowerTxtCMP->setPosition(Vector2f((round)(col * 6 + pbpRec.left - pbpRec.width), (round)(row * 11)));

		//Fire rate PowerUps
		playerFireRateTxtCMP->setFontSize(32u);
		auto pfRect = playerFireRateTxtCMP->getGlobalBounds();
		playerFireRateTxtCMP->setPosition(Vector2f((round)(col * 6 + pfRect.left - pfRect.width), (round)(row * 12)));

		//Bullet number PowerUp
		playerBulletNumberTxtCMP->setFontSize(32u);
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
		hpCMP->textCMP->setFontSize(38u);
		hpCMP->setScale(Vector2f(4.f, 3.f));
		hpCMP->textCMP->setOrigin(Vector2f((round)(hpCMP->textCMP->getGlobalBounds().width / 2), (round)(hpCMP->textCMP->getGlobalBounds().height / 2)));
		hpCMP->textCMP->setPosition(Vector2f((round)(leftView.getSize().x/2), (round)(hpCMP->overHPBar->getSprite().getPosition().y - hpCMP->textCMP->getGlobalBounds().height/2 - hpCMP->textCMP->getGlobalBounds().top)));
	}

	//Right Panel
	{
		//Creates entity and setting view
		rightPanel = _scene->makeEntity();
		rightPanel->setView(rightView);
		//Creates fps textcomponent and initializing its settings
		FPStxtCMP = rightPanel->addComponent<TextComponent>("FPS: " + toStrDecPt(2, Engine::FPS));		
		FPStxtCMP->setFontSize(40u);
		sf::FloatRect textRect = FPStxtCMP->getLocalBounds();
		FPStxtCMP->setOrigin(Vector2f((round)(textRect.left + textRect.width / 2), (round)(textRect.top + textRect.height / 2)));
		FPStxtCMP->setPosition(Vector2f((round)(rightView.getSize().x / 2), (round)(row * 3)));
		//Creates current mode textcomponent and initializing its settings
		currentModeCMP = rightPanel->addComponent<TextComponent>("CURRENT LEVEL: " + to_string(Engine::currentPlayerLevel + 1));
		currentModeCMP->setFontSize(38u);
		sf::FloatRect currentModeRect = currentModeCMP->getLocalBounds();
		currentModeCMP->setOrigin(Vector2f((round)(currentModeRect.left + currentModeRect.width / 2), (round)(currentModeRect.top + currentModeRect.height / 2)));
		currentModeCMP->setPosition(Vector2f((round)(rightView.getSize().x / 2), (round)(row * 1)));
	}

}

//Sets life sprites according to the current lifes
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

//Creates the sprites for the upgrades, assigning one to each of the different upgrades in each iteration
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

//Sets the upgrade sprites to it's value. Parameter type is the type of ugprade and counter the ammount.
void Panels::setUpgradesSprites(string type, int counter) {

	//Depending on the counter, the rectangle will display the right sprite from the sprite sheet
	upgradeCounterRec.left = (round)(upgradeCounterTexture.getSize().x * 0);
	upgradeCounterRec.top = (round)(upgradeCounterTexture.getSize().y * 0);
	upgradeCounterRec.width = (round)((upgradeCounterTexture.getSize().x / 5) * counter);
	upgradeCounterRec.height = (round)(upgradeCounterTexture.getSize().y);

	//Sets sprite for damage upgrade
	if (type == "damage") {
		currentBulletDamage = counter;
		upgradeDamageSpriteCMP->getSprite().setTextureRect(upgradeCounterRec);
	};
	//Sets sprite for fly speed upgrade
	if (type == "flySpeed") {
		currentFlySpeed = counter;
		upgradeFlyeSpeedSpriteCMP->getSprite().setTextureRect(upgradeCounterRec);
	};
	//Sets sprite for fire rate upgrade
	if (type == "firerate") {
		currentFirerate = counter;
		upgradeFirerateSpriteCMP->getSprite().setTextureRect(upgradeCounterRec);
	};
	//Sets sprite for bullets upgrade
	if (type == "bullets") {
		currentBulletSpread = counter;
		upgradeBulletsSpriteCMP->getSprite().setTextureRect(upgradeCounterRec);
	};
	//Sets sprite for score upgrade
	if (type == "score") {
		currentScore = counter;
		scoreTxtCMP->setText("SCORE: " + to_string(playerCMP->_playerSettings.score));
	};
	//Sets sprite for coin upgrade
	if (type == "coin") {
		currentCoins = counter;
		coinsTxtCMP->setText("COINS: " + to_string(playerCMP->_playerSettings.shopPoints));
	};	
	//Sets sprite for hp upgrade and updates both current hp and current max hp
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

//Updates the panel
void Panels::update(double dt) {
	timer += dt;

	//If timer bigger than 0.1 and player not null, checks for changes on each of the upgrades
	if (timer > 0.1 && playerCMP != nullptr) {

		//Checks for changes on life
		if (currentLifes != playerCMP->_playerSettings.lifes) { setLifeSprites(); }
		//Checks for changes on life
		if (currentBulletDamage != playerCMP->weaponCMP->_bSettings.damageUpgradeCount) {
			setUpgradesSprites("damage", playerCMP->weaponCMP->_bSettings.damageUpgradeCount);
		}
		//Checks for changes on fly speed
		if (currentFlySpeed != playerCMP->_playerSettings.flySpeedUpgradeCount) {
			setUpgradesSprites("flySpeed", playerCMP->_playerSettings.flySpeedUpgradeCount);
		}
		//Checks for changes on fire rate
		if (currentFirerate != playerCMP->weaponCMP->_wSettings.firerateUpgradeCount) {
			setUpgradesSprites("firerate", playerCMP->weaponCMP->_wSettings.firerateUpgradeCount);
		}
		//Checks for changes on bullets
		if (currentBulletSpread != playerCMP->weaponCMP->_wSettings.numBulletsUpgradeCount) {
			setUpgradesSprites("bullets", playerCMP->weaponCMP->_wSettings.numBulletsUpgradeCount);
		}
		//Checks for changes on score
		if (currentScore != playerCMP->_playerSettings.score) {
			setUpgradesSprites("score", playerCMP->_playerSettings.score);
		}
		//Checks for changes on coins
		if (currentCoins != playerCMP->_playerSettings.shopPoints) {
			setUpgradesSprites("coin", playerCMP->_playerSettings.shopPoints);
		}
		//Checks for changes on health
		if (currentHP != playerCMP->hpCMP->getHP() || currentMaxHP != playerCMP->hpCMP->getMaxHP()) {
			setUpgradesSprites("hp", playerCMP->hpCMP->getHP());
		}
		//Sets timer to 0
		timer = 0;
		//Updates the FPS text
		FPStxtCMP->setText("FPS: " + toStrDecPt(2, Engine::FPS));


		if (Engine::currentPlayerLevel >= 0) {
			currentModeCMP->setText("CURRENT LEVEL: " + to_string(Engine::currentPlayerLevel + 1));
			sf::FloatRect currentModeRect = currentModeCMP->getLocalBounds();
			currentModeCMP->setOrigin(Vector2f((round)(currentModeRect.left + currentModeRect.width / 2), (round)(currentModeRect.top + currentModeRect.height / 2)));
		}
		if (Engine::currentPlayerLevel < 0) {
			currentModeCMP->setText("INFINITE MODE");
			sf::FloatRect currentModeRect = currentModeCMP->getLocalBounds();
			currentModeCMP->setOrigin(Vector2f((round)(currentModeRect.left + currentModeRect.width / 2), (round)(currentModeRect.top + currentModeRect.height / 2)));
		}
	}	
}

//Renders all the components

void Panels::render() {}

//Panels destructor
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
	currentModeCMP.reset();
	playerFireRateTxtCMP.reset();
	playerBulletNumberTxtCMP.reset();
	hpCMP.reset();
	playerCMP.reset();
}