
#include "Player.h"
#include <math.h>
Player::Player(sf::Texture tex)
{

    this->t = tex;
    this->initvariables();
}

Player::~Player()
{
    delete rect;
    delete a;
}

void Player::initvariables()
{
    this->coins=0;
    this->health=100;
    this->time = 0;
    this->nimages.x = 3;
    this->nimages.y = 9;
    this->switchtime = 0.15f;

    this->sprite.setTexture(t);
    sprite.setScale(1.25, 1.25);
    this->a = new animation(&t, this->nimages, this->switchtime);
    this->sprite.setTextureRect(a->r);
    this->sprite.setPosition(sf::Vector2f(460, 250));

    
    this->jumpheight = 100.0f;

    this->row = 0;
    this->canjump = false;
    this->bounceup = false;
    this->rightface = true;
    this->velocity.x = 0;
    this->velocity.y = 0;
    this->acceleration.x = 500;
    this->maxspeed = 300.0f;
    this->createBoundrect();
    this->deceleration = -500;
}

void Player::equipcoin()
{
    coins++;
}

void Player::onspikes()
{
    std::cout<<"Health : "<<health<<std::endl;
    health -=0.5;
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
void Player::move(float dt, sf::Vector2f direction)
{
    this->dt = dt;
    if (direction.x > 0.5f)
    {
        if (velocity.x >= 0)
        {
            if (velocity.x < maxspeed)
                velocity.x += acceleration.x * dt;
            else velocity.x = maxspeed * direction.x;
        }
        if (velocity.x < 0)
        {
            velocity.x -= deceleration * dt;
        }
    }
    if (direction.x < -0.5f)
    {
        if (velocity.x <= 0)
        {
            if (velocity.x > -maxspeed)
            {
                velocity.x -= acceleration.x * dt;
            }
            else velocity.x = maxspeed * direction.x;
        }
        if (velocity.x > 0)
        {
            velocity.x += deceleration * dt;
        }

    }

    if (direction.x == 0.0f)
    {
        if (velocity.x > 0.0f)
        {
            velocity.x += deceleration * dt;
            if (velocity.x < 0.0f)
            {
                velocity.x = 0.0f;

            }
        }
        else if (velocity.x < 0.0f)
        {
            velocity.x -= deceleration * dt;
            if (velocity.x > 0.0f)
            {
                velocity.x = 0.0f;
            }
        }

        if (velocity.x == 0)
        {
            row = 0;
        }

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
            velocity.y = -sqrt(2 * 1000 * 200.0f);
        }
    }
    a->update(row, (int)direction.x, dt);

    if (canjump == false)
    {
        velocity.y += 1000.0f * dt;
    }
    if (canjump)
    {
        canjump = false;
    }

}
void Player::createBoundrect()
{
    this->rect = new Boundrect(sprite, sf::Vector2f(-23, -23), 45, 70);
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

bool Player::IsGameOver()
{
    /*
        - Checks if the player is fallen or not.
        - If player has fallen then return true to the IsGameOver.
    */
    if(health<0)
    {
        return true;
    } 
    if (this->sprite.getPosition().y < 1000)
        return false;
    else
        return true;
}

void Player::update(const float& dt)
{
    time+=dt;
    this->sprite.setTextureRect(a->r);
    this->sprite.move(this->velocity * dt);
    sprite.setOrigin(sf::Vector2f((double)(a->r.width) / 2.0, (double)(a->r.height) / 2.0));

    this->rect->update();

    // text.setPosition(body.getPosition()+sf::Vector2f(406,-512));
     //std::string s="Coins : ";
     //s.append(std::to_string(count));
     //text.setString(s);
}
void Player::render(sf::RenderTarget* target)
{
    target->draw(this->sprite);
    rect->render(target);
}