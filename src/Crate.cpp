#include "Crate.h"
#include "Crate.h"
#include <iostream>

/////////////////////////////////// CONSTRUCTOR FUNCTION ////////////////////////////////////////////

Crate::Crate(float x, float y, float gridsize, sf::Texture& texture, sf::IntRect& texturerect, Tiletype type)\
            : Tile(x,y,gridsize,texture,texturerect,type)
{
	boundrect = new Boundrect(tilesprite, sf::Vector2f(0, 0), gridsize, gridsize);
}

/////////////////////////////////// FUNCTIONS ////////////////////////////////////////////

void Crate::accept(Visitor* v)
{
	v->visitCrate(this);
}

