#ifndef ICYMOVEMENT_H
#define ICYMOVEMENT_H

#include "Movementstrategy.h"
#include "Player.h"
class Icymovement : public Movementstrategy
{
	public:
	void update(const float dt,sf::Vector2f& velocity,sf::Vector2f direction);
};



#endif
