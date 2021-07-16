
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


#ifndef PLAYER_H
#define PLAYER_H
class Player 
{
    private:

    //variables
    bool rightface;
    sf::Vector2f velocity;
    unsigned time;
    int row;
    bool canjump;
    bool bounceup;
    float jumpheight;
    sf::Vector2f nimages;
    float switchtime;
    float dt;
    animation* a;
    sf::Texture t;
    sf::Vector2f acceleration;
    float maxspeed;
    float deceleration;
    unsigned coins;
    float health;
    void initvariables();

   protected:
  
    sf::Sprite sprite;
    Boundrect* rect;

    public:

    //functions
    Player(sf::Texture);
    ~Player();
    
    void createBoundrect();
    void update(const float& dt);
    void move(float dt,sf::Vector2f velocity);
	void render(sf::RenderTarget* target);

    /**
     * Attribute functions
     * */
    void equipcoin();
    void onspikes();
    float gethealth();
    int getcoins();
    void hitenemy();
    collider getcollider(){return collider(*rect);}
    void oncollision(sf::Vector2f& fromwhere);
    bool IsGameOver();

    sf::Vector2f getposition() {return sprite.getPosition(); }
   
    //coincollect getcollector(){return coincollect(body);}
    
};
#endif