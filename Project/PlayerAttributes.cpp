#include "PlayerAttributes.h"

PlayerAttributes::PlayerAttributes(Player* player)
{
	this->player = player;
	Hpbar.setPosition(1600,100);
	Hpbaroutline.setPosition(Hpbar.getPosition());
	Hpbar.setSize(sf::Vector2f(player->gethealth(),10));
	Hpbaroutline.setSize(Hpbar.getSize());
	Hpbar.setFillColor(sf::Color::Red);
	Hpbaroutline.setFillColor(sf::Color::Transparent);
	Hpbaroutline.setOutlineThickness(2.0f);
	Hpbaroutline.setOutlineColor(sf::Color::Green);
	s= "COINS : ";
	font.loadFromFile("Fonts/Dosis-Light.ttf");
	coins.setFont(font);
	coins.setPosition(1600,200);
	coins.setCharacterSize(24);
	coins.setString(s+std::to_string(player->getcoins()));
	coins.setFillColor(sf::Color::Yellow);
	
}

void PlayerAttributes::update()
{
	Hpbar.setSize(sf::Vector2f(player->gethealth(),10));
	coins.setString(s+std::to_string(player->getcoins()));
}

void PlayerAttributes::render(sf::RenderTarget* target)
{
	target->draw(Hpbaroutline);
	target->draw(Hpbar);
	target->draw(coins);
}