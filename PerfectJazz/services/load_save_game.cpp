#include "load_save_game.h"
#include "../lib/nlohmann/json.hpp"
#include "../player/cmp_player.h"
#include "../settings/settings_holder.h"
#include <engine.h>
#include <filesystem>
#include <Windows.h>
#include <fstream>
#include <shlobj_core.h>
#include <string>
#include <KnownFolders.h>
#include <atlstr.h>

using json = nlohmann::json;
using namespace std;
using namespace sf;

playerSettings LoadSaveGame::pSettings;
weaponSettings LoadSaveGame::wSettings;
bulletSettings LoadSaveGame::bSettings;
textureSettings LoadSaveGame::pTexHelper;
textureSettings LoadSaveGame::bTexHelper;
CStringA LoadSaveGame::savedGamesFilePath;
CStringA LoadSaveGame::pSettingsPath;
CStringA LoadSaveGame::wSettingsPath;
CStringA LoadSaveGame::bSettingsPath;
CStringA LoadSaveGame::pTexHelperPath;
CStringA LoadSaveGame::bTexHelperPath;
//Setting up conversion from settings to json
void to_json(json& j, const textureSettings& node) {
	j = {
		{"FileName", node.spriteFilename},
		{"spriteRows", node.spriteRows},
		{"spriteCols", node.spriteCols},
		{"desiredRow", node.desiredRow},
		{"desiredCol", node.desiredCol},
		{"spriteTimer", node.spriteTimer}
	};
}
void to_json(json& j, const playerSettings& node) {
	j = {
		{"damage", node.damage},
		{"hp", node.hp},
		{"maxHP", node.maxHP},
		{"hpVisible", node.hpVisible},
		{"restitution", node.restitution},
		{"friction", node.friction},
		{"angle", node.angle},
		{"lifes", node.lifes},
		{"maxLifes", node.maxLifes},
		{"score", node.score},
		{"shopPoints", node.shopPoints},
		{"flySpeedUpgradeCount", node.flySpeedUpgradeCount},
		{"category", node.category},
		{"flySpeed", node.flySpeed},
		{"scaleX", node.scale.x},
		{"scaleY", node.scale.y},
		{"currentLevel", node.currentLevel }
	};
}
void to_json(json& j, const bulletSettings& node) {
	j = {
		{"lifetime", node.lifetime},
		{"damage", node.damage},
		{"damageUpgradeCount", node.damageUpgradeCount},
		{"hp", node.hp},
		{"category", node.category },
		{"angle", node.angle},
		{"direction", node.direction},
		{"velocityX", node.velocity.x},
		{"velocityY", node.velocity.y},
		{"spriteScaleX", node.spriteScale.x},
		{"spriteScaleY", node.spriteScale.y},
		{"sound", node.sound}
	};
}
void to_json(json& j, const weaponSettings& node) {
	j = {
		{"fireTime", node.fireTime},
		{"fireTimer", node.fireTimer},
		{"numBullets", node.numBullets},
		{"firerateUpgradeCount", node.firerateUpgradeCount},
		{"numBulletsUpgradeCount", node.numBulletsUpgradeCount},
		{"direction", node.direction},
		{"sound", node.sound}
	};
}

//Setting up conversion from JSON to settings
void from_json(const json& j, textureSettings& node) {
	j.at("FileName").get_to(node.spriteFilename);
	j.at("spriteRows").get_to(node.spriteRows);
	j.at("spriteCols").get_to(node.spriteCols);
	j.at("desiredRow").get_to(node.desiredRow);
	j.at("desiredCol").get_to(node.desiredCol);
	j.at("spriteTimer").get_to(node.spriteTimer);
}
void from_json(const json& j, playerSettings& node) {
	j.at("damage").get_to(node.damage);
	j.at("hp").get_to(node.hp);
	j.at("maxHP").get_to(node.maxHP);
	j.at("hpVisible").get_to(node.hpVisible);
	j.at("restitution").get_to(node.restitution);
	j.at("friction").get_to(node.friction);
	j.at("angle").get_to(node.angle);
	j.at("lifes").get_to(node.lifes);
	j.at("maxLifes").get_to(node.maxLifes);
	j.at("score").get_to(node.score);
	j.at("shopPoints").get_to(node.shopPoints);
	j.at("flySpeedUpgradeCount").get_to(node.flySpeedUpgradeCount);
	j.at("category").get_to(node.category);
	j.at("flySpeed").get_to(node.flySpeed);
	j.at("scaleX").get_to(node.scale.x);
	j.at("scaleY").get_to(node.scale.y);
	j.at("currentLevel").get_to(node.currentLevel);
}
void from_json(const json& j, bulletSettings& node) {
	j.at("lifetime").get_to(node.lifetime);
	j.at("damage").get_to(node.damage);
	j.at("damageUpgradeCount").get_to(node.damageUpgradeCount);
	j.at("hp").get_to(node.hp);
	j.at("category").get_to(node.category);
	j.at("angle").get_to(node.angle);
	j.at("direction").get_to(node.direction);
	j.at("velocityX").get_to(node.velocity.x);
	j.at("velocityY").get_to(node.velocity.y);
	j.at("spriteScaleX").get_to(node.spriteScale.x);
	j.at("spriteScaleY").get_to(node.spriteScale.y);
	j.at("sound").get_to(node.sound);
}
void from_json(const json& j, weaponSettings& node) {
	j.at("fireTime").get_to(node.fireTime);
	j.at("fireTimer").get_to(node.fireTimer);
	j.at("numBullets").get_to(node.numBullets);
	j.at("firerateUpgradeCount").get_to(node.firerateUpgradeCount);
	j.at("numBulletsUpgradeCount").get_to(node.numBulletsUpgradeCount);
	j.at("direction").get_to(node.direction);
	j.at("sound").get_to(node.sound);
}

