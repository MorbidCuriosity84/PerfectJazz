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

MusicComponent::MusicComponent(Entity* p) : Component(p), sound(std::make_shared<sf::Sound>()), sBuffer(make_shared<sf::SoundBuffer>()) {}

void MusicComponent::playSound() const { sound->play(); }

void MusicComponent::stopSound() const { sound->stop(); }

void MusicComponent::loadSound(std::string filename){ 
	
	if (!sBuffer->loadFromFile(filename)) {
		//error
	}
	sound->setBuffer(*sBuffer);
}

std::shared_ptr<sf::Sound> MusicComponent::getSound() const { return sound; }

std::shared_ptr<sf::SoundBuffer> MusicComponent::getSoundBuffer() const { return sBuffer; }
