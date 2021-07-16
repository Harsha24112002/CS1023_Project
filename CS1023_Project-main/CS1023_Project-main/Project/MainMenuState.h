#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include "Button.h"
#include "GameInfo.h"
#include "InterfaceState.h"
class MainMenuState :
    public State
{
private:
	//Variables
	sf::Texture backgroundTexture;
	sf::RectangleShape background;
	sf::Font font;

	std::map<std::string, Button*> buttons;

	//Functions
	void initVariables();
	void initBackground();
	void initFonts();
	
	void initButtons();

public:
	MainMenuState(Statedata& state_info);
	virtual ~MainMenuState();

	//Functions

	void updateInput(const float& dt);
	void updateButtons();
	void update(const float& dt);
	void renderButtons(sf::RenderTarget* target = NULL);
	void render(sf::RenderTarget* target = NULL);
};

#endif