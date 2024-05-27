#include "Tilemap.h"
#include <fstream>

/////////////////////////////////// CONSTRUCTOR AND DESTRUCTOR FUNCTIONS ////////////////////////////////////////////

Tilemap::Tilemap(sf::Texture *texture, float gridsize, unsigned width, unsigned height)
{
	this->gridsizeu = (unsigned)gridsize;
	this->gridsizef = gridsize;
	this->mapsize.x = width;
	this->mapsize.y = height;
	this->texture = *texture;
	this->enemytex.loadFromFile("assets/Images/wilber_from_gimp.png");
	for (unsigned x = 0; x < mapsize.x; x++)
	{
		map.resize(mapsize.x, (std::vector<std::vector<Tile *>>()));
		for (unsigned y = 0; y < mapsize.y; y++)
		{

			map[x].resize(mapsize.y, std::vector<Tile *>());
		}
	}

	fromX = 0;
	fromY = 0;
	toX = 0;
	toY = 0;
	colfromX = 0;
	colfromY = 0;
	coltoX = 0;
	coltoY = 0;
	v = nullptr;
}

Tilemap::Tilemap(sf::Texture *texture, std::string filename)
{
	this->texture = *texture;
	this->enemytex.loadFromFile("assets/Images/wilber_from_gimp.png");
	Loadfromfile(filename);
	gridsizeu = (unsigned)gridsizef;
	fromX = 0;
	fromY = 0;
	toX = 0;
	toY = 0;
	colfromX = 0;
	colfromY = 0;
	coltoX = 0;
	coltoY = 0;
	v = nullptr;
}

Tilemap::~Tilemap()
{
	clear();
}

/////////////////////////////////// FUNCTIONS ////////////////////////////////////////////

void Tilemap::clear()
{
	for (auto &a : map)
	{
		for (auto &b : a)
		{
			for (auto &c : b)
			{
				if (c != nullptr)
				{
					delete c;
					c = nullptr;
				}
			}
		}
	}
}

bool Tilemap::checksametype(std::vector<Tile *> layer, Tiletype type)
{
	for (auto &a : layer)
	{
		if (a != nullptr)
		{
			if (a->gettype() == type)
			{
				return true;
			}
		}
	}
	return false;
}

void Tilemap::addtile(unsigned x, unsigned y, sf::IntRect &texturerect, Tiletype type)
{
	if (x < mapsize.x && x >= 0 && y < mapsize.y && y >= 0)
	{
		if (!checksametype(map[x][y], type))
		{
			if (type == ENEMY)
			{
				map[x][y].push_back(new Enemytile(x * gridsizef, y * gridsizef, gridsizef, texture, texturerect, type, &enemytex));
			}
			if (type == FLOORTILE)
			{
				map[x][y].push_back(new Floortile(x * gridsizef, y * gridsizef, gridsizef, texture, texturerect, type));
			}
			if (type == COIN)
			{
				map[x][y].push_back(new Coin(x * gridsizef, y * gridsizef, gridsizef, texture, texturerect, type));
			}
			if (type == WATER)
			{
				map[x][y].push_back(new Water(x * gridsizef, y * gridsizef, gridsizef, texture, texturerect, type));
			}
			if (type == FINISHTILE)
			{
				map[x][y].push_back(new Finishtile(x * gridsizef, y * gridsizeu, gridsizef, texture, texturerect, type));
			}
			if (type == POWERUP1)
			{
				map[x][y].push_back(new Powerup1(x * gridsizef, y * gridsizeu, gridsizef, texture, texturerect, type));
			}
			if (type == BACKGROUND)
			{
				map[x][y].push_back(new Backgroundtile(x * gridsizef, y * gridsizeu, gridsizef, texture, texturerect, type));
			}
			if (type == ICY)
			{
				map[x][y].push_back(new Icytile(x * gridsizef, y * gridsizeu, gridsizef, texture, texturerect, type));
			}
			if (type == CRATE)
			{
				map[x][y].push_back(new Crate(x * gridsizef, y * gridsizeu, gridsizef, texture, texturerect, type));
			}
			if (type == POWERUP2)
			{
				map[x][y].push_back(new Powerup2(x * gridsizef, y * gridsizeu, gridsizef, texture, texturerect, type));
			}
			if (type == SHIELD)
			{
				map[x][y].push_back(new Shield(x * gridsizef, y * gridsizeu, gridsizef, texture, texturerect, type));
			}
			if (type == POISON)
			{
				map[x][y].push_back(new Shield(x * gridsizef, y * gridsizeu, gridsizef, texture, texturerect, type));
			}
		}
	}
}

void Tilemap::removetile(unsigned x, unsigned y)
{

	if (map[x][y].size() >= 1)
	{
		delete map[x][y][map[x][y].size() - 1];
		map[x][y][map[x][y].size() - 1] = nullptr;
		map[x][y].pop_back();
	}
}

void Tilemap::checkcollison(Player *player, sf::Vector2f &direction)
{
	v = new Collisionvisitor(player, direction);
	auto Playergridpos = sf::Vector2i(player->getposition().x / gridsizef, player->getposition().y / gridsizef);
	colfromX = std::min((int)(mapsize.x - 1), std::max(Playergridpos.x - 10, 0));
	colfromY = std::min((int)(mapsize.y - 1), std::max(Playergridpos.y - 7, 0));

	coltoX = std::min((int)(mapsize.x - 1), std::max(colfromX + 20, 0));
	coltoY = std::min((int)(mapsize.y - 1), std::max(colfromY + 14, 0));
	for (unsigned x = colfromX; x < coltoX; x++)
	{
		for (unsigned y = colfromY; y < coltoY; y++)
		{
			for (unsigned z = 0; z < map[x][y].size(); z++)
			{
				if (map[x][y][z] != nullptr)
				{
					map[x][y][z]->accept(v);
					if (map[x][y][z]->istiledead())
					{
						map[x][y].erase(map[x][y].begin() + z);
						z--;
					}
				}
			}
		}
	}
}

