#ifndef POWERUP1_H
#define POWERUP1_H

#include "Tile.h"
#include "Visitor.h"
#include <iostream>

class Powerup1 : public Tile
{
public:
	//Constructor, Destructor
	Powerup1(float x, float y, float gridsize, sf::Texture& texture, sf::IntRect& texturerect, Tiletype type);
	virtual ~Powerup1(){}

	//Functions
	void accept(Visitor* v);
	
};

#endif