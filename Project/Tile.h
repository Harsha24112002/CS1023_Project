#ifndef TILE_H
#define TILE_H
#include <SFML/Graphics.hpp>
#include "collider.h"
#include "Bound_Rect.h"
class Tile
{
private:

	sf::Sprite tilesprite;
	bool collision;
	Boundrect* boundrect;
	float gridsize;
	sf::IntRect texturerect;
	int type;
public:
	Tile();
	Tile(float x, float y, float gridsize, sf::Texture& texture, sf::IntRect& texturerect, int type, bool collison);
	virtual ~Tile();

	friend std::ostream& operator<<(std::ostream& out, Tile);
	virtual collider getcollider();
	int gettype();
	bool getcollision();
	virtual void update(float dt);
	virtual void render(sf::RenderTarget* target);
};


#endif