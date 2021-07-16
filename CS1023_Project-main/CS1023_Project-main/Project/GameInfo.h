#ifndef GAMEINFO_H
#define GAMEINFO_H

#include "State.h"
#include "GameState.h"
#include "Button.h"
#include "PlayerInfo.h"

class GameInfo : public State
{
private:

	//Variables
	sf::Texture backgroundTexture;
	std::map<std::string, Button*> buttons;
	sf::RectangleShape background;
	sf::Font font;
	sf::RectangleShape back;

	//Functions
	void initBackground();
	void initFonts();
	void initButtons();

public: 
	GameInfo(Statedata& state_info);
	virtual ~GameInfo();

	void updateInput(const float& dt);
	void updateButtons();
	void update(const float& dt);
	void renderButtons(sf::RenderTarget* target = NULL);
	void render(sf::RenderTarget* target = NULL);

};

#endif
