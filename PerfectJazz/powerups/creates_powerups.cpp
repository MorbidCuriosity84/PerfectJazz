#include "creates_powerups.h"
#include "cmp_powerup.h"

void Powerups::createPowerups(Scene* _scene) {

	auto en = _scene->makeEntity();
	en->setView(mainView);

	auto power = en->addComponent<PowerupComponent>();
	power->deployPowerup();
}
