#include "PlayerAttributes.h"

/////////////////////////////////// CONSTRUCTOR FUNCTION ////////////////////////////////////////////

PlayerAttributes::PlayerAttributes(Player* player)
{
	this->player = player;
	Hpbar.setPosition(HPPOS);
	Hpbaroutline.setPosition(Hpbar.getPosition());
	Hpbar.setSize(sf::Vector2f(player->gethealth(),HPHEIGHT));
	Hpbaroutline.setSize(Hpbar.getSize());
	Hpbar.setFillColor(sf::Color::Red);
	Hpbaroutline.setFillColor(sf::Color::Transparent);
	Hpbaroutline.setOutlineThickness(2.0f);
	Hpbaroutline.setOutlineColor(sf::Color::Green);
	s= "COINS : ";
	font.loadFromFile("assets/Fonts/Steppe.otf");
	coins.setFont(font);
	coins.setPosition(COINPOS);
	coins.setCharacterSize(24);
	coins.setString(s+std::to_string(player->getcoins()));
	coins.setFillColor(sf::Color::Yellow);
	Poweruptimer.setSize(sf::Vector2f(P2TIME,HPHEIGHT));
	Poweruptimer.setFillColor(sf::Color::Magenta);
	Poweruptimer.setPosition(P2POS);
	shieldtimer.setSize(sf::Vector2f(SHIELDTIME,HPHEIGHT));
	shieldtimer.setFillColor(sf::Color::Cyan);
	shieldtimer.setPosition(SHIELDPOS);
	
}

/////////////////////////////////// UPDATE FUNCTION ////////////////////////////////////////////

void PlayerAttributes::update()
{
	Hpbar.setSize(sf::Vector2f(player->gethealth(),HPHEIGHT));
	coins.setString(s+std::to_string(player->getcoins()));
	if(player->catchedpowerup2())
	{
		Poweruptimer.setSize(sf::Vector2f(player->getpowerup2time()*10,HPHEIGHT));
	}
	if(player->hasshield())
	{
		shieldtimer.setSize(sf::Vector2f(player->getshieldtime()*10,HPHEIGHT));
	}
}

/////////////////////////////////// RENDER FUNCTION ////////////////////////////////////////////

void PlayerAttributes::render(sf::RenderTarget* target)
{
	target->draw(Hpbaroutline);
	target->draw(Hpbar);
	target->draw(coins);
	if(player->catchedpowerup2())
	{
		target->draw(Poweruptimer);
	}
	if(player->hasshield())
	{
		target->draw(shieldtimer);
	}
}