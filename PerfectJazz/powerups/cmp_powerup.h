#pragma once

#include <ecm.h>
#include <list>
#include <random>
#include <map>

using namespace sf;
using namespace std;

class PowerupComponent : public Component{
public:
	void render() override {};
	void update(double dt);
	int randomNumber(std::discrete_distribution<> dist);
	void deployPowerup();

	PowerupComponent() = delete;
	explicit PowerupComponent(Entity* p);
protected:
	double timer;
};

