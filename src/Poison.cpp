#include "Poison.h"
#include <iostream>

/////////////////////////////////// CONSTRUCTOR FUNCTION ////////////////////////////////////////////

Poison::Poison(float x, float y, float gridsize, sf::Texture& texture, sf::IntRect& texturerect, Tiletype type)\
	: Tile(x, y, gridsize, texture, texturerect, type)
{
	boundrect = new Boundrect(tilesprite, sf::Vector2f(0, 0), gridsize, gridsize);
}

/////////////////////////////////// FUNCTIONS ////////////////////////////////////////////

void Poison::accept(Visitor* v)
{
	return v->visitPoison(this);
}