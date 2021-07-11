#ifndef TILEMAP_H
#define TILEMAP_H

#include "Tile.h"

class Tilemap
{
private:
	std::vector<std::vector<std::vector<Tile*>>> map ;
	unsigned layers;
	sf::Vector2f mapsize;
	unsigned gridsizeu;
	float gridsizef;
	sf::Texture texture;

public:
	Tilemap(float gridsize,float width,float height);
	~Tilemap();
	void update();
	void render(sf::RenderTarget* target);
	void addtile(unsigned x,unsigned y,unsigned z,sf::IntRect& texturerect);
	void removetile(unsigned x,unsigned y ,unsigned z);
};

#endif