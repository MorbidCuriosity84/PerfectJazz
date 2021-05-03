#pragma once
#include "../settings/bullet_settings.h"
#include "../settings/player_settings.h"
#include "../settings/texture_helper_settings.h"
#include "../settings/weapon_settings.h"
#include <atlstr.h>

class LoadSaveGame {
public:
	static bool setUpPath();
	static void saveGame();
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

