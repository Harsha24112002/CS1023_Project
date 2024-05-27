#ifndef COIN_H
#define COIN_H

#include "Tile.h"
#include "Visitor.h"
#include <iostream>


#define COINSCALE 1
class Coin : public Tile
{
public:
	//Constructor, Destructor
	Coin(float x, float y, float gridsize, sf::Texture& texture, sf::IntRect& texturerect, Tiletype type);
	virtual ~Coin(){}

	//Functions
	void accept(Visitor* v);
	
};

#endif