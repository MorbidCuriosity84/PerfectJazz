#include "cmp_sound.h"

SoundComponent::SoundComponent(Entity* p) : Component(p), sound(std::make_shared<sf::Sound>()) {}

void SoundComponent::playSound() const { sound->play(); }

void SoundComponent::stopSound() const { sound->stop(); }

std::shared_ptr<sf::Sound> SoundComponent::getSound() const { return sound; }

std::shared_ptr<sf::SoundBuffer> SoundComponent::getSoundBuffer() const { return sBuffer; }
