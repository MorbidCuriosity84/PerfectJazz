#pragma once
#include "engine.h"
#include "../components/cmp_text.h"

enum _menuType {
	MAIN_MENU,
	SETTINGS_MENU,
	RESOLUTION_MENU,
	LEVEL_MENU,
	HOW_TO_MENU,
};

//Scene with the main menu, that allows the player to load a game, star a new game,
//and change the resolution 
class MainMenu : public Scene {
public:
	MainMenu() = default;
	~MainMenu() override = default;
	void Load() override;
	void settingUpKeySprites();
	void UnLoad() override;
	void Update(const double& dt) override;

protected:
	sf::IntRect _titleShipLeftRect;
	sf::IntRect _titleShipRightRect;
	sf::IntRect _keysRect;
	sf::IntRect _spaceRect;
	std::shared_ptr<sf::Texture> _titleShipTex;
	std::vector<std::shared_ptr<TextComponent>> menuOption;
	std::shared_ptr<TextComponent> menuOption1;
	std::shared_ptr<TextComponent> menuOption2;
	std::shared_ptr<TextComponent> menuOption3;
	std::shared_ptr<TextComponent> menuOption4;
	std::shared_ptr<TextComponent> loadGameTxt;
	std::shared_ptr<TextComponent> arrowsTxt;
	std::shared_ptr<TextComponent> escTxt;
	std::shared_ptr<TextComponent> spaceTxt;
	std::shared_ptr<TextComponent> enterxt;
	bool isMainMenuScreen;
	bool isLevelMenuScreen;
	bool isSettingsScreen;
	bool isResolutionScreen;
	bool isGameLoading;
	bool isHowToScreen;
	int selectedIndex;
	double timer;
	double keysTimer;
	double loadingTimer;
	std::vector<std::string> s;
	void changeMenuText(std::vector<std::string> s);
	void alignSprite();
	void changeBools(bool isMainMenuScreen, bool isLevelMenuScreen, bool isSettingsScreen, bool isResolutionScreen, bool isHowToScreen);
	void switchSceneText(_menuType scene);
	void changeResolution(int type);
	void loadGame();
	void moveUp();
	void moveDown();
};