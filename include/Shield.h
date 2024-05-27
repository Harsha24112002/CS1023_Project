#ifndef SHIELD_H
#define SHIELD_H

#include "Tile.h"
#include "Visitor.h"
#include <iostream>

class Shield : public Tile
{
public:
	//Constructor, Destructor
	Shield(float x, float y, float gridsize, sf::Texture& texture, sf::IntRect& texturerect, Tiletype type);
	virtual ~Shield() {}

	//Functions
	void accept(Visitor* v);

};

#endif

