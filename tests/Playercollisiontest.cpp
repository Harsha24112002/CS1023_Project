#include <gtest/gtest.h>
#include "Player.h"
#include "collider.h"
#include "Collisionvisitor.h"
class PlayerCollisiontest : public testing::Test
{
	protected:
	Player* player;
	sf::Vector2f direction;
	Tile* coin;
	Tile* water;
	Tile* healer;
	Tile* shield;
	Visitor* v;
	sf::Texture t1;
	sf::Texture t2;

	void SetUp()
	{
		direction ={0,0};

		t1.loadFromFile("assets/Images/tux_from_linux.png");
		t2.loadFromFile("assets/tiles_2.png");
		
		player = new Player(t1);
		sf::IntRect i = {0,0,80,80};
		coin = new Coin(PLAYERPOS.x+PBOUNDWIDTH,PLAYERPOS.y+PBOUNDHEIGHT,(float)80.0,t2,i,COIN);
		water = new Water(PLAYERPOS.x+PBOUNDWIDTH,PLAYERPOS.y+PBOUNDHEIGHT,(float)80.0,t2,i,WATER);
		healer = new Powerup1(PLAYERPOS.x+PBOUNDWIDTH,PLAYERPOS.y+PBOUNDHEIGHT,(float)80.0,t2,i,POWERUP1);
		shield = new Shield(PLAYERPOS.x+PBOUNDWIDTH,PLAYERPOS.y+PBOUNDHEIGHT,(float)80.0,t2,i,SHIELD);
		v = new Collisionvisitor(player,direction);
	}

	void TearDown()
	{
		delete v;
		delete player;
		delete coin;
		delete water;
		delete healer;
		delete shield;
	}
	
};
TEST_F(PlayerCollisiontest,coin)
{
	for(unsigned i=0;i<100;i++)
	{
		player->move(0.02,{1,0});
		player->update(0.02);
		if(!coin->istiledead())
		{
		coin->accept(v);
		}

	}
	EXPECT_EQ(player->getcoins(),1);
}
TEST_F(PlayerCollisiontest,water)
{
	for(unsigned i=0;i<100;i++)
	{
		player->move(0.02,{1,0});
		player->update(0.02);
		if(!water->istiledead())
		{
		water->accept(v);
		}

	}
	EXPECT_LT(player->gethealth(),100);
}
TEST_F(PlayerCollisiontest,shield)
{
	for(unsigned i=0;i<100;i++)
	{
		player->move(0.02,{1,0});
		player->update(0.02);
		if(!shield->istiledead())
		{
		shield->accept(v);
		}

	}
	player->onwater();
	EXPECT_EQ(player->gethealth(),FULLHP);
}

TEST_F(PlayerCollisiontest,healthpotion)
{
	for(unsigned i =0 ;i<100;i++)
	{
	player->onwater();
	}
	player->hitenemy();
	for(unsigned i=0;i<100;i++)
	{
		player->move(0.02,{1,0});
		player->update(0.02);
		if(!healer->istiledead())
		{
		healer->accept(v);
		}

	}
	
	EXPECT_FLOAT_EQ(player->gethealth(),FULLHP);
}