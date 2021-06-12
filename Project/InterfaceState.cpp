#include "InterfaceState.h"

Interface::Interface(sf::RenderWindow* window,std::stack<State*>* states):State(window,states)
{
	this->rect.setSize(sf::Vector2f(28.0f,25.0f));
	this->rect.setOutlineThickness(1.0f);
	this->rect.setOutlineColor(sf::Color::Green);
	this->rect.setFillColor(sf::Color::Transparent);
	this->rect.setPosition(this->mousePosView);
	this->rect.setOrigin(this->rect.getSize()/2.0f);
	this->initialise();
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

void Interface::obstaclepositions()
{
	std::fstream file;
	file.open("Config/obstaclepositions.ini",std::ios_base::app | std::ios_base::in);
	if(file.is_open())
	{	
		if(alreadythere(a[count].getPosition()))
		file<<a[count].getPosition().x<<" "<<a[count].getPosition().y<<std::endl;		
	}
	file.close();
}

void Interface::initKeybinds()
{

}

void Interface::updateInput(const float& dt)
{
	if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if(alreadythere(mousePosView))
		{
		sf::RectangleShape p(rect.getSize());
		p.setPosition(mousePosView);
		p.setFillColor(sf::Color::Green);
		p.setOrigin(rect.getSize()/2.0f);
		a.push_back(p);
		obstaclepositions();
		count++;
		std::cout<<count<<std::endl;
		}
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		this->endState();
	}
}
void Interface::initialise()
{
	std::fstream file;
	file.open("Config/obstaclepositions.ini");

	if(file.is_open())
	{
		sf::RectangleShape m;
		float c,d;

		while(file>>c>>d)
		{
		m.setSize(rect.getSize());
		m.setPosition(c,d);
		m.setFillColor(sf::Color::Green);
		m.setOrigin(rect.getSize()/2.0f);
		a.push_back(m);
		}

	}
	file.close();
	
}

bool alreadythere(sf::Vector2f a)
{
	std::fstream file;
	file.open("obstaclepositions.ini");
	float c;
	float d;
	if(file.is_open())
	{
		while(file>>c>>d)
		{
			if(c==a.x && d==a.y)
			{
				return false;
			}
		}
	}
	return true;
}

