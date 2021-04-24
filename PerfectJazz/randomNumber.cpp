#include "randomNumber.h"
#include <map>
#include <chrono>
#include <iostream>

int RandomNumber::generateRandomNumber(std::discrete_distribution<> dist) {
	
	std::random_device random;
	auto seed = std::chrono::system_clock::now().time_since_epoch().count();	
	std::mt19937 generates(seed);
	std::vector<int> vecNumbers;

	for (int n = 0; n < 100; ++n) {
		vecNumbers.push_back(dist(generates));
	}

	std::uniform_int_distribution<int> percentageDist(0, 99);
	int selectedNumber = percentageDist(generates);

	return vecNumbers[selectedNumber];
}
