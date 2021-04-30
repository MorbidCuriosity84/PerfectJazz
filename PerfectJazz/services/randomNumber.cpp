#include "randomNumber.h"
#include <map>
#include <chrono>
#include <iostream>

int RandomNumber::generateRandomNumber(std::discrete_distribution<> dist) {
	return genRandomNumBetween(dist, 0, 100);
}

int RandomNumber::genRandomNumBetween(std::discrete_distribution<> dist, int a, int b)
{
	std::random_device random;
	auto seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::mt19937 generates(seed);
	std::vector<int> vecNumbers;

	for (int n = a; n < b; ++n) {
		vecNumbers.push_back(dist(generates));
	}

	std::uniform_int_distribution<int> percentageDist(a, b-1);
	int selectedNumber = percentageDist(generates);

	return vecNumbers[selectedNumber];
}

int RandomNumber::genRandomNumBetween(int a, int b)
{
	std::uniform_int_distribution<int> dist(a,b);
	std::random_device random;
	auto seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::mt19937 generates(seed);
	std::vector<int> vecNumbers;

	for (int n = a; n < b; ++n) {
		vecNumbers.push_back(dist(generates));
	}

	std::uniform_int_distribution<int> percentageDist(a, b - 1);
	int selectedNumber = percentageDist(generates);

	return vecNumbers[selectedNumber];
}

double RandomNumber::generateUniformRealNumber(int a, int b) {
	std::mt19937_64 rng;	
	uint64_t timeSeed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
	std::seed_seq ss{ uint32_t(timeSeed & 0xffffffff), uint32_t(timeSeed >> 32) };
	rng.seed(ss);	
	std::uniform_real_distribution<double> unif(a, b);
	return unif(rng);
}
