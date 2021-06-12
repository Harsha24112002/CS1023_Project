#include "SFML/Graphics.hpp"
#ifndef BOUND_RECT_H
#define BOUND_RECT_H
class Boundrect
{
	private:

	sf::RectangleShape bound;
	sf::Sprite& sprite;
	sf::Vector2f offset;
	sf::FloatRect rectbound;

	public:

	Boundrect(sf::Sprite& sprite,sf::Vector2f offset,float width,float height);
	void update();
	void render(sf::RenderTarget* Target);
	void move(sf::Vector2f pos);
	sf::FloatRect getfloatrect(){return rectbound;}
};
#endif