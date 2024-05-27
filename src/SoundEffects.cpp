#include "SoundEffects.h"

/////////////////////////////////// CONSTRUCTOR FUNCTIONS ////////////////////////////////////////////

SoundEffects::SoundEffects(std::string soundFileName)
{
	if (!buffer.loadFromFile(soundFileName))
		throw("ERROR::PAUSE_MENU_STATE::COULT NOT LOAD SOUND");

	this->sound.setBuffer(buffer);
}

/////////////////////////////////// ACCESSOR FUNCTIONS ////////////////////////////////////////////

void SoundEffects::setVolume(int volume)
{
	this->sound.setVolume(volume);
}

void SoundEffects::playSound()
{
	this->sound.play();
}
