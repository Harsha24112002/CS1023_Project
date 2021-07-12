#include "InterfaceState.h"

Interface::Interface(Statedata& state_info):State(state_info)
{
	tilemap = new Tilemap(stateinfo.gridsize,10.0,10.0);
	rect.setPosition(this->mousePosView);
	rect.setSize(sf::Vector2f(stateinfo.gridsize,stateinfo.gridsize));
	rect.setOutlineColor(sf::Color::Green);
	rect.setOutlineThickness(1.0f);
	rect.setFillColor(sf::Color::Transparent);
	this->texrect =sf::IntRect(0,0,(int)stateinfo.gridsize,(int)stateinfo.gridsize);
	textureselector = new TextureSelector(20,20,10,10,stateinfo.gridsize,tilemap->getTilesheet());
}

void Interface::updatemousepos()
{
	updateMousePositions();
	for(auto &a:buttons)
	{
		a.second->update(mousePosView);
	}
}
void Interface::update(const float& dt)
{

	updatemousepos();
	
	this->updateInput(dt);
	
	textureselector->update(mousePosWindow);
	rect.setPosition(sf::Vector2f((float)mousePosGrid.x*stateinfo.gridsize,(float)mousePosGrid.y*stateinfo.gridsize));
	
}

void Interface::render(sf::RenderTarget* target)
{
	if(!target)
	{
		target=this->window;
	}
	
	tilemap->render(target);
	if(!textureselector->getactive())
	{
	target->draw(rect);
	}
	for(auto & a:buttons)
	{
		a.second->render(target);
	}
	textureselector->render(target);
}


void Interface::initKeybinds()
{

}

void Interface::updateInput(const float& dt)
{
	if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if(!textureselector->getactive())
		tilemap->addtile(mousePosGrid.x,mousePosGrid.y,0,texrect);
		else 
		{
		texrect= textureselector->getTexturerect();
		}
	}
	if(sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		tilemap->removetile(mousePosGrid.x,mousePosGrid.y,0);
	}
	
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		this->endState();
	}
}



