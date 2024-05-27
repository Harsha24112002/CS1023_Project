#include "Collisionvisitor.h"
#include <iostream>

/////////////////////////////////// CONSTRUCTOR FUNCTION ////////////////////////////////////////////

Collisionvisitor::Collisionvisitor(Player* player,sf::Vector2f& direction): direction(direction),c(player->getcollider())
{
	this->player = player;
	
}

/////////////////////////////////// FUNCTIONS ////////////////////////////////////////////

void Collisionvisitor::visitFloor(Floortile* f)
{
	if(f->getcollider().stopcollision(c,direction,{1,1}))
	{
		if(player->getice())
		{
			player->switchmove();
		}
		player->oncollision(direction);
	}
}

void Collisionvisitor::visitEnemy(Enemytile* e)
{
	
	if(e->getcollider().stopcollision(c,direction,{1,1}))
	{
		if(direction.y>0 && direction.x == 0)
		{
			if(!e->isdead())
			{
				e->todead();
			}
		}
		else 
		{
			player->hitenemy();
		}
	}
	if(e->issqueezed())
	{
		e->maketiledead();
	}
}

void Collisionvisitor::visitCoin(Coin* coin)
{
	if(coin->getcollider().checkcollision(c))
	{
		coin->maketiledead();
		player->equipcoin();
	}
}

void Collisionvisitor::visitWater(Water* water)
{
		if (water->getcollider().checkcollision(c))
		{
			if (!player->hasshield())
			{
				player->onwater();
			}
		}
}

void Collisionvisitor::visitFinish(Finishtile* finish)
{
	if (finish->getcollider().stopcollision(c, direction, {1,1}))
	{
		player->makelevelover();
	}
}

void Collisionvisitor::visitPowerup1(Powerup1* powerup)
{
	if(powerup->getcollider().checkcollision(c))
	{
		player->powerupSound();
		player->revive();
		powerup->maketiledead();
	}
}
void Collisionvisitor::visitPowerup2(Powerup2* powerup)
{
	if(powerup->getcollider().checkcollision(c))
	{
		player->powerupSound();
		player->Jumphigh();
		powerup->maketiledead();
	}
}
void Collisionvisitor::visitShield(Shield* shield)
{
	if (shield->getcollider().checkcollision(c))
	{
		player->powerupSound();
		player->equipShield();
		shield->maketiledead();
	}
}
void Collisionvisitor::visitPoison(Poison* poison)
{
	if (poison->getcollider().checkcollision(c))
	{
		player->powerupSound();
		poison->maketiledead();
		player->makePlayerDead();
	}
}
void Collisionvisitor::visitBackground(Backgroundtile* back)
{
	
}

void Collisionvisitor::visitIce(Icytile* ice)
{
	if(ice->getcollider().stopcollision(c,direction,{1,1}))
	{
		if(direction.y>0)
		{
			if(!player->getice())
			{
				player->switchmove();
			}
			player->oncollision(direction);
		}
	}
}
void Collisionvisitor::visitCrate(Crate* crate)
{	
	if(crate->getcollider().stopcollision(c,direction,{0.5,1}))
	{
		if(player->getice())
		{
			player->switchmove();
		}
		player->oncollision(direction);
	}
}
