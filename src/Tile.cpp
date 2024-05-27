#include "Tile.h"
#include <iostream>

/////////////////////////////////// CONSTRUCTOR AND DESTRUCTOR FUNCTIONS ////////////////////////////////////////////

Tile::Tile(float x, float y, float gridsize, sf::Texture& texture, sf::IntRect& texturerect, Tiletype type)
{
	//tile.setSize(sf::Vector2f(gridsize,gridsize));
	tilesprite.setPosition(x, y);
	tilesprite.setColor(sf::Color::White);
	tilesprite.setTexture(texture);
	tilesprite.setTextureRect(texturerect);
	
	this->gridsize = gridsize;
	this->texturerect = texturerect;
	this->type = type;

	boundrect = nullptr;
	dead =false;

}
Tile::Tile()
{
	type = FLOORTILE;
}

Tile::~Tile()
{
	delete boundrect;
}

/////////////////////////////////// FUNCTIONS ////////////////////////////////////////////

collider Tile::getcollider()
{
	return collider(*boundrect);
}
std::ostream& operator<<(std::ostream& os, Tile t)
{
	os << t.tilesprite.getPosition().x << " " << t.tilesprite.getPosition().y << " " << t.texturerect.left << " " << t.texturerect.top << \
		" " << t.type ;

	return os;
}
int Tile::gettype()
{
	return type;
}

void Tile::maketiledead()
{
	dead =true;
}

bool Tile::istiledead()
{
	return dead;
}
/////////////////////////////////// UPDATE FUNCTIONS ////////////////////////////////////////////

void Tile::update(float dt)
{
	if (boundrect)
		boundrect->update();
}

/////////////////////////////////// RENDER FUNCTIONS ////////////////////////////////////////////

void Tile::render(sf::RenderTarget* target)
{
	if (target)
	{
		target->draw(tilesprite);


		if (boundrect)
		{
			boundrect->render(target);
		}
	}

}