void Tilemap::savetofile(std::string &filename)
{
	std::ofstream savefile;
	savefile.open(filename);
	if (savefile.is_open())
	{
		savefile << mapsize.x << " " << mapsize.y << "\n"
				 << gridsizef << "\n"
				 << "\n";
		for (auto &a : map)
		{
			for (auto &b : a)
			{
				for (auto &c : b)
				{
					if (c != nullptr)
					{
						savefile << *c << " ";
					}
				}
			}
		}
	}
	savefile.close();
}

void Tilemap::Loadfromfile(std::string &filename)
{
	clear();
	std::ifstream loadfile;
	loadfile.open(filename);
	if (loadfile.is_open())
	{
		loadfile >> mapsize.x >> mapsize.y >> gridsizef;
		sf::Vector2f positions;
		sf::IntRect texrect;
		int itype;
		Tiletype type;
		for (unsigned x = 0; x < mapsize.x; x++)
		{
			map.resize(mapsize.x, (std::vector<std::vector<Tile *>>()));
			for (unsigned y = 0; y < mapsize.y; y++)
			{

				map[x].resize(mapsize.y, std::vector<Tile *>());
			}
		}
		while (loadfile >> positions.x >> positions.y >> texrect.left >> texrect.top >> itype)
		{
			type = static_cast<Tiletype>(itype);
			int a = positions.x / gridsizef;
			int b = positions.y / gridsizef;
			texrect.width = (float)gridsizef;
			texrect.height = (float)gridsizef;
			if (type == ENEMY)
			{
				map[a][b].push_back(new Enemytile(positions.x, positions.y, gridsizef, texture, texrect, type, &enemytex));
			}
			if (type == FLOORTILE)
			{
				map[a][b].push_back(new Floortile(positions.x, positions.y, gridsizef, texture, texrect, type));
			}
			if (type == COIN)
			{
				map[a][b].push_back(new Coin(positions.x, positions.y, gridsizef, texture, texrect, type));
			}
			if (type == WATER)
			{
				map[a][b].push_back(new Water(positions.x, positions.y, gridsizef, texture, texrect, type));
			}
			if (type == FINISHTILE)
			{
				map[a][b].push_back(new Finishtile(positions.x, positions.y, gridsizef, texture, texrect, type));
			}
			if (type == POWERUP1)
			{
				map[a][b].push_back(new Powerup1(positions.x, positions.y, gridsizef, texture, texrect, type));
			}
			if (type == BACKGROUND)
			{
				map[a][b].push_back(new Backgroundtile(positions.x, positions.y, gridsizef, texture, texrect, type));
			}
			if (type == ICY)
			{
				map[a][b].push_back(new Icytile(positions.x, positions.y, gridsizef, texture, texrect, type));
			}
			if (type == CRATE)
			{
				map[a][b].push_back(new Crate(positions.x, positions.y, gridsizef, texture, texrect, type));
			}
			if (type == POWERUP2)
			{
				map[a][b].push_back(new Powerup2(positions.x, positions.y, gridsizef, texture, texrect, type));
			}
			if (type == SHIELD)
			{
				map[a][b].push_back(new Shield(positions.x, positions.y, gridsizef, texture, texrect, type));
			}
			if (type == POISON)
			{
				map[a][b].push_back(new Shield(positions.x, positions.y, gridsizef, texture, texrect, type));
			}
		}
	}
	loadfile.close();
}

/////////////////////////////////// UPDATE FUNCTIONS ////////////////////////////////////////////

void Tilemap::update(sf::Vector2i Playergridpos, float dt)
{

	fromX = Playergridpos.x - 10;
	fromY = Playergridpos.y - 7;

	if (fromX < 0)
	{
		fromX = 0;
	}
	if (fromX >= mapsize.x)
	{
		fromX = mapsize.x - 1;
	}
	if (fromY < 0)
	{
		fromY = 0;
	}
	if (fromY >= mapsize.y)
	{
		fromY = mapsize.y - 1;
	}
	toX = fromX + 20;
	toY = fromY + 14;
	
	if (toX < 0)
	{
		toX = 0;
	}
	if (toX >= mapsize.x)
	{
		toX = mapsize.x - 1;
	}
	if (toY < 0)
	{
		toY = 0;
	}
	if (toY >= mapsize.y)
	{
		toY = mapsize.y - 1;
	}
	// std::cout<<fromX<<":"<<fromY<<":"<<toX<<":"<<toY<<std::endl;
	for (unsigned x = fromX; x < toX; x++)
	{
		for (unsigned y = fromY; y < toY; y++)
		{
			for (unsigned z = 0; z < map[x][y].size(); z++)
			{
				if (map[x][y][z] != nullptr)
				{
					map[x][y][z]->update(dt);
				}
			}
		}
	}
}

/////////////////////////////////// RENDER FUNCTIONS ////////////////////////////////////////////

void Tilemap::render(sf::RenderTarget *target)
{
	for (unsigned x = fromX; x < toX; x++)
	{
		for (unsigned y = fromY; y < toY; y++)
		{
			for (unsigned z = 0; z < map[x][y].size(); z++)
			{
				if (map[x][y][z] != nullptr)
				{
					map[x][y][z]->render(target);
				}
			}
		}
	}
}