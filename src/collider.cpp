#include "collider.h"
#include<iostream>

/////////////////////////////////// ACCESSOR FUNCTIONS ////////////////////////////////////////////

bool collider::checkcollision(collider& body2)
{
    sf::FloatRect tile = rect.getfloatrect();
    sf::FloatRect player = body2.getfloatrect();
    if(tile.intersects(player))
    {
        return true;
    }
    return false;
}

bool collider::stopcollision(collider& body2, sf::Vector2f& fromwhere, sf::Vector2f howmuchmovable)
{
    sf::FloatRect tile = rect.getfloatrect();
    sf::FloatRect player = body2.getfloatrect();
    float deltax = (tile.left + (tile.width / 2.0f)) - (player.left + (player.width / 2.0f));
    float deltay = (tile.top + (tile.height / 2.0f)) - (player.top + (player.height / 2.0f));
    float intersectx = abs(deltax) - ((tile.width + player.width) / 2.0f);
    float intersecty = abs(deltay) - ((tile.height + player.height) / 2.0f);

    howmuchmovable.x = std::max(0.0f, std::min(1.0f, howmuchmovable.x));
    howmuchmovable.y = std::max(0.0f, std::min(1.0f, howmuchmovable.y));
    if (intersectx < 0 && intersecty < 0)
    {

        if (abs(intersectx) <= abs(intersecty))
        {
            if (deltax > 0.0f)
            {
                rect.move(sf::Vector2f((1.0f - howmuchmovable.x) * (-intersectx), 0));
                body2.move(sf::Vector2f((howmuchmovable.x) * (intersectx), 0));
                if (intersectx < 0)
                {
                    fromwhere.x = 1.0f;
                }
            }
            if (deltax < 0.0f)
            {
                rect.move(sf::Vector2f((1.0f - howmuchmovable.x) * intersectx, 0));
                body2.move(sf::Vector2f((howmuchmovable.x) * (-intersectx), 0));
                if (intersectx < 0)
                {
                    fromwhere.x = -1.0f;
                }
            }
        }
        if (abs(intersectx) > abs(intersecty))
        {
            if (deltay > 0.0f)
            {

                rect.move(sf::Vector2f(0, ((1.0f - howmuchmovable.y) * (-intersecty))));
                body2.move(sf::Vector2f(0, (howmuchmovable.y) * ((intersecty))));
                if (intersecty < 0)
                {
                    fromwhere.y = 1.0f;
                }

            }

            if (deltay < 0.0f)
            {

                rect.move(sf::Vector2f(0, ((1.0f - howmuchmovable.y) * intersecty)));
                body2.move(sf::Vector2f(0, (howmuchmovable.y) * ((-intersecty))));
                if (intersecty < 0)
                {
                    fromwhere.y = -1.0f;
                }

            }
        }
        if (intersectx <= 0 && intersecty <= 0)
        {
            return true;
        }

    }
    return false;
}