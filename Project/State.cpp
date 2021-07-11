#include "State.h"

State::State(Statedata& state_info):stateinfo(state_info)
{
	this->inittextures();
	this->window = state_info.window;
	this->states = state_info.states;
	this->quit = false;
	
}

State::~State()
{

}

void State::inittextures()
{
	textures["Player_body"].loadFromFile("Resources/Images/kit_from_firefox.png");
	textures["Tile"].loadFromFile("Resources/Images/Basic_Ground_Top_Pixel.png");
	textures["Underground"].loadFromFile("Resources/Images/Basic_Ground_Filler_Pixel.png");

}

bool State::getQuit() 
{
	return this->quit;
}


void State::endState()
{
	this->quit = true;
}

void State::updateMousePositions()
{
	this->mousePosScreen = sf::Mouse::getPosition();
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
	this->mousePosGrid = sf::Vector2u(this->mousePosView.x/this->stateinfo.gridsize,this->mousePosView.y/this->stateinfo.gridsize);	
}
