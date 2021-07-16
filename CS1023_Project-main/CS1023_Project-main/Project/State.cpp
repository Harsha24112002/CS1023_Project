#include "State.h"

State::State(Statedata& state_info) :stateinfo(state_info)
{
	this->inittextures();
	this->window = state_info.window;
	this->states = state_info.states;
	this->quit = false;
	this->paused = false;
	this->totalquit = false;
	this->playagain = false;
}

State::~State()
{

}

void State::inittextures()
{
	textures["Player_body"].loadFromFile("Resources/Images/kit_from_firefox.png");
	textures["Player_body2"].loadFromFile("Resources/Images/tux_from_linux.png");
	textures["Player_body3"].loadFromFile("Resources/Images/droid_from_android.png");
	textures["Player_body4"].loadFromFile("Resources/Images/sara_from_opengameart.png");
	textures["Tile"].loadFromFile("Resources/Images/Basic_Ground_Top_Pixel.png");
	textures["Underground"].loadFromFile("Resources/Images/Basic_Ground_Filler_Pixel.png");
	textures["Quit_Background"].loadFromFile("Resources/Images/QuitState_Image.jpeg");
	textures["GameInfo_Background"].loadFromFile("Resources/Images/GameInfo_Backgound.jpg");
	textures["Back_Image"].loadFromFile("Resources/Images/back.png");
	textures["Next_Image1"].loadFromFile("Resources/Images/next1.png");
	textures["Next_Image2"].loadFromFile("Resources/Images/next2.png");
	textures["Help_Image"].loadFromFile("Resources/Images/help.png");
	textures["Close_Image"].loadFromFile("Resources/Images/close.png");
}

bool State::getQuit()
{
	return this->quit;
}


void State::endState()
{
	this->quit = true;
}

const bool& State::getTotalQuit() const
{
	return this->totalquit;
}

const bool& State::getPlayAgain() const
{
	return this->playagain;
}

void State::pauseState()
{
	this->paused = true;
}

void State::unpauseState()
{
	this->paused = false;
}

void State::QuitGame()
{
	this->totalquit = true;
}

void State::PlayAgain()
{
	this->playagain = true;
}
void State::updateMousePositions(sf::View view)
{
	this->mousePosScreen = sf::Mouse::getPosition();
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	window->setView(view);
	this->mousePosView = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
	this->mousePosGrid = sf::Vector2u(this->mousePosView.x / this->stateinfo.gridsize, this->mousePosView.y / this->stateinfo.gridsize);
	window->setView(window->getDefaultView());
}
