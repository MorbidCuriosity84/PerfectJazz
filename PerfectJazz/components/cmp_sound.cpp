#include "cmp_sound.h"
// Constructor for the sound component
SoundComponent::SoundComponent(Entity* p) : Component(p), pitch(1.f), volume(25.f) {}

// Plays the sound, setting the pitch to its current value
void SoundComponent::playSound() {
	sounds[soundIndexEnum].setPitch(pitch);
	sounds[soundIndexEnum].play();
	pitch += 0.15f;	
	pitch = (pitch > 3.f ? pitch = 1.f : pitch);
	sounds->setPitch( pitch );
}

// Constructor for the music component
MusicComponent::MusicComponent(Entity* p) : Component(p), music(std::make_shared<sf::Music>()) {}

// Plays music
void MusicComponent::playMusic() const { music->play(); }

// Stops music
void MusicComponent::stopMusic() const { music->stop(); }

// Loads music from file
void MusicComponent::loadMusic(std::string filename){ 
	
	music->openFromFile(filename);	
}
// Get the loaded music
std::shared_ptr<sf::Music> MusicComponent::getSound() const { return music; }


