#include "InterfaceState.h"

Interface::Interface(sf::RenderWindow* window,std::stack<State*>* states):State(window,states)
{
	this->rect.setSize(sf::Vector2f(28.0f,25.0f));
	this->rect.setOutlineThickness(1.0f);
	this->rect.setOutlineColor(sf::Color::Green);
	this->rect.setFillColor(sf::Color::Transparent);
	this->rect.setPosition(this->mousePosView);
	this->rect.setOrigin(this->rect.getSize()/2.0f);
	
}

void Interface::update(const float& dt)
{
	this->updateMousePositions();
	this->updateInput(dt);
	this->rect.setPosition(this->mousePosView);
	
}

void Interface::render(sf::RenderTarget* target)
{
	if(!target)
	{
		target=this->window;
	}
	target->draw(this->rect);
	for(auto& k : a)
	{
		target->draw(k);
	}
}


void Interface::initKeybinds()
{

}

void Interface::updateInput(const float& dt)
{
	if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		sf::RectangleShape p(rect.getSize());
		p.setPosition(mousePosView);
		p.setFillColor(sf::Color::Green);
		p.setOrigin(rect.getSize()/2.0f);
		a.push_back(p);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		this->endState();
	}
}



