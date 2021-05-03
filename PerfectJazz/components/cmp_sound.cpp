#include "cmp_sound.h"

SoundComponent::SoundComponent(Entity* p) : Component(p), pitch(1.f), volume(25.f) {}

void SoundComponent::playSound() {
	sounds[soundIndexEnum].setPitch(pitch);
	sounds[soundIndexEnum].play();
	pitch += 0.15f;	
	pitch = (pitch > 3.f ? pitch = 1.f : pitch);
	sounds->setPitch( pitch );
}

void SoundComponent::stopSound()
{
}

void SoundComponent::setPitch(float pitch)
{
}

void SoundComponent::setVolume(float vol)
{
}

MusicComponent::MusicComponent(Entity* p) : Component(p), music(std::make_shared<sf::Music>()) {}

void MusicComponent::playMusic() const { music->play(); }

void MusicComponent::stopMusic() const { music->stop(); }

void MusicComponent::loadMusic(std::string filename){ 
	
	music->openFromFile(filename);	
}

std::shared_ptr<sf::Music> MusicComponent::getSound() const { return music; }


