#include "Floormovement.h"

void Floormovement::update(const float dt,sf::Vector2f& velocity,sf::Vector2f direction)
{
	if(direction.x>0)
	{
		velocity.x = MAXSPEED;
	}
	else if(direction.x<0)
	{
		velocity.x = -MAXSPEED;
	}
	else if(direction.x ==0)
	{
		velocity.x = 0;
	}
}