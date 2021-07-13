#include<SFML/Graphics.hpp>
#include "Bound_Rect.h"
#include "Tile.h"
#ifndef COLLIDER_H
#define COLLIDER_H
class collider
{
    public:
    collider(Boundrect& rect):rect(rect){}
    bool checkcollision(collider& body2,sf::Vector2f&,float);
    sf::FloatRect getfloatrect(){return rect.getfloatrect();}
   /* sf::Vector2f getsize(){return sf::Vector2f(rect.getTextureRect().width/2.0f,sprite.getTextureRect().height/2.0f);}
    sf::Vector2f getpos(){return rect.getPosition();}
    sf::FloatRect getglobalbounds(){return rect.getGlobalBounds();}*/
    void move(sf::Vector2f a){return rect.move(a);}
    private:
    Boundrect& rect;
};
#endif