#include<gtest/gtest.h>

#include "collider.h"
#include "Player.h"

class Collisiontest : public testing::Test
{
	protected:
	sf::Sprite tile1;
	sf::Sprite tile2;
	Boundrect* b1;
	Boundrect* b2;
	collider* c1;
	collider* c2;
	sf::Texture t1;
	sf::Texture t2;

	void SetUp()
	{
		t1.loadFromFile("assets/tiles.png");
		t2.loadFromFile("assets/tiles_2.png");
		
		tile1.setTexture(t1);
		tile2.setTexture(t2);
		
		b1= new Boundrect(tile1,{0,0},t1.getSize().x,t2.getSize().y);
		b2= new Boundrect(tile2,{0,0},t2.getSize().x,t2.getSize().y);

		c1 = new collider(*b1);
		c2 = new collider(*b2);
		 
	}

	void TearDown()
	{
		delete b1;
		delete b2;
		delete c1;
		delete c2;
	}
	
};
TEST_F(Collisiontest,collision1)
{
	sf::Vector2f direction = {0,0};
	tile1.setPosition(0,0);
	tile2.setPosition(t1.getSize().x-10,t1.getSize().y-1);
	b1->update();
	
	b2->update();
	EXPECT_TRUE(c1->stopcollision(*c2,direction,{1,1}));
	
}
TEST_F(Collisiontest,collision2)
{
	sf::Vector2f direction = {0,0};
	tile1.setPosition(0,0);
	tile2.setPosition(t1.getSize().x-1,t1.getSize().y-10);
	b1->update();
	
	b2->update();
	EXPECT_TRUE(c1->stopcollision(*c2,direction,{1,1}));
	
}
TEST_F(Collisiontest,collisionx1)
{
	sf::Vector2f direction = {0,0};
	tile1.setPosition(0,0);
	tile2.setPosition(t1.getSize().x-10,t1.getSize().y-1);
	b1->update();
	
	b2->update();
	(c1->stopcollision(*c2,direction,{1,1}));
	EXPECT_FLOAT_EQ(tile2.getPosition().y,t1.getSize().y);	
}

TEST_F(Collisiontest,collisionx2)
{
	sf::Vector2f direction = {0,0};
	tile1.setPosition(0,0);
	tile2.setPosition(t1.getSize().x-10,t1.getSize().y-1);
	b1->update();
	
	b2->update();
	(c1->stopcollision(*c2,direction,{1,1}));
	EXPECT_FLOAT_EQ(tile2.getPosition().x,t1.getSize().x-10);	
}

TEST_F(Collisiontest,collisiony1)
{
	sf::Vector2f direction = {0,0};
	tile1.setPosition(0,0);
	tile2.setPosition(t1.getSize().x-1,t1.getSize().y-10);
	b1->update();
	
	b2->update();
	(c1->stopcollision(*c2,direction,{1,1}));
	EXPECT_FLOAT_EQ(tile2.getPosition().x,t1.getSize().x);	
}
TEST_F(Collisiontest,collisiony2)
{
	sf::Vector2f direction = {0,0};
	tile1.setPosition(0,0);
	tile2.setPosition(t1.getSize().x-1,t1.getSize().y-10);
	b1->update();
	
	b2->update();
	(c1->stopcollision(*c2,direction,{1,1}));
	EXPECT_FLOAT_EQ(tile2.getPosition().y,t1.getSize().y-10);	
}
