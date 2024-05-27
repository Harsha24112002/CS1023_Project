#ifndef POISON_H
#define POISON_H

#include "Tile.h"
#include "Visitor.h"
#include <iostream>

class Poison : public Tile
{
public:
	//Constructor, Destructor
	Poison(float x, float y, float gridsize, sf::Texture& texture, sf::IntRect& texturerect, Tiletype type);
	virtual ~Poison() {}

	//Functions
	void accept(Visitor* v);

};

#endif // !POISON_H

