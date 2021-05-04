#pragma once
#include <queue>
#include <SFML/Audio.hpp>
#include "../game.h"

using namespace std;
using namespace sf;

//Holds a static array of ints that represents the current buffer being used
class SoundQueue
{
protected:	
	static int counts[32]; //keeps a pointer to the next available sound
public:
	//Default constructor
	SoundQueue() = default;
	//Default destructor
	~SoundQueue() = default;
	//Gets sounds from the buffer
	static sf::Sound getSound(SOUNDS sound);
};

