#include "State.h"

State::State(sf::RenderWindow* window, std::stack<State*>* states)
{
	this->inittextures();
	this->window = window;
	
	this->states = states;
	this->quit = false;
}

State::~State()
{

}

void State::inittextures()
{
	textures["Main_Menu_Background"].loadFromFile("Resources/Images/Backgrounds/RUN2WIN.jpeg");
	textures["Player_body"].loadFromFile("Resources/Images/kit_from_firefox.png");
	textures["Tile"].loadFromFile("Resources/Images/Basic_Ground_Top_Pixel.png");
	textures["Underground"].loadFromFile("Resources/Images/Basic_Ground_Filler_Pixel.png");

}

const bool& State::getQuit() const
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
}
