#ifndef PLAYERATTRIBUTES_H
#define PLAYERATTRIBUTES_H

#define HPPOS sf::Vector2f(1600,200)
#define HPHEIGHT 15
#define COINPOS sf::Vector2f(1600,100)
#define P2POS sf::Vector2f(1600,250)
#define SHIELDPOS sf::Vector2f(1600,300)
#include "Player.h"

class PlayerAttributes
{
private:
	//Variables
	 //sf Variables
	 sf::RectangleShape Hpbar;
	 sf::RectangleShape Hpbaroutline;
	 sf::RectangleShape Poweruptimer;
	 sf::RectangleShape shieldtimer;
	 sf::Text coins;
	 sf::Font font;

	 //Objects
	 Player* player;
	 
	std::string s;

public:
	//Constructor
	PlayerAttributes(Player* player);

	//Update and Render Functions
	void update();
	void render(sf::RenderTarget* target);
};

#endif