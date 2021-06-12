#include "collider.h"
#include<iostream>
bool collider::checkcollision(collider& body2,sf::Vector2f& fromwhere,float howmuchmovable)
{
    sf::FloatRect tile = rect.getfloatrect();
    sf::FloatRect player=body2.getfloatrect();
    float deltax=(tile.left+(tile.width/2.0f))-(player.left+(player.width/2.0f));
    float deltay= (tile.top+(tile.height/2.0f))-(player.top+(player.height/2.0f));
    float intersectx=abs(deltax)-((tile.width+player.width)/2.0f);
    float intersecty=abs(deltay)-((tile.height+player.height)/2.0f);

    howmuchmovable=std::max(0.0f,std::min(1.0f,howmuchmovable));
    if(intersectx<0 && intersecty<0)
    {
        if(abs(intersectx)<=abs(intersecty))
        {
            if(deltax>0.0f)
            {
            rect.move(sf::Vector2f((1.0f-howmuchmovable)*(-intersectx),0));
            body2.move(sf::Vector2f((howmuchmovable)*(intersectx),0));
            }
            if(deltax<0.0f)
            {
            rect.move(sf::Vector2f((1.0f-howmuchmovable)*intersectx,0));
            body2.move(sf::Vector2f((howmuchmovable)*(-intersectx),0));     
            }
        }
        else if(abs(intersectx)>abs(intersecty))
        {
            if(deltay>0.0f)
            {
               
          //  std::cout<<(1-howmuchmovable)*(-intersecty)<<" : "<<(howmuchmovable)*intersecty<<std::endl;
            rect.move(sf::Vector2f(0,((1.0f-howmuchmovable)*(-intersecty))));
           body2.move(sf::Vector2f(0,(howmuchmovable)*((intersecty))));
            
            }
            
            if(deltay<0.0f)
            {
            rect.move(sf::Vector2f(0,((1.0f-howmuchmovable)*intersecty)));
            body2.move(sf::Vector2f(0,(howmuchmovable)*((-intersecty))));  
         
            }
        }
    
    if(deltax<0)
    {
        fromwhere.x=-1.0f;
    }
    else if(deltax>0)
    {
        fromwhere.x=1.0f;
    }
    if(deltay<0)
    {
        fromwhere.y=-1.0f;
    }
    else if(deltay>0)
    {
        fromwhere.y=1.0f;
    }
    return true;
    }
    
    return false;
}
