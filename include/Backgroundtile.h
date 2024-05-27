#ifndef BACKGROUNDTILE_H
#define BACKGROUNDTILE_H

#include "Tile.h"

#include "Visitor.h"

class Backgroundtile : public Tile
{
public:
	//Constructor, Destructor 
	Backgroundtile(float x, float y, float gridsize, sf::Texture& texture, sf::IntRect& texturerect, Tiletype type);
	virtual ~Backgroundtile(){};

	//Function
	void accept(Visitor* v);
};

#endif