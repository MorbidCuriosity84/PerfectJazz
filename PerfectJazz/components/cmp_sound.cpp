#include "cmp_sound.h"

SoundComponent::SoundComponent(Entity* p) : Component(p), sound(std::make_shared<sf::Sound>()), sBuffer(make_shared<sf::SoundBuffer>()) {}

void SoundComponent::playSound() const { sound->play(); }

void SoundComponent::stopSound() const { sound->stop(); }

void SoundComponent::loadSound(std::string filename)
{
	if (!sBuffer->loadFromFile(filename)) {
		//error
	}
	sound->setBuffer(*sBuffer);
}

std::shared_ptr<sf::Sound> SoundComponent::getSound() const { return sound; }

std::shared_ptr<sf::SoundBuffer> SoundComponent::getSoundBuffer() const { return sBuffer; }

MusicComponent::MusicComponent(Entity* p) : Component(p), music(std::make_shared<sf::Music>()) {}

void MusicComponent::playMusic() const { music->play(); }

void MusicComponent::stopMusic() const { music->stop(); }

void MusicComponent::loadMusic(std::string filename){ 
	
	music->openFromFile(filename);	
}

std::shared_ptr<sf::Music> MusicComponent::getSound() const { return music; }

