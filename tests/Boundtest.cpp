#include <gtest/gtest.h>
#include "Bound_Rect.h"
class Boundtest: public testing::Test
{
	protected:
	sf::Sprite a;
	sf::Texture t;
	Boundrect* b;
	float iposx;
	float iposy;
	float fposx;
	float fposy;
	void SetUp()
	{
		t.loadFromFile("assets/Images/tux_from_linux.png");
		a.setTexture(t);
		b = new Boundrect(a,sf::Vector2f(0,0),t.getSize().x,t.getSize().y);
		iposx = b->getfloatrect().left;
		iposy = b->getfloatrect().top;
	}
	void TearDown()
	{

	}
};

TEST_F(Boundtest,Movementtest1)
{
	sf::Vector2f movement = {1,1};
	a.move(movement);
	b->update();
	fposx = b->getfloatrect().left;
	EXPECT_EQ(fposx,iposx+movement.x);
}

TEST_F(Boundtest,Movementtest2)
{
	sf::Vector2f movement = {1,1};
	a.move(movement);
	b->update();
	fposy = b->getfloatrect().top;
	EXPECT_EQ(fposy,iposy+movement.y);	
}

TEST_F(Boundtest,Movementtest3)
{
	sf::Vector2f movement = {1,1};
	a.move(movement);
	fposx = b->getfloatrect().left;
	EXPECT_EQ(fposx,iposx);
}
TEST_F(Boundtest,Movementtest4)
{
	sf::Vector2f movement = {1,1};
	b->move(movement);
	b->update();
	EXPECT_EQ(a.getPosition().x,b->getfloatrect().left);
}
TEST_F(Boundtest,Movementtest5)
{
	sf::Vector2f movement = {1,1};
	b->move(movement);
	b->update();
	EXPECT_EQ(a.getPosition().y,b->getfloatrect().top);
}
