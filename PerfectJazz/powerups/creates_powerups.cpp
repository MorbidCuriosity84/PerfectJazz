#include "creates_powerups.h"
#include "cmp_powerup.h"
#include "../PerfectJazz/services/randomNumber.h"
#include "../settings/texture_helper_settings.h"
#include "../pools/powerupPool.h"
#include <system_physics.h>

using namespace std;
using namespace sf;
using namespace Physics;

Scene* _scene;
double _timer;
textureSettings _powerupTextureHelper;
powerupSettings _powerupSettings;

//Deploys the powerups
void Powerups::deployPowerups() {
	std::string type;
	//probabilities for the powerups. Each power up has a chance to be randomly picked
	std::discrete_distribution<> powerupsWeights({
		1,    // Damage % chance       1,  
		2,    // Health % chance       1,  
		1,    // Bullet Num % chance   0.3,
		0.7,    // Firerate % chance	   0.7,
		0.7,    // Player Mov % chance 0.7,
		97,    // Coin % chance		   97,	
		0.2 });// Extra % chance	   0.2 
	int choosenPowerup = RandomNumber::generateRandomNumber(powerupsWeights);

	//probabilities for the columns. Each columns has a chance to be randomly picked
	std::discrete_distribution<> columnWeights({
		2,   // 1st column % chance
		10,  // 2nd column % chance
		8,   // 3rd column % chance
		5,   // 4th column % chance
		8,   // 5th column % chance
		2,   // 6th column % chance
		5,   // 7th column % chance
		10,  // 8th column % chance
		10,  // 9th column % chance
		5,   // 10th column % chance
		2,   // 11th column % chance
		8,   // 12th column % chance
		5,   // 13th column % chance
		8,   // 14th column % chance
		10,  // 15th column % chance
		2 });// 16th column % chance

	int choosenColumn = RandomNumber::generateRandomNumber(columnWeights);

	//if Damage
	if (choosenPowerup == 0) { 
		_powerupTextureHelper = TextureHelpingSettings::LoadSettings(DAMAGE_PWU, _scene); type = "damage_pwu";
		_powerupSettings = PowerupSettings::LoadSettings(DAMAGE_PWU, _scene);
	}
	//if Health
	if (choosenPowerup == 1) { 
		_powerupTextureHelper = TextureHelpingSettings::LoadSettings(HP_PWU, _scene); type = "hp_pwu";
		_powerupSettings = PowerupSettings::LoadSettings(HP_PWU, _scene);
	}
	//if Bullet Num
	if (choosenPowerup == 2) { 
		_powerupTextureHelper = TextureHelpingSettings::LoadSettings(BULLET_NUM_PWU, _scene); type = "bullet_num_pwu";
		_powerupSettings = PowerupSettings::LoadSettings(BULLET_NUM_PWU, _scene);
	}
	//if Firerate
	if (choosenPowerup == 3) {
		_powerupTextureHelper = TextureHelpingSettings::LoadSettings(FIRERATE_PWU, _scene); type = "firerate_pwu";
		_powerupSettings = PowerupSettings::LoadSettings(FIRERATE_PWU, _scene);
	}
	//if Player movement
	if (choosenPowerup == 4) { 
		_powerupTextureHelper = TextureHelpingSettings::LoadSettings(PLAYER_MOVEMENT_PWU, _scene); type = "player_movement_pwu";
		_powerupSettings = PowerupSettings::LoadSettings(PLAYER_MOVEMENT_PWU, _scene);
	}
	//if Coin or Extra
	if (choosenPowerup == 5 || choosenPowerup == 6) { 
		_powerupTextureHelper = TextureHelpingSettings::LoadSettings(COIN_PWU, _scene);  type = "coin_pwu";
		_powerupSettings = PowerupSettings::LoadSettings(COIN_PWU, _scene);
	}
	//If extra, deployes a bonus with coins spelling the word "BONUS"
	//This function draws one line at a time, in order to display the word "BONUS"
	if (choosenPowerup == 6) {
		for (int i = 0; i < 5; i++) {
			if (i == 0) {
				for (int j = 0; j < 14; j++) {
					shared_ptr<Entity> en = PowerupPool::pwp_pool[PowerupPool::pwp_poolPointer++];
					en->setView(mainView);

					if (j == 0) { en->setPosition(Vector2f((round)(mainView.getSize().x / 32 * 4) + ((mainView.getSize().x / 32)), mainView.getSize().x / 32 - (mainView.getSize().x / 32) * i)); }
					if (j == 1) { en->setPosition(Vector2f((round)(mainView.getSize().x / 32 * 5) + ((mainView.getSize().x / 32)), mainView.getSize().x / 32 - (mainView.getSize().x / 32) * i)); }
					if (j == 2) { en->setPosition(Vector2f((round)(mainView.getSize().x / 32 * 6) + ((mainView.getSize().x / 32)), mainView.getSize().x / 32 - (mainView.getSize().x / 32) * i)); }
					if (j == 3) { en->setPosition(Vector2f((round)(mainView.getSize().x / 32 * 10) + ((mainView.getSize().x / 32)), mainView.getSize().x / 32 - (mainView.getSize().x / 32) * i)); }
					if (j == 4) { en->setPosition(Vector2f((round)(mainView.getSize().x / 32 * 11) + ((mainView.getSize().x / 32)), mainView.getSize().x / 32 - (mainView.getSize().x / 32) * i)); }
					if (j == 5) { en->setPosition(Vector2f((round)(mainView.getSize().x / 32 * 14) + ((mainView.getSize().x / 32)), mainView.getSize().x / 32 - (mainView.getSize().x / 32) * i)); }
					if (j == 6) { en->setPosition(Vector2f((round)(mainView.getSize().x / 32 * 17) + ((mainView.getSize().x / 32)), mainView.getSize().x / 32 - (mainView.getSize().x / 32) * i)); }
					if (j == 7) { en->setPosition(Vector2f((round)(mainView.getSize().x / 32 * 19) + ((mainView.getSize().x / 32)), mainView.getSize().x / 32 - (mainView.getSize().x / 32) * i)); }
					if (j == 8) { en->setPosition(Vector2f((round)(mainView.getSize().x / 32 * 20) + ((mainView.getSize().x / 32)), mainView.getSize().x / 32 - (mainView.getSize().x / 32) * i)); }
					if (j == 9) { en->setPosition(Vector2f((round)(mainView.getSize().x / 32 * 21) + ((mainView.getSize().x / 32)), mainView.getSize().x / 32 - (mainView.getSize().x / 32) * i)); }
					if (j == 10) { en->setPosition(Vector2f((round)(mainView.getSize().x / 32 * 22) + ((mainView.getSize().x / 32)), mainView.getSize().x / 32 - (mainView.getSize().x / 32) * i)); }
					if (j == 11) { en->setPosition(Vector2f((round)(mainView.getSize().x / 32 * 24) + ((mainView.getSize().x / 32)), mainView.getSize().x / 32 - (mainView.getSize().x / 32) * i)); }
					if (j == 12) { en->setPosition(Vector2f((round)(mainView.getSize().x / 32 * 25) + ((mainView.getSize().x / 32)), mainView.getSize().x / 32 - (mainView.getSize().x / 32) * i)); }
					if (j == 13) { en->setPosition(Vector2f((round)(mainView.getSize().x / 32 * 26) + ((mainView.getSize().x / 32)), mainView.getSize().x / 32 - (mainView.getSize().x / 32) * i)); }


					en->addComponent<PowerupComponent>(_powerupTextureHelper, _powerupSettings);
					en->addTag(type);
				}
			}
			if (i == 1) {
				for (int j = 0; j < 9; j++) {
					shared_ptr<Entity> en = PowerupPool::pwp_pool[PowerupPool::pwp_poolPointer++];
					en->setView(mainView);

					if (j == 0) { en->setPosition(Vector2f((round)(mainView.getSize().x / 32 * 4) + ((mainView.getSize().x / 32)), mainView.getSize().x / 32 - (mainView.getSize().x / 32) * i)); }
					if (j == 1) { en->setPosition(Vector2f((round)(mainView.getSize().x / 32 * 7) + ((mainView.getSize().x / 32)), mainView.getSize().x / 32 - (mainView.getSize().x / 32) * i)); }
					if (j == 2) { en->setPosition(Vector2f((round)(mainView.getSize().x / 32 * 9) + ((mainView.getSize().x / 32)), mainView.getSize().x / 32 - (mainView.getSize().x / 32) * i)); }
					if (j == 3) { en->setPosition(Vector2f((round)(mainView.getSize().x / 32 * 12) + ((mainView.getSize().x / 32)), mainView.getSize().x / 32 - (mainView.getSize().x / 32) * i)); }
					if (j == 4) { en->setPosition(Vector2f((round)(mainView.getSize().x / 32 * 14) + ((mainView.getSize().x / 32)), mainView.getSize().x / 32 - (mainView.getSize().x / 32) * i)); }
					if (j == 5) { en->setPosition(Vector2f((round)(mainView.getSize().x / 32 * 17) + ((mainView.getSize().x / 32)), mainView.getSize().x / 32 - (mainView.getSize().x / 32) * i)); }
					if (j == 6) { en->setPosition(Vector2f((round)(mainView.getSize().x / 32 * 19) + ((mainView.getSize().x / 32)), mainView.getSize().x / 32 - (mainView.getSize().x / 32) * i)); }
					if (j == 7) { en->setPosition(Vector2f((round)(mainView.getSize().x / 32 * 22) + ((mainView.getSize().x / 32)), mainView.getSize().x / 32 - (mainView.getSize().x / 32) * i)); }
					if (j == 8) { en->setPosition(Vector2f((round)(mainView.getSize().x / 32 * 27) + ((mainView.getSize().x / 32)), mainView.getSize().x / 32 - (mainView.getSize().x / 32) * i)); }

					en->addComponent<PowerupComponent>(_powerupTextureHelper, _powerupSettings);
					en->addTag(type);
				}
			}

			if (i == 2) {
				for (int j = 0; j < 12; j++) {
					shared_ptr<Entity> en = PowerupPool::pwp_pool[PowerupPool::pwp_poolPointer++];
					en->setView(mainView);
					if (j == 0) { en->setPosition(Vector2f((round)(mainView.getSize().x / 32 * 4) + ((mainView.getSize().x / 32)), mainView.getSize().x / 32 - (mainView.getSize().x / 32) * i)); }
					if (j == 1) { en->setPosition(Vector2f((round)(mainView.getSize().x / 32 * 5) + ((mainView.getSize().x / 32)), mainView.getSize().x / 32 - (mainView.getSize().x / 32) * i)); }
					if (j == 2) { en->setPosition(Vector2f((round)(mainView.getSize().x / 32 * 6) + ((mainView.getSize().x / 32)), mainView.getSize().x / 32 - (mainView.getSize().x / 32) * i)); }
					if (j == 3) { en->setPosition(Vector2f((round)(mainView.getSize().x / 32 * 9) + ((mainView.getSize().x / 32)), mainView.getSize().x / 32 - (mainView.getSize().x / 32) * i)); }
					if (j == 4) { en->setPosition(Vector2f((round)(mainView.getSize().x / 32 * 12) + ((mainView.getSize().x / 32)), mainView.getSize().x / 32 - (mainView.getSize().x / 32) * i)); }
					if (j == 5) { en->setPosition(Vector2f((round)(mainView.getSize().x / 32 * 14) + ((mainView.getSize().x / 32)), mainView.getSize().x / 32 - (mainView.getSize().x / 32) * i)); }
					if (j == 6) { en->setPosition(Vector2f((round)(mainView.getSize().x / 32 * 16) + ((mainView.getSize().x / 32)), mainView.getSize().x / 32 - (mainView.getSize().x / 32) * i)); }
					if (j == 7) { en->setPosition(Vector2f((round)(mainView.getSize().x / 32 * 17) + ((mainView.getSize().x / 32)), mainView.getSize().x / 32 - (mainView.getSize().x / 32) * i)); }
					if (j == 8) { en->setPosition(Vector2f((round)(mainView.getSize().x / 32 * 19) + ((mainView.getSize().x / 32)), mainView.getSize().x / 32 - (mainView.getSize().x / 32) * i)); }
					if (j == 9) { en->setPosition(Vector2f((round)(mainView.getSize().x / 32 * 22) + ((mainView.getSize().x / 32)), mainView.getSize().x / 32 - (mainView.getSize().x / 32) * i)); }
					if (j == 10) { en->setPosition(Vector2f((round)(mainView.getSize().x / 32 * 25) + ((mainView.getSize().x / 32)), mainView.getSize().x / 32 - (mainView.getSize().x / 32) * i)); }
					if (j == 11) { en->setPosition(Vector2f((round)(mainView.getSize().x / 32 * 26) + ((mainView.getSize().x / 32)), mainView.getSize().x / 32 - (mainView.getSize().x / 32) * i)); }

					en->addComponent<PowerupComponent>(_powerupTextureHelper, _powerupSettings);
					en->addTag(type);
				}
			}
			if (i == 3) {
				for (int j = 0; j < 10; j++) {
					shared_ptr<Entity> en = PowerupPool::pwp_pool[PowerupPool::pwp_poolPointer++];
					en->setView(mainView);

					if (j == 0) { en->setPosition(Vector2f((round)(mainView.getSize().x / 32 * 4) + ((mainView.getSize().x / 32)), mainView.getSize().x / 32 - (mainView.getSize().x / 32) * i)); }
					if (j == 1) { en->setPosition(Vector2f((round)(mainView.getSize().x / 32 * 7) + ((mainView.getSize().x / 32)), mainView.getSize().x / 32 - (mainView.getSize().x / 32) * i)); }
					if (j == 2) { en->setPosition(Vector2f((round)(mainView.getSize().x / 32 * 9) + ((mainView.getSize().x / 32)), mainView.getSize().x / 32 - (mainView.getSize().x / 32) * i)); }
					if (j == 3) { en->setPosition(Vector2f((round)(mainView.getSize().x / 32 * 12) + ((mainView.getSize().x / 32)), mainView.getSize().x / 32 - (mainView.getSize().x / 32) * i)); }
					if (j == 4) { en->setPosition(Vector2f((round)(mainView.getSize().x / 32 * 14) + ((mainView.getSize().x / 32)), mainView.getSize().x / 32 - (mainView.getSize().x / 32) * i)); }
					if (j == 5) { en->setPosition(Vector2f((round)(mainView.getSize().x / 32 * 15) + ((mainView.getSize().x / 32)), mainView.getSize().x / 32 - (mainView.getSize().x / 32) * i)); }
					if (j == 6) { en->setPosition(Vector2f((round)(mainView.getSize().x / 32 * 17) + ((mainView.getSize().x / 32)), mainView.getSize().x / 32 - (mainView.getSize().x / 32) * i)); }
					if (j == 7) { en->setPosition(Vector2f((round)(mainView.getSize().x / 32 * 19) + ((mainView.getSize().x / 32)), mainView.getSize().x / 32 - (mainView.getSize().x / 32) * i)); }
					if (j == 8) { en->setPosition(Vector2f((round)(mainView.getSize().x / 32 * 22) + ((mainView.getSize().x / 32)), mainView.getSize().x / 32 - (mainView.getSize().x / 32) * i)); }
					if (j == 9) { en->setPosition(Vector2f((round)(mainView.getSize().x / 32 * 24) + ((mainView.getSize().x / 32)), mainView.getSize().x / 32 - (mainView.getSize().x / 32) * i)); }

					en->addComponent<PowerupComponent>(_powerupTextureHelper, _powerupSettings);
					en->addTag(type);
				}
			}

			if (i == 4) {
				for (int j = 0; j < 12; j++) {
					shared_ptr<Entity> en = PowerupPool::pwp_pool[PowerupPool::pwp_poolPointer++];
					en->setView(mainView);

					if (j == 0) { en->setPosition(Vector2f((round)(mainView.getSize().x / 32 * 4) + ((mainView.getSize().x / 32)), mainView.getSize().x / 32 - (mainView.getSize().x / 32) * i)); }
					if (j == 1) { en->setPosition(Vector2f((round)(mainView.getSize().x / 32 * 5) + ((mainView.getSize().x / 32)), mainView.getSize().x / 32 - (mainView.getSize().x / 32) * i)); }
					if (j == 2) { en->setPosition(Vector2f((round)(mainView.getSize().x / 32 * 6) + ((mainView.getSize().x / 32)), mainView.getSize().x / 32 - (mainView.getSize().x / 32) * i)); }
					if (j == 3) { en->setPosition(Vector2f((round)(mainView.getSize().x / 32 * 10) + ((mainView.getSize().x / 32)), mainView.getSize().x / 32 - (mainView.getSize().x / 32) * i)); }
					if (j == 4) { en->setPosition(Vector2f((round)(mainView.getSize().x / 32 * 11) + ((mainView.getSize().x / 32)), mainView.getSize().x / 32 - (mainView.getSize().x / 32) * i)); }
					if (j == 5) { en->setPosition(Vector2f((round)(mainView.getSize().x / 32 * 14) + ((mainView.getSize().x / 32)), mainView.getSize().x / 32 - (mainView.getSize().x / 32) * i)); }
					if (j == 6) { en->setPosition(Vector2f((round)(mainView.getSize().x / 32 * 17) + ((mainView.getSize().x / 32)), mainView.getSize().x / 32 - (mainView.getSize().x / 32) * i)); }
					if (j == 7) { en->setPosition(Vector2f((round)(mainView.getSize().x / 32 * 19) + ((mainView.getSize().x / 32)), mainView.getSize().x / 32 - (mainView.getSize().x / 32) * i)); }
					if (j == 8) { en->setPosition(Vector2f((round)(mainView.getSize().x / 32 * 22) + ((mainView.getSize().x / 32)), mainView.getSize().x / 32 - (mainView.getSize().x / 32) * i)); }
					if (j == 9) { en->setPosition(Vector2f((round)(mainView.getSize().x / 32 * 25) + ((mainView.getSize().x / 32)), mainView.getSize().x / 32 - (mainView.getSize().x / 32) * i)); }
					if (j == 10) { en->setPosition(Vector2f((round)(mainView.getSize().x / 32 * 26) + ((mainView.getSize().x / 32)), mainView.getSize().x / 32 - (mainView.getSize().x / 32) * i)); }
					if (j == 11) { en->setPosition(Vector2f((round)(mainView.getSize().x / 32 * 27) + ((mainView.getSize().x / 32)), mainView.getSize().x / 32 - (mainView.getSize().x / 32) * i)); }

					en->addComponent<PowerupComponent>(_powerupTextureHelper, _powerupSettings);
					en->addTag(type);
				}
			}
			_powerupSettings = PowerupSettings::LoadSettings(COIN_PWU, _scene);
		}
	}
	//Sets the entity to the mainview, adds a tag and sets the visibility and alive
	else {
		shared_ptr<Entity> en = PowerupPool::pwp_pool[PowerupPool::pwp_poolPointer++];
		en->setView(mainView);
		en->setVisible(false);

		en->setPosition(Vector2f((round)(mainView.getSize().x / 16 * choosenColumn) + (round)((mainView.getSize().x / 16) / 2), 0 - mainView.getSize().x / 32));

		en->addComponent<PowerupComponent>(_powerupTextureHelper, _powerupSettings);
		en->addTag(type);
		en->setAlive(true);
		en->setVisible(true);

	}
}

//Sets the scene and timer values
void Powerups::createPowerups(Scene* scene) {
	_scene = scene;
	_timer = 0;
}

//Deployes powerups regularly, depending on the timer value
void Powerups::update(double dt) {
	_timer += dt;

	if (_timer > 1) {
		deployPowerups();
		_timer = 0.f;
	}
}