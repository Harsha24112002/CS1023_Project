#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <sstream>
#include <fstream>
#include <stack>
#include <map>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include "animation.h"
#include "collider.h"
#include "Bound_Rect.h"

class obstacle
{
private:
    //sf Variables
    sf::Texture t;
    sf::Sprite sprite;

    //Objects
    Boundrect* rect;

public:
    //Constructor, Destructor
    obstacle(sf::Texture,sf::Vector2f);
    ~obstacle();

    //Functions
    void createBoundRect();
    collider getcollider(){return collider(*rect);}
    sf::Vector2f getposition(){return sprite.getPosition();}

     //Update, move and Render Functions
     void update(float dt);
     void move(float dt,sf::Vector2f a){};
     void render(sf::RenderTarget& window);
};
#endif