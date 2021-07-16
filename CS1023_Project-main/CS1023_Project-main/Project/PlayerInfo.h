#ifndef PLAYERINFO_H
#define PLAYERINFO_H

#include "State.h"
#include "Button.h"
#include "GameState.h"

class PlayerInfo :
    public State
{
private:

	//Variables
	sf::Texture backgroundTexture;
	std::map<std::string, Button*> buttons;
	sf::RectangleShape background;
	sf::Font font;
	sf::RectangleShape next1;
	sf::RectangleShape next2;
	sf::RectangleShape rect;
	std::map<int, sf::RectangleShape> players;
	size_t currentnum;
	Button* PlayGameButton;
	std::map<int, sf::RectangleShape>::iterator itr;
	std::map<std::string, Button*>::iterator button_itr;
	float time;
	//Functions
	void initBackground();
	void initFonts();
	void initButtons();
	void initPlayers();

public:
	PlayerInfo(Statedata& state_info);
	virtual ~PlayerInfo();

	void updateInput(const float& dt);
	void updateButtons();
	void update(const float& dt);
	void renderButtons(sf::RenderTarget* target = NULL);
	void render(sf::RenderTarget* target = NULL);
};

#endif