#include "Coin.h"
#include <iostream>

/////////////////////////////////// CONSTRUCTOR FUNCTION ////////////////////////////////////////////

Coin::Coin(float x, float y, float gridsize, sf::Texture& texture, sf::IntRect& texturerect, Tiletype type)\
            : Tile(x,y,gridsize,texture,texturerect,type)
{
	tilesprite.setScale(COINSCALE,COINSCALE);
	tilesprite.setPosition(x+((1-COINSCALE)/2)*gridsize,y+((1-COINSCALE)/2)*gridsize);
	boundrect = new Boundrect(tilesprite, sf::Vector2f(0, 0),COINSCALE*gridsize, COINSCALE*gridsize);
}

/////////////////////////////////// FUNCTIONS ////////////////////////////////////////////

void Coin::accept(Visitor* v)
{
	return v->visitCoin(this);
}
