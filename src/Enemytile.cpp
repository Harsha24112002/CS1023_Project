#include "Enemytile.h"

/////////////////////////////////// CONSTRUCTOR AND DESTRUCTOR FUNCTIONS ////////////////////////////////////////////

Enemytile::Enemytile(float x, float y, float gridsize, sf::Texture& texture, sf::IntRect& texturerect, Tiletype type,sf::Texture* enemytexture)
	: Tile(x,y,gridsize,texture,texturerect,type)
{
	e = new Enemy(x,y,enemytexture);
}

Enemytile::~Enemytile()
{
	delete e;
}

/////////////////////////////////// FUNCTIONS ////////////////////////////////////////////

void Enemytile::accept(Visitor* v)
{
	v->visitEnemy(this);
}

collider Enemytile::getcollider()
{
	return e->getcollider();
}

void Enemytile::todead()
{
	e->makedead();
}

bool Enemytile::isdead()
{
	return e->isdead();
}

bool Enemytile::issqueezed()
{
	return e->issqueezed();
}

/////////////////////////////////// UPDATE FUNCTIONS ////////////////////////////////////////////

void Enemytile::update(float dt)
{
	e->update(dt);
}

/////////////////////////////////// RENDER FUNCTIONS ////////////////////////////////////////////

void Enemytile::render(sf::RenderTarget* target)
{
	e->render(target);
}