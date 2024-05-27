#include "Icytile.h"
#include <iostream>

/////////////////////////////////// CONSTRUCTOR FUNCTION ////////////////////////////////////////////

Icytile::Icytile(float x, float y, float gridsize, sf::Texture& texture, sf::IntRect& texturerect, Tiletype type)\
            : Tile(x,y,gridsize,texture,texturerect,type)
{
	boundrect = new Boundrect(tilesprite, sf::Vector2f(0, 0), gridsize, gridsize);
}

/////////////////////////////////// FUNCTIONS ////////////////////////////////////////////

void Icytile::accept(Visitor* v)
{
	v->visitIce(this);
}