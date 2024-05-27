#include "Icymovement.h"

void Icymovement::update(const float dt,sf::Vector2f& velocity,sf::Vector2f direction)
{
	 if (direction.x > 0.5f)
    {
        if (velocity.x >= 0)
        {
            if (velocity.x < MAXSPEED)
                velocity.x += ACCLERATION * dt;
            else velocity.x = MAXSPEED * direction.x;
        }
        if (velocity.x < 0)
        {
            velocity.x -= 2*DECELARATION * dt;
        }
    }
    if (direction.x < -0.5f)
    {
        if (velocity.x <= 0)
        {
            if (velocity.x > -MAXSPEED)
            {
                velocity.x -= ACCLERATION * dt;
            }
            else velocity.x = MAXSPEED * direction.x;
        }
        if (velocity.x > 0)
        {
            velocity.x += 2*DECELARATION * dt;
        }

    }

    if (direction.x == 0.0f)
    {
        if (velocity.x > 0.0f)
        {
            velocity.x += DECELARATION * dt;
            if (velocity.x < 0.0f)
            {
                velocity.x = 0.0f;

            }
        }
        else if (velocity.x < 0.0f)
        {
            velocity.x -= DECELARATION * dt;
            if (velocity.x > 0.0f)
            {
                velocity.x = 0.0f;
            }
        }
    }
}