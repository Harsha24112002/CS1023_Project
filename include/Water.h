#ifndef WATER_H
#define WATER_H

#include "Tile.h"
#include "Visitor.h"
#include <iostream>

class Water : public Tile
{
public:
	//Constructor, Destructor
	Water(float x, float y, float gridsize, sf::Texture& texture, sf::IntRect& texturerect, Tiletype type);
	virtual ~Water(){}
	
	//Functions
	void accept(Visitor* v);
	//void update(){std::cout<<"Nenu coin ni"<<std::endl;}
};

#endif