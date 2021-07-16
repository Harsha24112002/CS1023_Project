#ifndef ENEMYTILE_H
#define ENEMYTILE_H

#include "Enemy.h"
#include "Tile.h"
class Enemytile : public Tile
{
	private:
	
	Enemy* e;


	public:

	Enemytile(float x, float y, float gridsize, sf::Texture& texture, sf::IntRect& texturerect, int type, bool collision,sf::Texture* enemytexture);
	collider getcollider();
	void update(float dt);
	void render(sf::RenderTarget* target);
};


#endif