#include "Player.h"
#include <math.h>
Player::Player(sf::Texture tex)
{
   
    this->t=tex;
    this->sprite.setTexture(t);
    this->initvariables();
}
void Player::initvariables()
{
    this->sprite.setPosition(sf::Vector2f(200,600));
    this->nimages.x=3;
    this->nimages.y=9;
    this->switchtime=0.25f;
    this->a= new animation(&t,this->nimages,this->switchtime);
    this->jumpheight=100.0f;
    
    this->row=0;
    this->canjump=false;
    this->rightface=true;
    this->velocity.x=0;
    this->velocity.y=0;
    this->acceleration.x=300;
    this->maxspeed=250.0f;
    this->createBoundrect();
    this->deceleration=-500;
}
void Player::move(float dt,sf::Vector2f direction)
{  
    
    if(direction.x>0.5f)
    {
       if(velocity.x>=0)
       {
        if(velocity.x<maxspeed)
        velocity.x+=acceleration.x*dt;
        else velocity.x=maxspeed*direction.x;
       }
       if(velocity.x<0)
       {
           velocity.x-=deceleration*dt;
       }
    }
    if(direction.x<-0.5f)
    {
        if(velocity.x<=0)
        {
        if(velocity.x>-maxspeed)
        {
            velocity.x-=acceleration.x*dt;
        }
        else velocity.x=maxspeed*direction.x;
        }
        if(velocity.x>0)
        {
            velocity.x+=deceleration*dt;
        }

    }
    
    if(direction.x==0.0f)
    {
        if(velocity.x>0.0f)
        {
            velocity.x+=deceleration*dt;
            if(velocity.x<0.0f)
            {
                velocity.x=0.0f;
                
            }
        }
        else if(velocity.x<0.0f)
        {
            velocity.x-=deceleration*dt;
            if(velocity.x>0.0f)
            {
                velocity.x=0.0f;
            }
        }

        if(velocity.x==0)
        {
            row=0;
        }
     
    }
    if(velocity.x>0.0f)
    {
        row=1;
        sprite.setScale(1,1);
        sprite.setOrigin(0,0);
       
    }
    if(velocity.x<0.0f)
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
   if(canjump)
   {
       canjump=false;              
   }
   
  
}
void Player::createBoundrect()
{
    this->rect=new Boundrect(sprite,sf::Vector2f(-23,-23),42,63);
}
void Player::oncollision(sf::Vector2f& fromwhere)
{
    if(fromwhere.y<0)
    {
        velocity.y=0;
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