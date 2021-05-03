#pragma once
#include "player_settings.h"
#include "weapon_settings.h"
#include "bullet_settings.h"
#include "texture_helper_settings.h"

static class SettingsHolder
{
public:
	//Creates an instance of the struct player settings, weapons settings, bullets settings,
	//player texture helper and bullet texture helper, to be used to save the players settings
	static playerSettings pSettings;
	static weaponSettings wSettings;
	static bulletSettings bSettings;
	static textureSettings pTexHelper;
	static textureSettings bTexHelper;

	//Default constructor
	SettingsHolder() {}
};

