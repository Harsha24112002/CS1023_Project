#ifndef POWERUP2_H
#define POWERUP2_H

#include "Tile.h"
#include "Visitor.h"

class Powerup2 : public Tile
{
public:
	//Constructor, Destructor 
	Powerup2(float x, float y, float gridsize, sf::Texture& texture, sf::IntRect& texturerect, Tiletype type);
	virtual ~Powerup2(){};

	//Function
	void accept(Visitor* v);
};
#endif