bool LoadSaveGame::setUpPath() {
	//Check if there is a savedgames folder
	PWSTR path = NULL;
	HRESULT hres;
	std::wstring strFileName;
	std::string narrow;

	hres = SHGetKnownFolderPath(FOLDERID_SavedGames, KF_FLAG_CREATE, NULL, &path);
	if (path == NULL) {
		cout << "No saved games folder" << endl;
		return false;
	}
	else {
		//Converts wchar to const char. 
		//Setting up the file paths and file names for each of the settings files

		CStringA perfectJazzFolder = "/Perfect_Jazz/";
		CStringA pSettingsFile = "pSettings.json";
		CStringA wSettingssFile = "wSettings.json";
		CStringA bSettingssFile = "bSettings.json";
		CStringA pTexHelperFile = "pTexHelper.json";
		CStringA bTexHelperFile = "bTexHelper.json";
		savedGamesFilePath = path;
		perfectJazzFolder = CStringW(savedGamesFilePath + perfectJazzFolder);
		pSettingsPath = CStringW(perfectJazzFolder + pSettingsFile);
		wSettingsPath = CStringW(perfectJazzFolder + wSettingssFile);
		bSettingsPath = CStringW(perfectJazzFolder + bSettingssFile);
		pTexHelperPath = CStringW(perfectJazzFolder + pTexHelperFile);
		bTexHelperPath = CStringW(perfectJazzFolder + bTexHelperFile);


		if (CreateDirectory(perfectJazzFolder, NULL) || ERROR_ALREADY_EXISTS == GetLastError()) {
		}
		//Freeing bytes
		CoTaskMemFree(path);
		return true;
	}
}

void LoadSaveGame::saveGame() {
	if (setUpPath()) {
		auto oldCMP = player->GetCompatibleComponent<PlayerComponent>()[0];
		auto oldHP = player->GetCompatibleComponent<HPComponent>()[0];

		//Updating player settings before saving
		oldCMP->_playerSettings.hp = oldHP->getHP();
		oldCMP->_playerSettings.maxHP = oldHP->getMaxHP();
		oldCMP->_playerSettings.currentLevel = Engine::currentPlayerLevel;

		bSettings = oldCMP->weaponCMP->_bSettings;
		json bSetJson = bSettings;
		wSettings = oldCMP->weaponCMP->_wSettings;
		json wSetJson = wSettings;
		pSettings = oldCMP->_playerSettings;
		json pSetJson = pSettings;
		pTexHelper = oldCMP->_playerTextureHelper;
		json pHelperJson = pTexHelper;
		bTexHelper = oldCMP->_bulletTextureHelper;
		json bHelperJson = bTexHelper;

		std::ofstream bSet(bSettingsPath);
		bSet << bSetJson << std::endl;

		std::ofstream wSet(wSettingsPath);
		wSet << wSetJson << std::endl;

		std::ofstream pSet(pSettingsPath);
		pSet << pSetJson << std::endl;

		std::ofstream pHelper(pTexHelperPath);
		pHelper << pHelperJson << std::endl;

		std::ofstream bHelper(bTexHelperPath);
		bHelper << bHelperJson << std::endl;
	}
}

void LoadSaveGame::loadGame() {
	if (setUpPath()) {
		std::ifstream bSet(bSettingsPath);
		bulletSettings bSetJson = json::parse(bSet);
		std::ifstream wSet(wSettingsPath);
		weaponSettings wSetJson = json::parse(wSet);
		std::ifstream pSet(pSettingsPath);
		playerSettings pSetJson = json::parse(pSet);
		std::ifstream pHelper(pTexHelperPath);
		textureSettings pHelperJson = json::parse(pHelper);
		std::ifstream bHelper(bTexHelperPath);
		textureSettings bHelperJson = json::parse(bHelper);

		SettingsHolder::bSettings = bSetJson;
		SettingsHolder::wSettings = wSetJson;
		SettingsHolder::pSettings = pSetJson;
		SettingsHolder::pTexHelper = pHelperJson;
		SettingsHolder::bTexHelper = bHelperJson;

		auto bSpriteTexture = make_shared<sf::Texture>();
		auto bSpriteRectangle = make_shared<sf::IntRect>();
		auto pSpriteTexture = make_shared<sf::Texture>();
		auto pspriteRectangle = make_shared<sf::IntRect>();

		SettingsHolder::pTexHelper.spriteTexture = bSpriteTexture;
		SettingsHolder::pTexHelper.spriteRectangle = bSpriteRectangle;
		SettingsHolder::bTexHelper.spriteTexture = pSpriteTexture;
		SettingsHolder::bTexHelper.spriteRectangle = pspriteRectangle;
	}

}


