#include "InterfaceState.h"

Interface::Interface(Statedata& state_info):State(state_info)
{
	tilemap = new Tilemap(stateinfo.gridsize,24,14);
	rect.setPosition(this->mousePosView);
	rect.setSize(sf::Vector2f(stateinfo.gridsize,stateinfo.gridsize));
	rect.setOutlineColor(sf::Color::Green);
	rect.setOutlineThickness(1.0f);
	rect.setFillColor(sf::Color::Transparent);
	this->texrect =sf::IntRect(0,0,(int)stateinfo.gridsize,(int)stateinfo.gridsize);
	textureselector = new TextureSelector(20,20,10,10,stateinfo.gridsize,tilemap->getTilesheet());
	std::string filename="Tilepositions.txt";
	tilemap->Loadfromfile(filename);
	type=0;
	collision=false;
	keytime=0.0f;
	
	f.loadFromFile("Fonts/BodoniFLF-Bold.ttf");

	mousetext.setFont(f);
	mousetext.setString(std::to_string(collision));
	mousetext.setPosition(mousePosView);
	mousetext.setFillColor(sf::Color::White);
	mousetext.setCharacterSize(15);
	
	this->initView();
}
void Interface::initView()
{
	view.setSize(window->getDefaultView().getSize());	
	view.setCenter(window->getSize().x/2.0f,window->getSize().y/2.0f);
}
void Interface::updatemousepos()
{
	updateMousePositions(view);
	for(auto &a:buttons)
	{
		a.second->update(mousePosView);
	}
}
void Interface::update(const float& dt)
{
	keytime+=dt;
	updatemousepos();
	
	this->updateInput(dt);
	
	textureselector->update(mousePosWindow);
	rect.setPosition(sf::Vector2f((float)mousePosGrid.x*stateinfo.gridsize,(float)mousePosGrid.y*stateinfo.gridsize));
	mousetext.setPosition(mousePosView.x+10,mousePosView.y-10);
	mousetext.setString("collision : "+std::to_string(collision)+"\n"+"Type: "+std::to_string(type));
}

void Interface::render(sf::RenderTarget* target)
{
	if(!target)
	{
		target=this->window;
	}
	target->setView(view);
	tilemap->render(target);
	
	if(!textureselector->getactive())
	{
	target->draw(rect);
	}
	target->draw(mousetext);
	target->setView(target->getDefaultView());
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
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		view.move(-15*dt,0);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		view.move(15*dt,0);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		view.move(0,-15*dt);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		view.move(0,15*dt);
	}
	
	if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if(!textureselector->getactive())
		{
		tilemap->addtile(mousePosGrid.x,mousePosGrid.y,0,texrect,type,collision);
		}
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
		std::string s="Tilepositions.txt";
		tilemap->savetofile(s);
		this->endState();
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::T) && keytime>1.0f)
	{
		if(collision)
		{
			collision=false;
		}
		else collision=true;
		keytime=0.0f;
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && keytime>1.0f)
	{
		++type;
		keytime=0.0f;
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && keytime>1.0f)
	{
		type--;
		keytime=0.0f;
	}
	
}



