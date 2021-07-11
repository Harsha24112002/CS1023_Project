#include "Tilemap.h"

Tilemap::Tilemap(float gridsize,float width,float height)
{
	this->gridsizeu=(unsigned)gridsize;
	this->gridsizef =gridsize;
	this->mapsize.x=width;
	this->mapsize.y=height;
	this->layers=1;
	this->texture.loadFromFile("Resources/floortileset.png");
	for(unsigned x=0;x<mapsize.x;x++)
	{
		map.resize(mapsize.x,(std::vector<std::vector<Tile*>>()));
		for(unsigned y=0;y<mapsize.y;y++)
		{
			
		map[x].resize(mapsize.y,std::vector<Tile*>());
		for(unsigned z=0;z<layers;z++)
		{
			map[x][y].resize(layers,nullptr);				
		}
	}
	}

}
Tilemap::~Tilemap()
{

} 
void Tilemap::update()
{
	
}
void Tilemap::addtile(unsigned x,unsigned y ,unsigned z,sf::IntRect& texturerect)
{
	if(x<mapsize.x && x>=0 &&y<mapsize.y && y>=0)
	{
	if(map[x][y][z]==nullptr)
	{
		map[x][y][z]=(new Tile(x*gridsizef,y*gridsizef,gridsizef,texture,texturerect));
	}
	}
}
void Tilemap::removetile(unsigned x,unsigned y ,unsigned z)
{
	if(map[x][y][z]!=nullptr)
	{
		delete map[x][y][z];
		map[x][y][z]=nullptr;
	}
}
void Tilemap::render(sf::RenderTarget* target)
{
	for(auto& a:this->map)
	{
		for(auto& b:a)
		{
			for(auto& c:b)
			{
				if(c!=nullptr)
				c->render(target);
			}
		}
	}
}