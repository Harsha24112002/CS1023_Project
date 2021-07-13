#include "Tile.h"

Tile::Tile(float x,float y,float gridsize,sf::Texture& texture,sf::IntRect& texturerect,int type,bool collision)
{
	//tile.setSize(sf::Vector2f(gridsize,gridsize));
	tilesprite.setPosition(x,y);
	tilesprite.setColor(sf::Color::White);
	tilesprite.setTexture(texture);
	tilesprite.setTextureRect(texturerect);

	this->gridsize=gridsize;
	this->texturerect=texturerect;
	this->type=type;
	this->collision=collision;

	boundrect = new Boundrect(tilesprite,sf::Vector2f(0,0),gridsize,gridsize);
}
Tile::Tile()
{
	type=0;
	collision=false;
}

Tile::~Tile()
{

}

collider Tile::getcollider()
{
	return collider(*boundrect);
}
std::ostream& operator<<(std::ostream& os,Tile t)
{
	os<< t.tilesprite.getPosition().x <<" "<<t.tilesprite.getPosition().y<<" "<<t.texturerect.left<<" "<<t.texturerect.top<<\
	" "<<t.type <<" "<< t.collision;

	return os;
}
bool Tile::getcollision()
{
	return collision;
}
void Tile::update()
{
	if(boundrect)
	boundrect->update();
}

void Tile::render(sf::RenderTarget* target)
{
	if(target)
	{
		target->draw(tilesprite);
	}
	if(boundrect)
	{
		boundrect->render(target);
	}
}