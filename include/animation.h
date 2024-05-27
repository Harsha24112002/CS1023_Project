#ifndef ANIMATION_H
#define ANIMATION_H

#include <SFML/Graphics.hpp>
#include <iostream>

class animation
{
private:
    //Variables
     //Accessors
     float switchtime;
     float totaltime;
     bool rightface;

     //sf Variables
     sf::Vector2f currentimage;
     sf::Vector2f nofimages;
     sf::Texture* texture;
public:
    //Constructor, Destructor
    /**
     * @brief Constructor for animation
     * @param tex texturesheet of the animation
     * @param nimages number of images along x and y axes
     * @param stime switch time for the animation
     * */
    animation(sf::Texture* tex, sf::Vector2f nimages, float stime);
    virtual ~animation();

    //Variables
    sf::Rect<int> r;

     //Update Functions
     /***
      * @brief Updates the current texture rect on the sprite(row -wise)
      * @param row row of the texture sheet 
      * @param direction direction facing
      * @param deltatime deltatime
      * */ 
     void update(int row, int direction, float deltatime);
};
#endif