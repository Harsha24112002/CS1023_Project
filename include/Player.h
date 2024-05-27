#ifndef PLAYER_H
#define PLAYER_H

#define SWITCHTIME 0.15
#define PBOUNDOFFSET sf::Vector2f(-23, -23)
#define PBOUNDWIDTH 45
#define PBOUNDHEIGHT 70
#define FULLHP 100
#define JUMPHEIGHT 175
#define ACCLERATION 500
#define MAXSPEED 300
#define DECELARATION -100
#define BOTTOMMOST 9000
#define P2TIME 7
#define SHIELDTIME 5
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
#include "Floormovement.h"
#include "Icymovement.h"
class Player 
{
private:
    //variables
     //sf Variables
     sf::Vector2f velocity;
     sf::Vector2f nimages;
     sf::Texture t;
     sf::SoundBuffer coin_buffer, water_buffer, powerup_buffer;

     //Accessors
     bool rightface;
     int row;
     bool canjump;
	bool shield;
     float jumpheight;
     unsigned coins;
     float health;
     bool levelover;
     bool onice;
     bool powerup2;
    Movementstrategy* Floor;
    Movementstrategy* Icy;
     //Time Variables
     float time;
     float switchtime;
     float dt;
     float powerup2time;
     float shieldtime; 
     //Objects
     animation* a;
    
    //Init Functions
    void initvariables();
    void initSounds();
    /**
     * @brief Creates Bounded rectangle around the player
     * */
    void createBoundrect();

protected:
  
    //sf Variables
    sf::Sprite sprite;

    //Objects
    Boundrect* rect;

public:
    //Constructor, Destructor
    Player(sf::Texture);
    ~Player();
	
	sf::Sound coin, water, powerup;
    
    //Functions
    
	void powerupSound();
    
    //Update and Render Functions
    /**
     * @brief Updates the player movement,Powerup times.
     * @param dt deltatime
     * */
    void update(const float& dt);
    /** 
     * @brief Sets the current velocity
     * @param dt deltatime
     * @param direction direction of movement
     * */
    void move(float dt, sf::Vector2f direction);
    /**
     * @brief Renders the player to the target
     * @param target Target on which player is to be rendered
     * */
	void render(sf::RenderTarget* target);

    /**
     * Attribute Functions
     * */
	void equipShield();
    void equipcoin();
    void onwater();
    void hitenemy();
    void switchmove();
    bool getice();
    float gethealth();
    int getcoins();
    void revive();
    bool IslevelOver();
    void Newlevel();
    void Jumphigh();
    bool catchedpowerup2();
    float getpowerup2time();
    bool hasshield();
    float getshieldtime();
    collider getcollider(){return collider(*rect);}
    void oncollision(sf::Vector2f& fromwhere);
    void makelevelover();
	void makePlayerDead();
    bool IsGameOver();

    sf::Vector2f getposition() {return sprite.getPosition(); }
    float getjumpheight(){return jumpheight;}
   
    //friend class Collisionvisitor;
    
};
#endif
