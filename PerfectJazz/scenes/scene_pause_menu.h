#pragma once
#include "engine.h"
#include "../components/cmp_text.h"

//Scene with a pause menu, that allows the player to save the game, go to the main menu
//or exit the game
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
	std::shared_ptr<TextComponent> menuOption4;
	std::shared_ptr<TextComponent> savingGameTxt;
	std::shared_ptr<TextComponent> cantSaveTxt;

	int selectedIndex;
	double timer;
	double savingTimer;
	double notSavingTimer;
	bool savingGame;
	bool notSavingGame;
	std::vector<std::string> s;
	void changeMenuText(std::vector<std::string> s);
	void alignSprite();
};


