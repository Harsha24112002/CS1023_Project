#include "Player.h"
#include <math.h>
#define PLAYERPOS sf::Vector2f(150, -180)
#define ACCGRAVITY 1000
/////////////////////////////////// INITILIZER FUNCTIONS ////////////////////////////////////////////

void Player::initvariables()
{
    levelover = false;
    Floor = new Floormovement();
    Icy = new Icymovement();
    onice = false;
    this->coins = 0;
    this->health = FULLHP;
    this->time = 0.0;
    powerup2 = false;
    powerup2time = P2TIME;
    shieldtime = SHIELDTIME;
    this->nimages.x = 3;
    this->nimages.y = 9;
    this->switchtime = SWITCHTIME;
    this->shield = false;

    this->sprite.setTexture(t);
    sprite.setScale(1.25, 1.25);
    this->a = new animation(&t, this->nimages, this->switchtime);
    this->sprite.setTextureRect(a->r);
    this->sprite.setPosition(PLAYERPOS);


    this->jumpheight = JUMPHEIGHT;

    this->row = 0;
    this->canjump = false;
    this->rightface = true;
    this->velocity.x = 0;
    this->velocity.y = 0;
    this->createBoundrect();
}

void Player::initSounds()
{
    if (!coin_buffer.loadFromFile("assets/Audio/Coin.wav"))
        throw("ERROR::PAUSE_MENU_STATE::COULT NOT LOAD SOUND");

    this->coin.setBuffer(coin_buffer);

    if (!water_buffer.loadFromFile("assets/Audio/Water.wav"))
        throw("ERROR::PAUSE_MENU_STATE::COULT NOT LOAD SOUND");

    this->water.setBuffer(water_buffer);

    if (!powerup_buffer.loadFromFile("assets/Audio/Power-up.wav"))
        throw("ERROR::PAUSE_MENU_STATE::COULT NOT LOAD SOUND");

    this->powerup.setBuffer(powerup_buffer);
    
    this->coin.setVolume(70);
    this->water.setVolume(70);
    this->powerup.setVolume(70);
}

/////////////////////////////////// CONSTRUCTOR AND DESTRUCTOR FUNCTIONS ////////////////////////////////////////////

Player::Player(sf::Texture tex)
{

    this->t = tex;
    this->initvariables();
    this->initSounds();
}

Player::~Player()
{
    delete rect;
    delete a;
}

/////////////////////////////////// ACCESSOR FUNCTIONS ////////////////////////////////////////////

void Player::equipShield()
{
    this->shield = true;
    shieldtime = SHIELDTIME;
}
bool Player::hasshield()
{
    return shield;
}
float Player::getshieldtime()
{
    return shieldtime;
}
void Player::equipcoin()
{
    coins++;
    this->coin.play();
}

void Player::onwater()
{
    if(!shield)
    {
    health -=0.5;
    this->water.play();
    }
}
float Player::gethealth()
{
    return health;
}
int Player::getcoins()
{
    return coins;
}
void Player::hitenemy()
{
    if(time>0.3)
    {    
    health-=25;
    time=0;
    }
}
void Player::switchmove()
{
    if(onice)
    {
     onice=false;
    }
    else onice =true;
}
bool Player::getice()
{
    return onice;
}
void Player::revive()
{
    health = FULLHP;
}
void Player::Jumphigh()
{
    powerup2time = P2TIME;
    powerup2 = true;
    jumpheight = 1.5* JUMPHEIGHT;
}
bool Player::catchedpowerup2()
{
    return powerup2;
}
float Player::getpowerup2time()
{
    return powerup2time;
}
void Player::makelevelover()
{
    levelover = true;
}
void Player::makePlayerDead()
{
    this->health = 0;
}
void Player::move(float dt, sf::Vector2f direction)
{
    this->dt = dt;
   
   if(onice)
   {
       Icy->update(dt,velocity,direction);
   }
   if(!onice)
   {
       Floor->update(dt,velocity,direction);
   }

        if (velocity.x == 0)
        {
            row = 0;
        }

    
    if (velocity.x > 0.0f)
    {
        row = 1;
        sprite.setScale(1.25, 1.25);
        sprite.setOrigin(0, 0);

    }
    if (velocity.x < 0.0f)
    {
        row = 1;
        sprite.setScale(-1.25, 1.25);
        sprite.setOrigin(-188, 0);
    }

    if (canjump)
    {
        if (direction.y < 0)
        {
            canjump = false;
            velocity.y = -sqrt(2 * ACCGRAVITY * jumpheight);
        }
    }
    a->update(row, (int)direction.x, dt);

    if (canjump == false)
    {
        velocity.y += ACCGRAVITY * dt;
    }
    if (canjump)
    {
        velocity.y = 0;
        canjump = false;
    }

}
void Player::createBoundrect()
{
    this->rect = new Boundrect(sprite, PBOUNDOFFSET, PBOUNDWIDTH, PBOUNDHEIGHT);
}
void Player::powerupSound()
{
    this->powerup.play();
}
void Player::oncollision(sf::Vector2f& fromwhere)
{
    if (fromwhere.y < 0)
    {
        velocity.y = 0;
    }
    else if (fromwhere.y > 0)
    {
        canjump = true;
        velocity.y = 0;
    }
}

bool Player::IslevelOver()
{
    return levelover;
}

void Player::Newlevel()
{
    levelover = false;
    this->sprite.setPosition(PLAYERPOS);
    velocity.x = 0;
    velocity.y = 0;
}

bool Player::IsGameOver()
{
    /*
        - Checks if the player is fallen or not.
        - If player has fallen then return true to the IsGameOver.
    */
    if(health<=0)
    {
        return true;
    } 
    if (this->sprite.getPosition().y < BOTTOMMOST)
        return false;
    else
        return true;
}

/////////////////////////////////// UPDATE FUNCTIONS ////////////////////////////////////////////

void Player::update(const float& dt)
{
    if (levelover)
    {
        this->sprite.setPosition(PLAYERPOS);
    }

    time+=dt;
   
    if(powerup2)
    {
        powerup2time -= dt;
    
    if(powerup2time<=0)
    {
        powerup2 =false;
        jumpheight = JUMPHEIGHT;
    }
    }
    if(shield)
    {
        shieldtime -= dt;
        if(shieldtime<=0)
        {
            shield = false;
        }
    }
    this->sprite.setTextureRect(a->r);
    this->sprite.move(this->velocity * dt);
    sprite.setOrigin(sf::Vector2f((double)(a->r.width) / 2.0, (double)(a->r.height) / 2.0));

    this->rect->update();
}

/////////////////////////////////// RENDER FUNCTIONS ////////////////////////////////////////////

void Player::render(sf::RenderTarget* target)
{
    target->draw(this->sprite);
    rect->render(target);
}
