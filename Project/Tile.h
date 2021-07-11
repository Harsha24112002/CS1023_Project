#ifndef TILE_H
#define TILE_H
#include <SFML/Graphics.hpp>
class Tile
{
private:
	sf::RectangleShape tile;
public:
	Tile();
	Tile(float x,float y,float gridsize,sf::Texture& texture,sf::IntRect& texturerect);
	~Tile();
	void update();
	void render(sf::RenderTarget* target);
};


#endif