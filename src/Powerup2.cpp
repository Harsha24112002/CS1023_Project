#include "Powerup2.h"

/////////////////////////////////// CONSTRUCTOR FUNCTION ////////////////////////////////////////////

Powerup2::Powerup2(float x, float y, float gridsize, sf::Texture& texture, sf::IntRect& texturerect, Tiletype type)\
            : Tile(x,y,gridsize,texture,texturerect,type)
{
	boundrect = new Boundrect(tilesprite, sf::Vector2f(0, 0),gridsize, gridsize);
}

/////////////////////////////////// FUNCTIONS ////////////////////////////////////////////

void Powerup2::accept(Visitor* v)
{
	return v->visitPowerup2(this);
}