#ifndef SOUNDEFFECTS_H
#define SOUNDEFFECTS_H

#include <SFML/Audio.hpp>

class SoundEffects
{
private:
	//Variables
	sf::SoundBuffer buffer;
public:
	//Constructor
	SoundEffects(std::string soundFileName);
	
	sf::Sound sound;

	//Functions
	void setVolume(int volume);

	void playSound();
};

#endif // !SOUNDEFFECTS_H
