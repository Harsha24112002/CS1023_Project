#ifndef ENEMY_H
#define ENEMY_H

#include "Player.h"

class Enemy
{
	private:
	Boundrect* bound;
	animation* a;
	sf::Sprite enemy;
	sf::Vector2f velocity;
	sf::Vector2f position;
	sf::Texture* t;

	public:
	Enemy(float x,float y,sf::Texture* tex);
	
	collider getcollider(){return collider(*bound);}
	void update(float dt);
	void render(sf::RenderTarget* target);


};


#endif