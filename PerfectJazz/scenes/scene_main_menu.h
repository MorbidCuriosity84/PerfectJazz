#pragma once
#include "engine.h"
#include "../components/cmp_text.h"

enum _menuType {
	MAIN_MENU,
	SETTINGS_MENU,
	RESOLUTION_MENU,
	LEVEL_MENU,
};

//Scene with the main menu, that allows the player to load a game, star a new game,
//and change the resolution 
class MainMenu : public Scene {
public:
	MainMenu() = default;
	~MainMenu() override = default;
	void Load() override;
	void UnLoad() override;
	void Update(const double& dt) override;

protected:
	sf::IntRect _titleShipLeftRect;
	sf::IntRect _titleShipRightRect;
	std::shared_ptr<sf::Texture> _titleShipTex;
	std::vector<std::shared_ptr<TextComponent>> menuOption;
	std::shared_ptr<TextComponent> menuOption1;
	std::shared_ptr<TextComponent> menuOption2;
	std::shared_ptr<TextComponent> menuOption3;
	std::shared_ptr<TextComponent> menuOption4;
	std::shared_ptr<TextComponent> loadGameTxt;
	bool isMainMenuScreen;
	bool isLevelMenuScreen;
	bool isSettingsScreen;
	bool isResolutionScreen;
	bool isGameLoading;
	int selectedIndex;
	double timer;
	double loadingTimer;
	std::vector<std::string> s;
	void changeMenuText(std::vector<std::string> s);
	void alignSprite();
	void changeBools(bool isMainMenuScreen, bool isLevelMenuScreen, bool isSettingsScreen, bool isResolutionScreen);
	void switchSceneText(_menuType scene);
	void changeResolution(int type);
	void loadGame();
	void moveUp();
	void moveDown();
};