#include "Bound_Rect.h"
#include "Tile.h"

#ifndef COLLIDER_H
#define COLLIDER_H

class collider
{
private:
    //Object
    Boundrect& rect;

public:
    //Constructor
    /**
     * @brief Constructor for collider
     * @param rect Boundrect to be compatible with collider
     * */
    collider(Boundrect& rect):rect(rect){}

    //Functions
     //Accessors
     /**
      * @brief Stops the collision
      * @param body2 Another body which is colliding
      * @param direction The direction of collision is stored in it
      * @param push Specifies how much body1 is movable
      * @return returns true if there is collision otherwise false
      * */
     bool stopcollision(collider& body2,sf::Vector2f& direction,sf::Vector2f push);
     /***
      * @brief checks for collision
      * @param body2 Another body which is colliding
      * @return returns true if there is collision otherwise false
      * */
     bool checkcollision(collider&);

    /**
	  * @brief For getting the floatrect of the bound
	  * @return returns an object of type sf::FloatRect
	  * */
    sf::FloatRect getfloatrect(){return rect.getfloatrect();}
     /**
	  * @brief Moves the sprite by some distance
	  * @param pos distance to be moved
	  * */
    void move(sf::Vector2f pos){return rect.move(pos);}

};
#endif