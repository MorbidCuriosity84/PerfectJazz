#pragma once
#include "engine.h"
#include "../components/cmp_text.h"

class PauseMenu : public Scene {
public:
	PauseMenu() = default;
	~PauseMenu() override = default;

	void Load() override;
	void UnLoad() override;
	void Update(const double& dt) override;
	void moveUp();
	void moveDown();

protected:
	sf::IntRect _titleShipLeftRect;
	sf::IntRect _titleShipRightRect;
	std::shared_ptr<sf::Texture> _titleShipTex;
	std::vector<std::shared_ptr<TextComponent>> menuOption;
	std::shared_ptr<TextComponent> menuOption1;
	std::shared_ptr<TextComponent> menuOption2;
	std::shared_ptr<TextComponent> menuOption3;
	int selectedIndex;
	double timer;
	std::vector<std::string> s;
	void changeMenuText(std::vector<std::string> s);
	void alignSprite();
};


