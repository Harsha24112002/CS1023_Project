#ifndef TILE_H
#define TILE_H

#include "collider.h"
#include "Bound_Rect.h"

//Class Declarations
class Collisionvisitor;
class Visitor;
enum Tiletype {FLOORTILE = 0,COIN,WATER,ENEMY,POWERUP1,POWERUP2,SHIELD,FINISHTILE,BACKGROUND,ICY,CRATE,POISON};
class Tile
{
protected:
	//Variables
	 //sf Variables
	 sf::Sprite tilesprite;
	 sf::IntRect texturerect;

	 //Accessors
	 bool dead;
	 float gridsize;
	 Tiletype type;

	 //Objects
	 Boundrect* boundrect;
public:
	//Constructors, Destructor
	Tile();
	Tile(float x, float y, float gridsize, sf::Texture& texture, sf::IntRect& texturerect, Tiletype type);
	virtual ~Tile();

	//Functions
	virtual void accept(Visitor* v){}
	friend std::ostream& operator<<(std::ostream& out, Tile);
	virtual collider getcollider();
	
	int gettype();
	virtual void maketiledead();
	virtual bool istiledead();
	//Update and Render Functions
	virtual void update(float dt);
	virtual void render(sf::RenderTarget* target);
};


#endif