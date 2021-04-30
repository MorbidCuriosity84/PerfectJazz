#pragma once
#include "player_settings.h"
#include "weapon_settings.h"
#include "bullet_settings.h"
#include "texture_helper_settings.h"

static class SettingsHolder
{
public:
	static playerSettings pSettings;
	static weaponSettings wSettings;
	static bulletSettings bSettings;
	static textureSettings pTexHelper;
	static textureSettings bTexHelper;

	SettingsHolder() {}
	/*SettingsHolder( playerSettings _pSettings,
					weaponSettings _wSettings,
					bulletSettings _bSettings,
					textureSettings _pTexHelper,
					textureSettings _bTexHelper	) :
					pSettings(_pSettings), 
					wSettings(_wSettings), 
					bSettings(_bSettings), 
					pTexHelper(_pTexHelper), 
					bTexHelper(_bTexHelper)	{}*/
};

