#include "Game.h"

//Static Functions


//Initializer Functions

void Game::initVariables()
{
	this->window = NULL;
	this->fullscreen = false;
	this->dt = 0.f;
}

void Game::initWindow()
{
	
	/*Creates a SFML window using options from window.ini file. */

	this->videoModes = sf::VideoMode::getFullscreenModes();

	std::string title = "None";
	sf::VideoMode window_bounds = sf::VideoMode::getDesktopMode();
	
	unsigned framerate_limit = 120;
	bool vertical_sync_enabled = false;
	

	
	this->window = new sf::RenderWindow(window_bounds, title, sf::Style::Fullscreen, windowSettings);
	
		

	this->window->setFramerateLimit(framerate_limit);
	this->window->setVerticalSyncEnabled(vertical_sync_enabled);
}
void Game::initStateinfo()
{
	this->state_info.window=this->window;
	this->state_info.states=&this->states;
	this->state_info.gridsize=80.0f;
}

void Game::initStates()
{
	this->states.push(new MainMenuState(this->state_info));
}


//Constructors / Destructors

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

//Functions

void Game::endApplication()
{
	std::cout << "Ending Application" << "\n";
}

void Game::updateDt()
{
	/*Updates the dt variables with the time it takes to update and render one frame*/

	this->dt = this->dtClock.restart().asSeconds();
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

void Game::render()
{
	this->window->clear(sf::Color(150,150,150,150));
	//render items
	if (!this->states.empty())
		this->states.top()->render();

	this->window->display();
}

void Game::run()
{
	while (this->window->isOpen())
	{
		this->updateDt();
		this->update();
		this->render();
	}
}