#ifndef ICYTILE_H
#define ICYTILE_H
#include "Tile.h"
#include "Visitor.h"
class Icytile : public Tile
{
public:
	//Constructor, Destructor 
	Icytile(float x, float y, float gridsize, sf::Texture& texture, sf::IntRect& texturerect, Tiletype type);
	virtual ~Icytile(){};

	//Function
	void accept(Visitor* v);
};

#endif