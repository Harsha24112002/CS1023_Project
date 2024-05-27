#ifndef CRATE_H
#define CRATE_H

#include "Tile.h"
#include "Visitor.h"

class Crate : public Tile
{
public:
	//Constructor, Destructor 
	Crate(float x, float y, float gridsize, sf::Texture& texture, sf::IntRect& texturerect, Tiletype type);
	virtual ~Crate(){};

	//Function
	void accept(Visitor* v);
};

#endif