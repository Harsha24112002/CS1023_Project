#ifndef COLLISIONVISITOR_H
#define COLLISIONVISITOR_H

#include "collider.h"
#include "Visitor.h"
#include "Player.h"
#include "Floortile.h"
#include "Enemytile.h"
#include "Coin.h"
#include "Water.h"
#include "Finishtile.h"
#include "Powerup1.h"
#include "Powerup2.h"
#include "Crate.h"
#include "Backgroundtile.h"
#include "Icytile.h"
#include "Shield.h"
#include "Poison.h"
class Collisionvisitor : public Visitor
{
private:
	//Objects
	Player* player;
	collider c;

	//sf Variables
	sf::Vector2f& direction;
public:
	//Constructor
	/**
	 * @brief Constructor for collisionvisitor
	 * @param player player whose collisions are going to be checked
	 * @param direction the direction of collision to player
	 * */
	Collisionvisitor(Player* player,sf::Vector2f& direction);

	//Functions
	void visitFloor(Floortile* f);
	void visitCoin(Coin* c);
	void visitEnemy(Enemytile* e);
	void visitWater(Water* water);
	void visitFinish(Finishtile* finish);
	void visitPowerup1(Powerup1* powerup);
	void visitBackground(Backgroundtile* back);
	void visitIce(Icytile* ice);
	void visitCrate(Crate* crate);
	void visitPowerup2(Powerup2* powerup);
	void visitShield(Shield* shield);
	void visitPoison(Poison* poison);
};

#endif