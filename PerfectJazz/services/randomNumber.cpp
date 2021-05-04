#include "randomNumber.h"
#include <map>
#include <chrono>
#include <iostream>

//Generates numbers according to given distribution
int RandomNumber::generateRandomNumber(std::discrete_distribution<> dist) {
	return genRandomNumBetween(dist, 0, 100);
}
//Generates numbers between a and b according to given distribution
int RandomNumber::genRandomNumBetween(std::discrete_distribution<> dist, int a, int b)
{
	std::random_device random;
	auto seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::mt19937 generates(seed);
	std::vector<int> vecNumbers;

	//For each n numbers, the vecNubmers puts a that produces 
	//a random value according to the discrete distribution
	for (int n = a; n < b; ++n) {
		vecNumbers.push_back(dist(generates));
	}

	//A number from a to b-1 is generated randomly in order to selected
	//that said number from the vector of numbers vecNumbers
	std::uniform_int_distribution<int> percentageDist(a, b-1);
	int selectedNumber = percentageDist(generates);

	return vecNumbers[selectedNumber];
}
//Generates numbers uniformly between a and b
int RandomNumber::genRandomNumBetween(int a, int b)
{
	//The discrete distribution will be between a and b, which will also be used to 
	//generate a to b numbers
	std::uniform_int_distribution<int> dist(a,b);
	std::random_device random;
	auto seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::mt19937 generates(seed);
	std::vector<int> vecNumbers;

	//For each n numbers, the vecNubmers puts a that produces 
	//a random value according to the discrete distribution	
	for (int n = a; n < b; ++n) {
		vecNumbers.push_back(dist(generates));
	}

	//A number from a to b-1 is generated randomly in order to selected
	//that said number from the vector of numbers vecNumbers
	std::uniform_int_distribution<int> percentageDist(a, b - 1);
	int selectedNumber = percentageDist(generates);

	return vecNumbers[selectedNumber];
}
//Generates a random real number between a and b
double RandomNumber::generateUniformRealNumber(double a, double b) {

	std::mt19937_64 rng;	
	uint64_t timeSeed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
	std::seed_seq ss{ uint32_t(timeSeed & 0xffffffff), uint32_t(timeSeed >> 32) };
	rng.seed(ss);	
	std::uniform_real_distribution<double> unif(a, b);
	return unif(rng);
}
