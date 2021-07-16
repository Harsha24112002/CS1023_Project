#include "Enemytile.h"


Enemytile::Enemytile(float x, float y, float gridsize, sf::Texture& texture, sf::IntRect& texturerect, int type, bool collision,sf::Texture* enemytexture):
	Tile(x,y,gridsize,texture,texturerect,type,collision)
{
	e = new Enemy(x,y,enemytexture);
}
collider Enemytile::getcollider()
{
	return e->getcollider();
}
void Enemytile::update(float dt)
{
	e->update(dt);
}

void Enemytile::render(sf::RenderTarget* target)
{
	e->render(target);
}