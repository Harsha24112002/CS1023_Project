#include <gtest/gtest.h>
#include "Player.h"

class PlayerResources : public testing::Test
{
	protected:
	Player* p;
	sf::Texture t;
	unsigned initcoins;
	unsigned inithp;

	void SetUp()
	{
	t.loadFromFile("assets/Images/tux_from_linux.png");
	p = new Player(t);
	initcoins = p->getcoins();
	inithp = p->gethealth();
	}

	void TearDown()
	{
		delete p;
	}
};

class PlayerMovement: public testing::Test
{
	protected:
	Player* p;
	sf::Texture t;
	sf::Vector2f ipos;

	void SetUp()
	{
	t.loadFromFile("assets/Images/tux_from_linux.png");
	p = new Player(t);
	ipos= p->getposition();
	}

	void TearDown()
	{
		delete p;
	}
};