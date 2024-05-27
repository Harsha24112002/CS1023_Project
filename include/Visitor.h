#ifndef VISITOR_H
#define VISITOR_H

class Floortile;
class Enemytile;
class Coin;
class Water;
class Finishtile;
class Powerup1;
class Backgroundtile;
class Icytile;
class Crate;
class Powerup2;
class Shield;
class Poison;
class Visitor
{
public:
	//Constructor
	Visitor(){};

	//Functions
	virtual void visitFloor(Floortile* e)=0;
	virtual void visitEnemy(Enemytile* e)=0;
	virtual void visitCoin(Coin* coin)=0;
	virtual void visitWater(Water* water)=0;
	virtual void visitFinish(Finishtile* finish) = 0;
	virtual void visitPowerup1(Powerup1* powerup) = 0;
	virtual void visitBackground(Backgroundtile* back) = 0;
	virtual void visitIce(Icytile* ice) = 0;
	virtual void visitCrate(Crate* crate)=0;
	virtual void visitPowerup2(Powerup2* powerup) = 0;
	virtual void visitShield(Shield* shield) = 0;
	virtual void visitPoison(Poison* poison) = 0;
};


#endif