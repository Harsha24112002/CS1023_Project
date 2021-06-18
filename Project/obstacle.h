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


#ifndef OBSTACLE_H
#define OBSTACLE_H
class obstacle
{
    public:
    obstacle(sf::Texture,sf::Vector2f);
    void createBoundRect();
    collider getcollider(){return collider(*rect);}
    void render(sf::RenderTarget& window);
    void update(float dt);
    void move(float dt,sf::Vector2f a){};
    sf::Vector2f getposition(){return sprite.getPosition();}
    private:
    sf::Texture t;
    sf::Sprite sprite;
    Boundrect* rect;
};
#endif