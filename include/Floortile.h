#ifndef FLOORTILE_H
#define FLOORTILE_H

#include "Tile.h"
#include "Visitor.h"

class Floortile : public Tile
{
public:
	//Constructor, Destructor 
	Floortile(float x, float y, float gridsize, sf::Texture& texture, sf::IntRect& texturerect, Tiletype type);
	virtual ~Floortile(){};

	//Function
	void accept(Visitor* v);
};

#endif