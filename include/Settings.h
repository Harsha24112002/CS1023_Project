#ifndef SETTINGS_H
#define SETTINGS_H

#include "State.h"
#include "Button.h"
#include "HowToPlay.h"
#include "SoundEffects.h"

class Settings : public State
{
private:
	//Variables
	 //sf Variables
	  //Rectangle shapes 
	  sf::RectangleShape background;

	  //View
	  sf::View view;
	 
	  //assets/Fonts
	  sf::Font font;
	 
	  //Text
	  sf::Text menuText;
	 
	std::map<std::string, Button*> buttons;

	//Init Functions
	void initBackground();
	void initView();
	void initFonts();
	void initButtons();
	void initSound();

public:
	//Constructor, Destructor
	Settings(Statedata& state_info);
	virtual ~Settings();

	int volumeBar = 10;
	sf::RectangleShape volumeLevel[15];
	SoundEffects* buttonSound;

	//Functions
	std::map<std::string, Button*>& getButtons();

	void addButton(const std::string key, float y, std::string text);
	const bool isButtonPressed(const std::string key);

	 //Update Functions
	 void updateButtons();
	 void updateVolume();
	 void update(const float& dt);
	 void updateInput(const float& dt);
	 
	 //Render Functions
	 void render(sf::RenderTarget* target = NULL);
};

#endif // !SETTINGS_H