#ifndef MOVEMENTSTRATEGY_H
#define MOVEMENTSTRATEGY_H

#include <SFML/Graphics.hpp>

class Movementstrategy
{
	public:
	virtual void update(const float dt,sf::Vector2f& velocity,sf::Vector2f direction)=0;
};

#endif