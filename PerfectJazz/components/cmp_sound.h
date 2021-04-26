#pragma once
#include <ecm.h>
#include <SFML/Audio.hpp>

using namespace sf;

class SoundComponent : public Component
{
protected:
	std::shared_ptr<sf::Sound> sound;
	std::shared_ptr<sf::SoundBuffer> sBuffer;
public: 
	SoundComponent(Entity* p);
	void playSound() const;
	void stopSound() const;
	std::shared_ptr<sf::Sound> getSound() const;
	std::shared_ptr<sf::SoundBuffer> getSoundBuffer() const;
};

