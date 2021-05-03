#pragma once
#include "../settings/bullet_settings.h"
#include "../settings/player_settings.h"
#include "../settings/texture_helper_settings.h"
#include "../settings/weapon_settings.h"
#include <atlstr.h>

class LoadSaveGame {
public:
	//Finds the Games Saved folder and returns true or false
	static bool setUpPath();
	//Saves the current players settings
	static void saveGame();
	//Loads the last players settings
	static void loadGame();

protected:
	static playerSettings pSettings;
	static weaponSettings wSettings;
	static bulletSettings bSettings;
	static textureSettings pTexHelper;
	static textureSettings bTexHelper;
	static CStringA savedGamesFilePath;
	static CStringA pSettingsPath;
	static CStringA wSettingsPath;
	static CStringA bSettingsPath;
	static CStringA pTexHelperPath;
	static CStringA bTexHelperPath;
};

