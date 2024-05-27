#ifndef ENEMYTILE_H
#define ENEMYTILE_H

#include "Enemy.h"
#include "Tile.h"
#include "Visitor.h"

class Enemytile : public Tile
{
private:
	Enemy* e;

public:
	//Constructor, Destructor
	Enemytile(float x, float y, float gridsize, sf::Texture& texture, sf::IntRect& texturerect, Tiletype type,sf::Texture* enemytexture);
	virtual ~Enemytile();

	//Functions
	void accept(Visitor* v);
	collider getcollider();
	
	 //Accessor Functions
	 void todead();
	 bool isdead();
	 bool issqueezed();

	 //Update and Render Functions
	 void update(float dt);
	 void render(sf::RenderTarget* target);
};


#endif