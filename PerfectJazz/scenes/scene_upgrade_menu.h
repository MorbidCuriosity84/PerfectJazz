#pragma once
#include "engine.h"
#include "../components/cmp_text.h"

class UpgradeMenu : public Scene {
public:
	UpgradeMenu() = default;
	~UpgradeMenu() override = default;

	void Load() override;
	void UnLoad() override;
	void Update(const double& dt) override;
	void moveUp();
	void moveDown();

protected:
	sf::IntRect _upgradeShipRect;
	sf::IntRect _coinRect;
	std::shared_ptr<sf::Texture> _upgradeShipTex;
	std::shared_ptr<sf::Texture> _coinTex;
	std::vector<std::shared_ptr<TextComponent>> allTextCMP;
	std::shared_ptr<TextComponent> menuOption1;
	std::shared_ptr<TextComponent> menuOption2;
	std::shared_ptr<TextComponent> menuOption3;
	std::shared_ptr<TextComponent> menuOption4;
	std::shared_ptr<TextComponent> menuOption1Value;
	std::shared_ptr<TextComponent> menuOption2Value;
	std::shared_ptr<TextComponent> menuOption3Value;
	std::shared_ptr<TextComponent> menuOption4Value;
	std::shared_ptr<TextComponent> menuOption1NextValue;
	std::shared_ptr<TextComponent> menuOption2NextValue;
	std::shared_ptr<TextComponent> menuOption3NextValue;
	std::shared_ptr<TextComponent> menuOption4NextValue;
	std::shared_ptr<TextComponent> menuOption1Cost;
	std::shared_ptr<TextComponent> menuOption2Cost;
	std::shared_ptr<TextComponent> menuOption3Cost;
	std::shared_ptr<TextComponent> menuOption4Cost;
	std::shared_ptr<TextComponent> currentValueText;
	std::shared_ptr<TextComponent> pressEnterText;
	std::shared_ptr<TextComponent> nextValueText;
	std::shared_ptr<TextComponent> upgradeCostText;
	std::shared_ptr<TextComponent> coinsTxtCMP;
	std::shared_ptr<TextComponent> titleCMP;
	std::shared_ptr<TextComponent> noEnoughMoneyText;
	std::shared_ptr<TextComponent> exitText;
	std::string upgradeCost;
	double fireRateMulti;
	double flySpeedMulti;
	double damageMulti;
	double maxHPMulti;
	double maxHPUpgrade;
	double maxFlySpeed;
	double maxBulletDamage;
	double maxFireRate;

	int selectedIndex;
	int col;
	int row;
	double timer;
	double pressTextTimer;
	double keyTimer;
	double notEnoughTimer;
	std::vector<std::string> s;
	void changeMenuText(std::vector<std::string> s);
	void alignSprite();
	void updatingCurrentValues();
	void updatingNextValues();
	void updatingCost();
	void centeringText();
	void purchasingUpgrade(int type);
};


