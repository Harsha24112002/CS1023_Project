#include "Enemy.h"

/////////////////////////////////// CONSTRUCTOR FUNCTIONS ////////////////////////////////////////////

Enemy::Enemy(float x,float y,sf::Texture* tex)
{
	this->t =tex;
	velocity.x=50;
	velocity.y=0;
	position.x=x;
	position.y=y;
	a=new animation(t,sf::Vector2f(3,9),0.15);
	enemy.setTexture(*t);
	enemy.setTextureRect(a->r);
	enemy.setPosition(position);
        this->bound = new Boundrect(enemy, sf::Vector2f(13, 16), 41, 65);

	dead = false;
	squeezed = false;
	squeezetime = 0.0;
}

/////////////////////////////////// ACCESSOR FUNCTIONS ////////////////////////////////////////////

bool Enemy::isdead()
{
	return dead;
}

bool Enemy::issqueezed()
{
	return squeezed;
}

void Enemy::makedead()
{
	dead =true;
}

/////////////////////////////////// UPDATE FUNCTIONS ////////////////////////////////////////////

void Enemy::update(float dt)
{
	if(!dead)
	{
	if (velocity.x > 0.0f)
	{
      
        enemy.setScale(1, 1);
        enemy.setOrigin(0, 0);
	}
    	if (velocity.x < 0.0f)
    	{
     
        enemy.setScale(-1, 1);
       enemy.setOrigin(62, 0);
    	}
	bound->update();
	a->update(1,velocity.x/abs(velocity.x),dt);
	enemy.setTextureRect(a->r);
	if(abs(position.x-enemy.getPosition().x)>80)
	{
		velocity = -velocity;
	}
	enemy.move(velocity*dt);
	}
	if(dead)
	{
		a->update(8,abs(velocity.x)/velocity.x,dt);
		enemy.setTextureRect(a->r);
		squeezetime+=dt;
		if(velocity.x>0)
		{
		enemy.setScale(1,1-4*squeezetime);
		}
		else
		{
		enemy.setScale(-1,1-4*squeezetime);	
		}
		enemy.setPosition(enemy.getPosition().x,position.y+enemy.getLocalBounds().height*4*squeezetime);
		if(squeezetime > 0.2)
		{	
			squeezed = true;
			squeezetime = 0;

		}
		bound->update();

	}
}

/////////////////////////////////// RENDER FUNCTIONS ////////////////////////////////////////////

void Enemy::render(sf::RenderTarget* target)
{
	target->draw(enemy);
	bound->render(target);
}