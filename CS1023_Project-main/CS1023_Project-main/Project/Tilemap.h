#ifndef TILEMAP_H
#define TILEMAP_H
#include "Enemytile.h"
#include "Tile.h"
#include "Player.h"
class Tilemap
{
private:
	std::vector<std::vector<std::vector<Tile*>>> map ;
	sf::Vector2f mapsize;
	unsigned gridsizeu;
	float gridsizef;
	sf::Texture texture;
	sf::Texture enemytex;
	bool checksametype(std::vector<Tile*>,int type);
	int fromX;
	int fromY;
	int toX;
	int toY;
	void clear();
public:
	Tilemap(float gridsize, unsigned width, unsigned height);
	virtual ~Tilemap();
	void update(sf::Vector2i Playergridpos,float dt);
	sf::Texture* getTilesheet() { return &texture; }
	void render(sf::RenderTarget* target);
	void addtile(unsigned x,unsigned y,sf::IntRect& texturerect,int type,bool collision);
	void removetile(unsigned x,unsigned y );
	void checkcollison(Player* player,sf::Vector2f& direction);
	void savetofile(std::string& filename);
	void Loadfromfile(std::string& filename);
};

#endif