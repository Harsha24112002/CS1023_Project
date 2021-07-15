#ifndef PLAYERATTRIBUTES_H
#define PLAYERATTRIBUTES_H
#include "Player.h"
class PlayerAttributes
{
	private:
	Player* player;
	sf::RectangleShape Hpbar;
	sf::RectangleShape Hpbaroutline;
	sf::Text coins;
	sf::Font font;
	std::string s;
	public :
	PlayerAttributes(Player* player);
	void update();
	void render(sf::RenderTarget* target);
};

#endif