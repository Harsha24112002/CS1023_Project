#ifndef TILEMAP_H
#define TILEMAP_H

#include "Tile.h"
#include "Player.h"
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
	Tilemap(float gridsize,unsigned width,unsigned height);
	~Tilemap();
	void update();
	sf::Texture* getTilesheet(){return &texture;}
	void render(sf::RenderTarget* target);
	void addtile(unsigned x,unsigned y,unsigned z,sf::IntRect& texturerect,int type,bool collision);
	void removetile(unsigned x,unsigned y ,unsigned z);
	void checkcollison(Player* player,sf::Vector2f& direction);
	void savetofile(std::string& filename);
	void Loadfromfile(std::string& filename);
};

#endif