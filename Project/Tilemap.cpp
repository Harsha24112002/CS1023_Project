#include "Tilemap.h"
#include <fstream>
Tilemap::Tilemap(float gridsize,unsigned width,unsigned height)
{
	this->gridsizeu=(unsigned)gridsize;
	this->gridsizef =gridsize;
	this->mapsize.x=width;
	this->mapsize.y=height;
	//this->layers=1;
//	std::cout<<mapsize.x<<mapsize.y<<std::endl;
	this->texture.loadFromFile("Resources/tiles_2.png");
	for(unsigned x=0;x<mapsize.x;x++)
	{
		map.resize(mapsize.x,(std::vector<std::vector<Tile*>>()));
		for(unsigned y=0;y<mapsize.y;y++)
		{
			
		map[x].resize(mapsize.y,std::vector<Tile*>());	
		
		}
	}

	fromX=0;
	fromY=0;
	toX=0;
	toY=0;

}
Tilemap::~Tilemap()
{
	for(auto& a:map)
	{
		for(auto&b :a)
		{
			for(auto&c : b)
			{
				delete c;
			}
		}
	}
} 
void Tilemap::update(sf::Vector2i Playergridpos)
{
	
	fromX=Playergridpos.x-12;

	fromY=Playergridpos.y-7;
	
	if(fromX<0)
	{
		fromX=0;
	}
	if(fromX >=mapsize.x)
	{
		fromX=mapsize.x-1;
	}
	if(fromY<0)
	{
		fromY=0;
	}
	if(fromY >=mapsize.y)
	{
		fromY=mapsize.y-1;
	}
	toX=fromX+24;
	toY=fromY+14;
	if(toX<0)
	{
		toX=0;
	}
	if(toX >=mapsize.x)
	{
		toX=mapsize.x-1;
	}
	if(toY<0)
	{
		toY=0;
	}
	if(toY >=mapsize.y)
	{
		toY=mapsize.y-1;
	}
	//std::cout<<fromX<<":"<<fromY<<":"<<toX<<":"<<toY<<std::endl; 
	for(unsigned x=fromX;x<toX;x++)
	{
		for(unsigned y=fromY;y<toY;y++)
		{
			for(unsigned z=0;z<map[x][y].size();z++)
			{
				if(map[x][y][z]!=nullptr)
				{
					map[x][y][z]->update();
				}
			}
		}
	}
}
bool Tilemap::checksametype(std::vector<Tile*> layer,int type)
{
	for(auto& a:layer)
	{
		if(a->gettype()==type)
		{
			return true;
		}
	}
	return false;
}
void Tilemap::addtile(unsigned x,unsigned y ,sf::IntRect& texturerect,int type,bool collison)
{
	if(x<mapsize.x && x>=0 &&y<mapsize.y && y>=0)
	{
	if(!checksametype(map[x][y],type))
	{
	map[x][y].push_back(new Tile(x*gridsizef,y*gridsizef,gridsizef,texture,texturerect,type,collison));
	}
	}
}
void Tilemap::removetile(unsigned x,unsigned y )
{
	if(map[x][y][map[x][y].size()-1]!=nullptr)
	{
		delete map[x][y][map[x][y].size()-1];
		map[x][y].pop_back();
		map[x][y][map[x][y].size()-1]=nullptr;
	}
}

void Tilemap::checkcollison(Player* player,sf::Vector2f& direction)
{
	collider collider=player->getcollider();
	/*for(auto& a:map)
	{
		for(auto& b: a)
		{
			for(auto& c:b)
			{
				if(c!=nullptr && c->getcollision())
				{
					if(c->getcollider().checkcollision(collider,direction,1.0f))
					{
						player->oncollision(direction);
					}
				}
			}
		}
	}*/
	for(unsigned x=fromX;x<toX;x++)
	{
		for(unsigned y=fromY;y<toY;y++)
		{
			for(unsigned z=0;z<map[x][y].size();z++)
			{
				if(map[x][y][z]!=nullptr)
				{
					if(map[x][y][z]->getcollider().checkcollision(collider,direction,1.0f))
					player->oncollision(direction);
				}
			}
		}
	}
}

void Tilemap::savetofile(std::string& filename)
{
	std::ofstream savefile;
	savefile.open(filename);
	if(savefile.is_open())
	{
		savefile<<mapsize.x<<" "<<mapsize.y<<"\n"<<gridsizef<<"\n"<<"\n";
		for(auto& a:map)
		{
			for(auto& b:a)
			{
				for(auto& c:b)
				{
					if(c!=nullptr)
					{
					savefile<<*c<<" ";
					}
				}
			}
		}
	}
	savefile.close();
}

void Tilemap::Loadfromfile(std::string& filename)
{
	std::ifstream loadfile;
	loadfile.open(filename);
	if(loadfile.is_open())
	{
		if(loadfile>>mapsize.x>>mapsize.y)
		{

		}
		if(loadfile>>gridsizef)
		{

		}
		sf::Vector2f positions;
		sf::IntRect texrect;
		int type;
		bool collison;
		while(loadfile>>positions.x>>positions.y>>texrect.left>>texrect.top>>type>>collison)
		{
			int a=positions.x/gridsizef;
			int b=positions.y/gridsizef;
			texrect.width=(float)gridsizef;
			texrect.height=(float)gridsizef;
			map[a][b].push_back(new Tile(positions.x,positions.y,gridsizef,texture,texrect,type,collison));
		}

	}
	loadfile.close();			
}

void Tilemap::render(sf::RenderTarget* target)
{
	for(unsigned x=fromX;x<toX;x++)
	{
		for(unsigned y=fromY;y<toY;y++)
		{
			for(unsigned z=0;z<map[x][y].size();z++)
			{
				if(map[x][y][z]!=nullptr)
				{
					map[x][y][z]->render(target);
				}
			}
		}
	}
}