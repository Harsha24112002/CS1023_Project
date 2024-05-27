#include<gtest/gtest.h>
#include "Player.h"

class Playertest : public testing::Test
{
	protected:
	Player* p;
	sf::Texture t;
	sf::Vector2f ipos;
	void SetUp()
	{

	t.loadFromFile("assets/Images/tux_from_linux.png");
	p = new Player(t);
	ipos = p->getposition();
	}

	void TearDown()
	{
		delete p;
	}
};
TEST_F(Playertest,Newlevel)
{
	p->move(0.5,{1,0});
	p->update(0.3);
	p->Newlevel();
	EXPECT_EQ(p->getposition().x,ipos.x);

}



int main(int argc,char** argv)
{
	testing::InitGoogleTest(&argc,argv);
	return RUN_ALL_TESTS();
}