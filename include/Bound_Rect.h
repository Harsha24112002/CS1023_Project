#ifndef BOUND_RECT_H
#define BOUND_RECT_H

#include "SFML/Graphics.hpp"

class Boundrect
{
private:
	//Variables
	 //sf Variables
	 sf::RectangleShape bound;
	 sf::Sprite& sprite;
	 sf::Vector2f offset;
	 sf::FloatRect rectbound;

public:
	//Constructor, Destructor
	/**
	 * @brief Constructor for Boundrect
	 * @param sprite Takes a sprite as a reference
	 * @param offset The offset from the position of sprite
	 * @param width width of the boundrect
	 * @param height height of the bound rect
	 * */
	Boundrect(sf::Sprite& sprite, sf::Vector2f offset, float width, float height);
	virtual ~Boundrect();

	//Functions
	 //Accessors 
	 /**
	  * @brief Moves the sprite by some distance
	  * @param pos distance to be moved
	  * */
	 void move(sf::Vector2f pos);

	 /**
	  * @brief For getting the floatrect of the bound
	  * @return returns an object of type sf::FloatRect
	  * */
	 sf::FloatRect getfloatrect() { return rectbound; }
	
	 //Update Functions
	 /***
	  * @brief Updates the boundrect with respect to sprite position
	 */
	 void update();

	 //Render Functions
	 /**
	  * @brief Renders the boundrect to the Target
	  * @param Target Target on which bound is rendered
	  * */
	 void render(sf::RenderTarget* Target);
};
#endif