#pragma once
#include <random>
class RandomNumber {
public:
	//Generates numbers according to given distribution
	static int generateRandomNumber(std::discrete_distribution<> dist);
	//Generates numbers between a and b according to given distribution
	static int genRandomNumBetween(std::discrete_distribution<> dist, int a, int b);
	//Generates numbers uniformly between a and b
	static int genRandomNumBetween(int a, int b);
	//Generates a random real number between a and b
	static double generateUniformRealNumber(double a, double b);
};

