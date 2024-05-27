#include <gtest/gtest.h>
#include "Playertest.h"
#include "Player.h"

TEST_F(PlayerResources,coins)
{
	p->equipcoin();
	EXPECT_EQ(p->getcoins(),1);
}

TEST_F(PlayerResources,hitenemy1)
{
	p->update(0.31);
	p->hitenemy();
	EXPECT_EQ(p->gethealth(),75);
}
TEST_F(PlayerResources,hpconst)
{
	p->update(0.2);
	p->hitenemy();
	EXPECT_EQ(p->gethealth(),100);
}
TEST_F(PlayerResources,hitenenemy2)
{
	for(unsigned i =0 ;i<4;i++)
	{
		p->update(0.31);
		p->hitenemy();
	}
	EXPECT_TRUE(p->IsGameOver());
}
TEST_F(PlayerResources,hitenenemy3)
{
	for(unsigned i =0 ;i<4;i++)
	{
		p->update(0.31);
		p->hitenemy();
	}
	p->revive();
	EXPECT_FLOAT_EQ(p->gethealth(),FULLHP);
}
TEST_F(PlayerResources,onwater)
{
	for(unsigned i =0 ;i<200;i++)
	{
		p->update(0.01);
		p->onwater();
	}
	EXPECT_TRUE(p->IsGameOver());
}
TEST_F(PlayerResources,onwater2)
{
	for(unsigned i =0;i<200;i++)
	{
		p->update(0.01);
		p->onwater();
	}
	p->revive();
	EXPECT_FLOAT_EQ(p->gethealth(),inithp);
}
TEST_F(PlayerResources,Killplayer)
{
	p->makePlayerDead();
	EXPECT_FLOAT_EQ(p->gethealth(),0);
}
TEST_F(PlayerResources,Powerup2test1)
{
	p->Jumphigh();
	EXPECT_EQ(P2TIME,p->getpowerup2time());
}

TEST_F(PlayerResources,Powerup2test2)
{
	p->Jumphigh();
	p->update(P2TIME);
	EXPECT_FALSE(p->catchedpowerup2());
}
TEST_F(PlayerResources,Powerup2test3)
{
	p->Jumphigh();
	p->update(2);
	EXPECT_FLOAT_EQ(p->getjumpheight(),JUMPHEIGHT*1.5);
}
TEST_F(PlayerResources,Powerup2test4)
{
	p->Jumphigh();
	p->update(P2TIME);
	EXPECT_FLOAT_EQ(p->getjumpheight(),JUMPHEIGHT);
}

/////////////////////
TEST_F(PlayerMovement,movementxpos)
{
	p->move(0.2,sf::Vector2f(1,0));
	p->update(0.2);
	sf::Vector2f fpos = p->getposition();
	EXPECT_FLOAT_EQ(ipos.x+MAXSPEED*0.2,fpos.x);
}
TEST_F(PlayerMovement,movementxneg)
{
	p->move(0.2,sf::Vector2f(-1,0));
	p->update(0.2);
	sf::Vector2f fpos = p->getposition();
	EXPECT_FLOAT_EQ(ipos.x-MAXSPEED*0.2,fpos.x);
}
TEST_F(PlayerMovement,swicthmovement)
{
	bool init = p->getice();
	p->switchmove();
	bool final = p->getice();
	EXPECT_FALSE(init == final);
}
TEST_F(PlayerMovement,movementxice)
{
	p->switchmove();
	p->move(0.3,{1,0});
	p->update(0.3);
	sf::Vector2f fpos = p->getposition();
	EXPECT_FLOAT_EQ(ipos.x+ACCLERATION*0.3*0.3,fpos.x);
}
TEST_F(PlayerMovement,movementxice2)
{
	p->switchmove();
	p->move(1,{1,0});
	p->update(1);
	p->move(0.7,{0,0});
	p->update(0.7);
	sf::Vector2f fpos = p->getposition();
	EXPECT_FLOAT_EQ(ipos.x+ACCLERATION+(ACCLERATION+DECELARATION*0.7)*0.7,fpos.x);
}
TEST_F(PlayerMovement,movementxice3)
{
	p->switchmove();
	p->move(1,{1,0});
	p->update(1);
	p->move(0.7,{-1,0});
	p->update(0.7);
	sf::Vector2f fpos = p->getposition();
	EXPECT_FLOAT_EQ(ipos.x+ACCLERATION+(ACCLERATION+2*DECELARATION*0.7)*0.7,fpos.x);
}


TEST_F(PlayerMovement,movementy)
{
	p->move(0.2,sf::Vector2f(0,0));
	p->update(0.2);
	sf::Vector2f fpos = p->getposition();
	EXPECT_FLOAT_EQ(ipos.y+0.2*ACCGRAVITY*0.2,fpos.y);
}