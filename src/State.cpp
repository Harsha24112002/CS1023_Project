#include "State.h"

/////////////////////////////////// INITILIZER FUNCTIONS ////////////////////////////////////////////

void State::inittextures()
{
	textures["Player_body"].loadFromFile("assets/Images/kit_from_firefox.png");
	textures["Player_body2"].loadFromFile("assets/Images/tux_from_linux.png");
	textures["Player_body3"].loadFromFile("assets/Images/droid_from_android.png");
	textures["Player_body4"].loadFromFile("assets/Images/sara_from_opengameart.png");
	// textures["Tile"].loadFromFile("assets/Images/Basic_Ground_Top_Pixel.png");
	// textures["Underground"].loadFromFile("assets/Images/Basic_Ground_Filler_Pixel.png");
	textures["Quit_Background"].loadFromFile("assets/Images/QuitState_Image.png");
	textures["Level_1"].loadFromFile("assets/tiles_2.png");
	textures["MainMenuBackground"].loadFromFile("assets/Images/MainMenuBackground.png");
	textures["GameInfo_Background"].loadFromFile("assets/Images/GameInfo_Background.png");
	textures["PlayerInfo_Background"].loadFromFile("assets/Images/PlayerInfo.jpg");
	textures["Back_Image"].loadFromFile("assets/Images/back.png");
	textures["Next_Image1"].loadFromFile("assets/Images/next1.png");
	textures["Next_Image2"].loadFromFile("assets/Images/next2.png");
	textures["Help_Image"].loadFromFile("assets/Images/help.png");
	textures["Close_Image"].loadFromFile("assets/Images/close.png");
	textures["THEME"].loadFromFile("assets/tiles_2.png");
	textures["THEME2"].loadFromFile("assets/tiles.png");
	textures["Gamestate_background"].loadFromFile("assets/background0.png");
}

/////////////////////////////////// CONSTRUCTOR AND DESTRUCTOR FUNCTIONS ////////////////////////////////////////////

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

/////////////////////////////////// ACCESSOR FUNCTIONS ////////////////////////////////////////////

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

/////////////////////////////////// UPDATE FUNCTIONS ////////////////////////////////////////////

void State::updateMousePositions(sf::View view)
{
	this->mousePosScreen = sf::Mouse::getPosition();
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	window->setView(view);
	this->mousePosView = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
	this->mousePosGrid = sf::Vector2u(this->mousePosView.x / this->stateinfo.gridsize, this->mousePosView.y / this->stateinfo.gridsize);
	window->setView(window->getDefaultView());
}
