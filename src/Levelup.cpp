#include "Levelup.h"
#include <iostream>
Levelup::Levelup(Statedata& stateinfo):State(stateinfo)
{
	std::cout<<"A"<<std::endl;
	this->initButtons();
	font.loadFromFile("assets/Fonts/Steppe.otf");
	text.setString("LEVEL CLEARED");
	text.setFont(font);
	
	text.setCharacterSize(60);
	text.setPosition(sf::Vector2f(600,200));
	//text.setStyle(sf::Text::Bold);
}

Levelup::~Levelup()
{
	for(auto& a:buttons)
	{
	delete a.second;
	}
}
void Levelup::initButtons()
{
	this->buttons["Continue"] = new Button(800, 500, 250, 75,
		&this->font, "CONTINUE",
		sf::Color::Black, sf::Color::White, sf::Color(20, 20, 20, 200));

}

void Levelup::update(const float& dt)
{
	
	updateMousePositions(window->getView());
	for(auto& a:buttons)
	{
	
		a.second->update(static_cast<sf::Vector2f>(mousePosWindow));
	}
	
	if(buttons["Continue"]->isPressed())
	{
		endState();
	}
}
void Levelup::render(sf::RenderTarget* target)
{
	if(!target)
	{
		target = window;
	}
	for(auto& a:buttons)
	{
		
		a.second->render(target);
	}
	target->draw(text);
}