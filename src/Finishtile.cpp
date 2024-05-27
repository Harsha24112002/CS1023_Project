#include "Finishtile.h"
#include <iostream>

/////////////////////////////////// CONSTRUCTOR FUNCTIONS ////////////////////////////////////////////

Finishtile::Finishtile(float x, float y, float gridsize, sf::Texture& texture, sf::IntRect& texturerect, Tiletype type)\
	: Tile(x, y, gridsize, texture, texturerect, type)
{
	boundrect = new Boundrect(tilesprite, sf::Vector2f(0, 0), gridsize, gridsize);
	tilesprite.setColor(sf::Color::Red);
}

/////////////////////////////////// FUNCTIONS ////////////////////////////////////////////

void Finishtile::accept(Visitor* v)
{
	 v->visitFinish(this);
}