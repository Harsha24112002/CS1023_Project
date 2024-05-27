#include "Water.h"
#include <iostream>

/////////////////////////////////// CONSTRUCTOR FUNCTIONS ////////////////////////////////////////////

Water::Water(float x, float y, float gridsize, sf::Texture& texture, sf::IntRect& texturerect, Tiletype type)\
            : Tile(x,y,gridsize,texture,texturerect,type)
{
	Tile::tilesprite.setColor(sf::Color(255,255,255,128));
	boundrect = new Boundrect(tilesprite, sf::Vector2f(0, 0), gridsize, gridsize);
}

/////////////////////////////////// FUNCTIONS ////////////////////////////////////////////

void Water::accept(Visitor* v)
{
	v->visitWater(this);
}
