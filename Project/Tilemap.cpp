#include "Tilemap.h"
#include <fstream>
Tilemap::Tilemap(float gridsize,unsigned width,unsigned height)
{
	this->gridsizeu=(unsigned)gridsize;
	this->gridsizef =gridsize;
	this->mapsize.x=width;
	this->mapsize.y=height;
	this->layers=1;
//	std::cout<<mapsize.x<<mapsize.y<<std::endl;
	this->texture.loadFromFile("Resources/tiles_2.png");
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
	for(auto& a:map)
	{
		for(auto& b : a)
		{
			for(auto& c:b)
			{
				if(c!=nullptr)
				{
					c->update();
				}
			}		
		}
	}
}
void Tilemap::addtile(unsigned x,unsigned y ,unsigned z,sf::IntRect& texturerect,int type,bool collison)
{
	if(x<mapsize.x && x>=0 &&y<mapsize.y && y>=0)
	{
	if(map[x][y][z]==nullptr)
	{
		map[x][y][z]=(new Tile(x*gridsizef,y*gridsizef,gridsizef,texture,texturerect,type,collison));
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

void Tilemap::checkcollison(Player* player,sf::Vector2f& direction)
{
	collider collider=player->getcollider();
	for(auto& a:map)
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
	}
}

void Tilemap::savetofile(std::string& filename)
{
	std::ofstream savefile;
	savefile.open(filename);
	if(savefile.is_open())
	{
		savefile<<mapsize.x<<" "<<mapsize.y<<"\n"<<gridsizef<<"\n"<<layers<<"\n";
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
		if(loadfile>>gridsizef>>layers)
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
			if(map[a][b][0]==nullptr)
			{
			map[a][b][0]= new Tile(positions.x,positions.y,gridsizef,texture,texrect,type,collison);
			}
		}

	}
	loadfile.close();			
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