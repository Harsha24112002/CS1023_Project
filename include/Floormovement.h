#ifndef FLOORMOVEMENT_H
#define FLOORMOVEMENT_H
#include "Movementstrategy.h"
#include "Player.h"
class Floormovement : public Movementstrategy
{
	public:
	void update(const float dt,sf::Vector2f& velocity,sf::Vector2f direction);
};



#endif