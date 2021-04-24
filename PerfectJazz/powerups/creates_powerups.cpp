#include "creates_powerups.h"
#include "cmp_powerup.h"
#include "../PerfectJazz/randomNumber.h"
#include "../settings/texture_helper_settings.h"

using namespace std;
using namespace sf;

Scene* _scene;
double _timer;
textureSettings _powerupTextureHelper;

void Powerups::deployPowerups() {

	auto en = _scene->makeEntity();
	en->setView(mainView);
	string type;
	//probabilities for the powerups. Each power up has a chance to be randomly picked
	std::discrete_distribution<> powerupsWeights({
		20,   // Damage % chance
		5,   // Bullet Num % chance
		15,   // Firerate % chance
		10,   // Player Mov % chance
		50 });// Coin % chance
	int choosenPowerup = RandomNumber::generateRandomNumber(powerupsWeights);

	//if Damage
	if (choosenPowerup == 0) { _powerupTextureHelper = TextureHelpingSettings::LoadSettings(DAMAGE_PWU, _scene); type = "damage_pwu"; }
	//if Bullet Num
	if (choosenPowerup == 1) { _powerupTextureHelper = TextureHelpingSettings::LoadSettings(BULLET_NUM_PWU, _scene); type = "bullet_num_pwu";	}
	//if Firerate
	if (choosenPowerup == 2) { _powerupTextureHelper = TextureHelpingSettings::LoadSettings(FIRERATE_PWU, _scene); type = "firerate_pwu";	}
	//if Player movement
	if (choosenPowerup == 3) { _powerupTextureHelper = TextureHelpingSettings::LoadSettings(PLAYER_MOVEMENT_PWU, _scene); type = "player_movement_pwu";	}
	//if Coin
	if (choosenPowerup == 4) { _powerupTextureHelper = TextureHelpingSettings::LoadSettings(COIN_PWU, _scene);  type = "coin_pwu";	}

	en->addComponent<PowerupComponent>(_powerupTextureHelper, type);
}

void Powerups::createPowerups(Scene* scene) {
	_scene = scene;
	_timer = 0;
}

void Powerups::update(double dt) {
	_timer += dt;

	if (_timer > 0.1) {
		deployPowerups();
		_timer = 0.f;
	}
}
