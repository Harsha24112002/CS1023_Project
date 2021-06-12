#include "Player.h"
#include <math.h>
Player::Player(sf::Texture tex)
{
   
    this->t=tex;
    this->sprite.setTexture(t);
    //this->sprite.setScale(sf::Vector2f(1.0f));
    this->sprite.setPosition(sf::Vector2f(200,600));
    this->nimages.x=3;
    this->nimages.y=9;
    this->switchtime=0.4f;
    this->a= new animation(&t,this->nimages,this->switchtime);
    this->jumpheight=100.0f;
    this->movementspeed=250.0f;
    this->row=0;
    this->canjump=false;
    this->rightface=true;
    this->velocity.x=0;
    this->velocity.y=0;
     this->createBoundrect();
}
void Player::move(float dt,sf::Vector2f direction)
{  
    this->velocity.x=direction.x*movementspeed;
    
    if(direction.x==0.0f)
    {
        row=0;
     
    }
    if(direction.x>0.0f)
    {
        row=1;
        sprite.setScale(1,1);
        sprite.setOrigin(0,0);
       
    }
    if(direction.x<0.0f)
    {
        row=1;
       sprite.setScale(-1,1);
        sprite.setOrigin(-188,0);
    }
    
    if(canjump)
    {
        if(direction.y<0)
        {
            canjump=false;
            velocity.y=-sqrt(2*1000*150.0f);
        }
    }
    a->update(row,direction.x,dt);
  
   if(canjump==false)
   {
   velocity.y+=1000.0f*dt;
   }
}
void Player::createBoundrect()
{
    this->rect=new Boundrect(sprite,sf::Vector2f(-23,-23),42,61);
}
void Player::oncollision(sf::Vector2f& fromwhere)
{
    if(fromwhere.x<0)
    {
        velocity.x=0;
        canjump=false;
    }
    else if(fromwhere.x>0)
    {
        velocity.x=0;
        canjump=false;
    }
    if(fromwhere.y<0)
    {
        velocity.y=0;
        canjump=false;
    }
    else if(fromwhere.y>0)
    {
        canjump=true;
        velocity.y=0;
    }
}
void Player::update(const float& dt)
{
    
    this->sprite.setTextureRect(a->r);
    this->sprite.move(this->velocity*dt);
    sprite.setOrigin(sf::Vector2f(a->r.width/2,a->r.height/2));
    this->velocity.x=0;
    this->rect->update();
 
   // text.setPosition(body.getPosition()+sf::Vector2f(406,-512));
    //std::string s="Coins : ";
    //s.append(std::to_string(count));
    //text.setString(s);
}
void Player::render(sf::RenderTarget* target)
{
    target->draw(this->sprite);
    rect->render(target);
}