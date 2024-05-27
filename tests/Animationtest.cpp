#include <gtest/gtest.h>
#include "animation.h"
class Animationtest : public testing::Test
{
	protected:
	sf::Texture t;
	animation* a;
	float dt1 = 0.16;
	float dt2 =0.1;

	void SetUp()
	{
		t.loadFromFile("assets/Images/tux_from_linux.png");
		a = new animation(&t,sf::Vector2f(3,9),0.15);
	}

	void TearDown()
	{
		delete a;
	}

};
TEST_F(Animationtest,currentimagex)
{
	float k = a->r.left+t.getSize().x/3;
	a->update(0,1,dt1);
	EXPECT_EQ(a ->r.left,k);
}
TEST_F(Animationtest,currentimagex2)
{
	float k = a->r.left;
	a->update(0,1,dt2);
	EXPECT_EQ(a ->r.left,k);
}
TEST_F(Animationtest,currentimagex3)
{
	float k = a->r.left+ t.getSize().x/3;
	a->update(0,1,dt1);
	a->update(0,1,dt2);
	EXPECT_EQ(a ->r.left,k);
}
TEST_F(Animationtest,currentimagex4)
{
	float k = a->r.left+t.getSize().x/3;
	a->update(0,1,dt2);
	a->update(0,1,dt2);
	EXPECT_EQ(a ->r.left,k);
}
TEST_F(Animationtest,currentimagex5)
{
	float k = a->r.left;
	a->update(0,1,dt1);	
	a->update(0,1,dt1);
	a->update(0,1,dt1);

	EXPECT_EQ(a ->r.left,k);
}

TEST_F(Animationtest,currentimagey)
{
	int row=1;
	float k = a->r.top+row*t.getSize().y/9;
	a->update(row,1,dt1);
	EXPECT_EQ(a->r.top,k);
}
