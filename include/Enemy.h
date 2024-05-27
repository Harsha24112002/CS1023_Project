#ifndef ENEMY_H
#define ENEMY_H

#include "Player.h"

class Enemy
{
private:
	//Objects
	Boundrect* bound;
	animation* a;

	//sf Variables
	sf::Sprite enemy;
	sf::Vector2f velocity;
	sf::Vector2f position;
	sf::Texture* t;

	//Accessor Variables
	bool dead;
	bool squeezed;
	float squeezetime;
public:
	//Constructor
	Enemy(float x,float y,sf::Texture* tex);
	
	//Functions
	/**
	 * @brief To wrap a bound to collider 
	 * @return returns an object of type collider
	 * */
	collider getcollider(){return collider(*bound);}
	bool isdead();
	bool issqueezed();
	void makedead();

	//Update and Render Functions
	/**
	 * @brief Updates the Enemy
	 * @param dt deltatime
	 * */
	void update(float dt);
	/**
	 * @brief Renders the Enemy to the target
	 * @param target the target on which enemy is to be rendered
	 * */
	void render(sf::RenderTarget* target);
};

#endif