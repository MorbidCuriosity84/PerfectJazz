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
shared_ptr<SpriteComponent> playerLifeSpriteCMP;
shared_ptr<SpriteComponent> upgradeDamageSpriteCMP;
shared_ptr<SpriteComponent> upgradeFlyeSpeedSpriteCMP;
shared_ptr<SpriteComponent> upgradeFirerateSpriteCMP;
shared_ptr<SpriteComponent> upgradeBulletsSpriteCMP;
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
Texture upgradeCounterTexture;
sf::IntRect upgradeCounterRec;
int currentLifes;
int currentBulletSpread;
int currentBulletDamage;
int currentFirerate;
int currentFlySpeed;
int row;
int col;


void Panels::createPanels(Scene* _scene) {

	auto playerCMP = player->GetCompatibleComponent<PlayerComponent>()[0];
	//Left Panel
	{
		leftPanel = _scene->makeEntity();
		leftPanel->setView(leftView);

		//Adding components
		playerLifeSpriteCMP = leftPanel->addComponent<SpriteComponent>();
		hpCMP = leftPanel->addComponent<HPComponent>(_scene, playerCMP->_playerSettings.maxHP);
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
		playerTxtCMP->setFontSize(50u);
		sf::FloatRect textRect = playerTxtCMP->getLocalBounds();
		playerTxtCMP->setOrigin(Vector2f((round)(textRect.left + textRect.width / 2.f), (round)(textRect.top + textRect.height / 2.f)));
		playerTxtCMP->setPosition(Vector2f((round)(leftView.getSize().x / 2), (round)(row * 2.5)));

		//Player life icons
		playerLifeTexture.loadFromFile("res/img/others/player_life.png");
		playerLifeSpriteCMP->isFollowingParent(false);
		playerLifeSpriteCMP->getSprite().setTexture(playerLifeTexture);
		playerLifeSpriteCMP->getSprite().setColor(Color::Red);
		playerLifeSpriteCMP->getSprite().setPosition(Vector2f(col * 2, row * 0.5));
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
		playerSpeedTxtCMP->setPosition(Vector2f(col * 5.5 + playerSpeedTxtCMP->_text.getGlobalBounds().left - playerSpeedTxtCMP->_text.getGlobalBounds().width, row * 10));
		playerSpeedTxtCMP->setFontSize(30u);

		//Bullets PowerUps
		playerBulletPowerTxtCMP->setPosition(Vector2f(col * 5.5 + playerBulletPowerTxtCMP->_text.getGlobalBounds().left - playerBulletPowerTxtCMP->_text.getGlobalBounds().width, row * 11));
		playerBulletPowerTxtCMP->setFontSize(30u);
		playerFireRateTxtCMP->setPosition(Vector2f(col * 5.5 + playerFireRateTxtCMP->_text.getGlobalBounds().left - playerFireRateTxtCMP->_text.getGlobalBounds().width, row * 12));
		playerFireRateTxtCMP->setFontSize(30u);
		playerBulletNumberTxtCMP->setPosition(Vector2f(col * 5.5 + playerBulletNumberTxtCMP->_text.getGlobalBounds().left - playerBulletNumberTxtCMP->_text.getGlobalBounds().width, row * 13));
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
	auto lifes = playerCMP->getPlayerLifes();

	if (lifes >= 0) {
		playerLifeRec.left = (round)(playerLifeTexture.getSize().x / 5);
		playerLifeRec.top = (round)(playerLifeTexture.getSize().y * 0);
		playerLifeRec.width = (round)(playerLifeTexture.getSize().x / 5) * (lifes);
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

		upgradeBulletsSpriteCMP->getSprite().setPosition(Vector2f((round)(col * 5), (round)(row * (10 + i)) - (round)(upgradeBulletsSpriteCMP->getSprite().getTextureRect().height/2)));
		upgradeBulletsSpriteCMP->getSprite().setTextureRect(upgradeCounterRec);

		if (i == 1) { upgradeFlyeSpeedSpriteCMP = upgradeBulletsSpriteCMP; };
		if (i == 2) { upgradeDamageSpriteCMP = upgradeBulletsSpriteCMP; };
		if (i == 3) { upgradeFirerateSpriteCMP = upgradeBulletsSpriteCMP; };
	}
}

void Panels::setUpgradesSprites(string type, int counter) {

	auto playerCMP = player->GetCompatibleComponent<PlayerComponent>()[0];

	upgradeCounterRec.left = (round)(upgradeCounterTexture.getSize().x / 5);
	upgradeCounterRec.top = (round)(upgradeCounterTexture.getSize().y * 0);
	upgradeCounterRec.width = (round)((upgradeCounterTexture.getSize().x / 5) * (counter));
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

		if (currentLifes != playerCMP->_playerSettings.lifes) { setLifeSprites(); }

		if (currentBulletDamage != playerCMP->_bulletSettings.damageUpgradeCount) {
			setUpgradesSprites("damage", playerCMP->_bulletSettings.damageUpgradeCount);
		}
		if (currentFlySpeed != playerCMP->_playerSettings.flySpeedUpgradeCount) {
			setUpgradesSprites("flySpeed", playerCMP->_playerSettings.flySpeedUpgradeCount);
		}
		if (currentFirerate != playerCMP->_weaponSettings.firerateUpgradeCount) {
			setUpgradesSprites("firerate", playerCMP->_weaponSettings.firerateUpgradeCount);
		}
		if (currentBulletSpread != playerCMP->_weaponSettings.numBulletsUpgradeCount) {
			setUpgradesSprites("bullets", playerCMP->_weaponSettings.numBulletsUpgradeCount);
		}
		timer = 0;
	}
}

void Panels::render() {
}