#pragma once
#include <ecm.h>
#include <SFML/Audio.hpp>

using namespace sf;
using namespace std;

class SoundComponent : public Component
{
protected:
	std::shared_ptr<sf::Sound> sound;
	std::shared_ptr<sf::SoundBuffer> sBuffer;
public: 
	SoundComponent() = delete;
	explicit SoundComponent(Entity* p);
	
	void update(double dt) override {}
	void render() override {} 

	void playSound() const;
	void stopSound() const;
	void loadSound(std::string filename);
	std::shared_ptr<sf::Sound> getSound() const;
	std::shared_ptr<sf::SoundBuffer> getSoundBuffer() const;	
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