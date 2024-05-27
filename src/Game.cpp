#include "Game.h"

/////////////////////////////////// INITILIZER FUNCTIONS ////////////////////////////////////////////
//                     Initializes the Window Variables and Dimensions.                            //
/////////////////////////////////////////////////////////////////////////////////////////////////////

void Game::initVariables()
{
	this->window = NULL;
	this->fullscreen = false;
	this->dt = 0.f;
}

void Game::initWindow()
{
	this->videoModes = sf::VideoMode::getFullscreenModes();

	std::string title = "None";
	sf::VideoMode window_bounds = sf::VideoMode::getDesktopMode();

	unsigned framerate_limit = 60;
	bool vertical_sync_enabled = false;

	this->window = new sf::RenderWindow(window_bounds, title, sf::Style::Fullscreen, windowSettings);

	this->window->setFramerateLimit(framerate_limit);
	this->window->setVerticalSyncEnabled(vertical_sync_enabled);
}

void Game::initStateinfo()
{
	this->state_info.window = this->window;
	this->state_info.states = &this->states;
	this->state_info.gridsize = 80.0f;
	this->state_info.activetexture = "Player_body";
	this->state_info.activetexturenum = 1;
	
	this->state_info.activelevel = "THEME";
	this->state_info.activefiles.push_back("assets/Maps/t1level1.txt");
	this->state_info.activefiles.push_back("assets/Maps/t1level2.txt");
	
	this->state_info.coins = 0;
	this->state_info.isplayerlocked.insert(std::pair<std::string, int>("Player_body", 0));
	this->state_info.isplayerlocked.insert(std::pair<std::string, int>("Player_body2", 1));
	this->state_info.isplayerlocked.insert(std::pair<std::string, int>("Player_body3", 1));
	this->state_info.isplayerlocked.insert(std::pair<std::string, int>("Player_body4", 1));
}

void Game::initStates()
{
	this->states.push(new MainMenuState(this->state_info));
}

/////////////////////////////////// CONSTRUCTORS AND DESTRUCTOR FUNCTIONS ////////////////////////////////////////////

Game::Game()
{
	this->initWindow();
	this->initStateinfo();
	this->initStates();

}

Game::~Game()
{
	delete this->window;

	while (!this->states.empty())
	{
		delete this->states.top();
		this->states.pop();
	}
}

/////////////////////////////////// FUNCTIONS ////////////////////////////////////////////

void Game::endApplication()
{
	std::cout << "Ending Application" << "\n";
}

/////////////////////////////////// UPDATE FUNCTIONS ////////////////////////////////////////////
//                Update Functions will update the current State Status.                       //
/////////////////////////////////////////////////////////////////////////////////////////////////

void Game::updateDt()
{
	// this->dt = this->dtClock.restart().asSeconds();
	// if(this->dt > 0.0166f)
	this->dt = 0.0166f;
}

void Game::updateSFMLEvents()
{
	while (this->window->pollEvent(this->sfevent))
	{
		if (this->sfevent.type == sf::Event::Closed)
			this->window->close();
	}
}

void Game::update()
{
	this->updateSFMLEvents();

	if (!this->states.empty())
	{
		this->states.top()->update(this->dt);

		if (this->states.top()->getQuit())
		{
			delete this->states.top();
			this->states.pop();
		}

		// Checking if the game is ending in the QuitState or not.
		else if (this->states.top()->getTotalQuit())
		{
			while (!this->states.empty())
			{
				delete this->states.top();

				this->states.pop();
			}
		}

		else if (this->states.top()->getPlayAgain())
		{
			while (this->states.size() != 1)
			{
				delete this->states.top();

				this->states.pop();
			}
		}

	}
	//Application end
	else
	{
		this->endApplication();
		this->window->close();
	}



}

/////////////////////////////////// RENDER FUNCTIONS ////////////////////////////////////////////
//              Render Functions will draw and display the current state objects.              //
/////////////////////////////////////////////////////////////////////////////////////////////////

void Game::render()
{
	this->window->clear(sf::Color(150, 150, 150, 150));
	//render items
	if (!this->states.empty())
		this->states.top()->render();

	this->window->display();
}

/////////////////////////////////// CORE FUNCTIONS ////////////////////////////////////////////

void Game::run()
{
	while (this->window->isOpen())
	{
		this->updateDt();
		this->update();
		this->render();
	}
}