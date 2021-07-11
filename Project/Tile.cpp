#include "Tile.h"

Tile::Tile(float x,float y,float gridsize,sf::Texture& texture,sf::IntRect& texturerect)
{
	tile.setSize(sf::Vector2f(gridsize,gridsize));
	tile.setPosition(x,y);
	tile.setFillColor(sf::Color::White);
	tile.setTexture(&texture);
	tile.setTextureRect(texturerect);
}
Tile::Tile()
{

}

Tile::~Tile()
{

}
void Tile::update()
{

}

void Tile::render(sf::RenderTarget* target)
{
	if(target)
	{
		target->draw(tile);
	}
}