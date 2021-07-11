#include "GameState.h"
#include <iostream>
#include  <fstream>


GameState::GameState(Statedata& state_info)
	:State(state_info)
{
	this->initobjects();
}

GameState::~GameState()
{
	delete player;

	for (auto i = obstacles.begin(); i < obstacles.end(); ++i)
	{
		delete* i;
	}

	/*
	 -To restore the default view of the screen which was disturbed
	  by the sf::View when player is moving
	*/
	this->window->setView(window->getDefaultView());
}

void GameState::resize(sf::RenderWindow* window,sf::View* view)
{
	view->setSize((float)window->getSize().x,(float)window->getSize().y);
}



void GameState::initobjects()
{
	player =new Player(textures["Player_body"]);
	this->check = false;
	this->is_game_over = false;
	//obstacles.push_back(new obstacle(textures["Tile"],sf::Vector2f(200.f,200.0f)));
	
	for(unsigned i=0;i<100;i++)
	{
		obstacles.push_back(new obstacle(textures["Tile"],sf::Vector2f(30*i,700)));
	}
	for (unsigned i=0;i<10;i++)
	{
		obstacles.push_back(new obstacle(textures["Tile"],sf::Vector2f(600+30*i,575)));
	}
	
	for(unsigned j=0;j<4;j++)
	{
	for(unsigned i=0;i<100;i++)
	{
		underground.push_back(new obstacle(textures["Underground"],sf::Vector2f(30*i,730+30*j)));
	}
	}
}

void GameState::updateInput(const float& dt)
{
	sf::Vector2f direction={0.0f,0.0f};
	//Update player input
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		direction={-1.0,0.0};
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		direction={1.0,0.0};
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		direction={0.0,-1.0};
	}
	
	this->player->move(dt,direction);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		view.reset(sf::FloatRect(0,0,1440,810));
		this->endState();
	}

}

void GameState::update(const float& dt)
{
	this->resize(window,&view);
	view.setCenter(player->getposition().x+500,player->getposition().y-200);
	unsigned count=0;
	collider c=player->getcollider();
	sf::Vector2f directionofcollison={0.0f,0.0f};
	
	this->updateMousePositions();
	
	for(auto& a: obstacles)
	{
		if((a->getcollider().checkcollision(c,directionofcollison,1.0f)))
		{
			player->oncollision(directionofcollison);
		} 
	
		
	}
	//std::cout<<"("<<player->getposition().x<<":"<<player->getposition().y<<")"<<":"<<"("<<obstacles[0]->getposition().x<<":"<<obstacles[0]->getposition().y<<")"<<std::endl;
	this->updateInput(dt);
	for(auto& a : obstacles)
	{
		a->update(dt);
	}
	this->player->update(dt);
	window->setView(view);

	/*
	  - Updating if the GameState is over or not.
	  - If over then endState() functions is called and new QuitState is
		pushed to the States without ending the current GameState.
	  - So when we quit the QuitState then we come back to the GameState
		and again QuitState is called so to avoid that check variable checks
		if the GameState is already there or not.
	*/
	if (player->IsGameOver())
	{
		is_game_over = true;
		this->endState();
	}

	if (is_game_over && (!check))
	{
		check = true;
		this->window->setView(window->getDefaultView());
		this->states->push(new QuitState(this->stateinfo));
	}

}

void GameState::render(sf::RenderTarget* target)
{
	if (!target)
	{
		target = this->window;
	}
	
	for(auto& a:this->obstacles)
	{
		a->render(*target);
	}
	for(auto a:this->underground)
	{
		a->render(*target);
	}
	this->player->render(target);
}
