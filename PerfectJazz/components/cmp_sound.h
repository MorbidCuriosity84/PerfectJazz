#pragma once
#include <ecm.h>
#include <SFML/Audio.hpp>
#include "../game.h"

using namespace sf;
using namespace std;

class SoundComponent : public Component
{
protected:
	SOUNDS soundIndexEnum;	
	float pitch;
	float volume;	
public: 
	SoundComponent() = delete;
	explicit SoundComponent(Entity* p);
	
	void update(double dt) override {}
	void render() override {} 

	void playSound();
	void stopSound();	

	void setPitch(float pitch);
	void setVolume(float vol);
};

class MusicComponent : public Component
{
protected:
	std::shared_ptr<sf::Music> music;	
public:
	MusicComponent() = delete;
	explicit MusicComponent(Entity* p);

	void update(double dt) override {}
	void render() override {}

	void playMusic() const;
	void stopMusic() const;
	void loadMusic(std::string filename);
	std::shared_ptr<sf::Music> getSound() const;	
};