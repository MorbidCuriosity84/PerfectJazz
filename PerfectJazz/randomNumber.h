#pragma once
#include <random>
class RandomNumber {
public:
	static int generateRandomNumber(std::discrete_distribution<> dist);
};

