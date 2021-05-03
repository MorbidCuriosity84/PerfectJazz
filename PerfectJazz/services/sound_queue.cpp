#include "sound_Queue.h"

int SoundQueue::counts[32];

//Gets sounds from the buffer
sf::Sound SoundQueue::getSound(SOUNDS sound) {
	counts[sound] = counts[sound]++ % 8; //increments the count but keeps it below 8 = number of available sound buffers for each wav
	return sounds[sound * counts[sound]]; //finds the next sound buffer for that sound
}
