#ifndef FINISHTILE_H
#define FINISHTILE_H

#include "Tile.h"
#include "Visitor.h"

class Finishtile : public Tile
{
public:
	//Constructor, Destructor
	Finishtile(float x, float y, float gridsize, sf::Texture& texture, sf::IntRect& texturerect, Tiletype type);
	virtual ~Finishtile() {};
	
	//Functions
	void accept(Visitor* v);
};

#endif