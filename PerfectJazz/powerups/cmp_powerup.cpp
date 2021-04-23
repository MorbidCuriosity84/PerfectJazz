#include "cmp_powerup.h"


using namespace std;
using namespace sf;

void PowerupComponent::deployPowerup() {

	//probabilities for the powerups. Each power up has a chance to be randomly picked
	std::discrete_distribution<> powerupsWeights({ 10, 20, 50, 20 });
	int choosenPowerup = randomNumber(powerupsWeights);

	//probabilities for the columns. Each columns has a chance to be randomly picked
	std::discrete_distribution<> columnWeights({ 2, 10, 8, 5, 8, 2, 5, 10, 10, 5, 2, 8, 5, 8, 10, 2 });
	int choosenColumn = randomNumber(columnWeights);
	cout << choosenColumn << ": column" << endl;


}

void PowerupComponent::update(double dt) {
	timer += dt;

	if (timer > 0.5) {
		deployPowerup();
		timer = 0.f;
	}
}

int PowerupComponent::randomNumber(std::discrete_distribution<> dist) {

	std::random_device random;
	std::mt19937 generates(random());
	std::map<int, int> mapNumbers;

	for (int n = 0; n < 1000; ++n) {
		++mapNumbers[dist(generates)];
	}

	auto it = mapNumbers.begin();
	std::advance(it, rand() % mapNumbers.size());
	return it->first;
}


PowerupComponent::PowerupComponent(Entity* p) : Component(p) {
	timer = 0;
}