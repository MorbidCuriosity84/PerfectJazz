#pragma once
#include "engine.h"
#include "../components/cmp_text.h"
class MenuSettings : public Scene {
public:
	MenuSettings() = default;
	~MenuSettings() override = default;

	void Load() override;
	void UnLoad() override;
	void Update(const double& dt) override;
	void moveUp();
	void moveDown();
	int getPressedItem();

protected:
	sf::IntRect _titleShipLeftRect;
	sf::IntRect _titleShipRightRect;
	std::shared_ptr<sf::Texture> _titleShipTex;
	std::vector<std::shared_ptr<TextComponent>> menuOption;
	int selectedIndex;
	double timer;
};