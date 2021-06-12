#include "GameState.h"
#include <iostream>
#include  <fstream>


GameState::GameState(sf::RenderWindow* window, std::stack<State*>* states)
	:State(window,states)
{
	this->initobjects();
}

GameState::~GameState()
{

}

void GameState::resize(sf::RenderWindow* window,sf::View* view)
{
	view->setSize((float)window->getSize().x,(float)window->getSize().y);
}

void GameState::createobstacles()
{
	std::fstream file;
	file.open("Config/obstaclepositions.ini");
	if(file.is_open())
	{
		float c;
		float d;
		while(file>>c>>d)
		{
			obstacles.push_back(new obstacle(textures["Tile"],sf::Vector2f(c,d)));
		}
	}
	file.close();
}

void GameState::initobjects()
{
	player =new Player(textures["Player_body"]);
	//obstacles.push_back(new obstacle(textures["Tile"],sf::Vector2f(200.f,200.0f)));
	createobstacles();
	for(unsigned i=0;i<100;i++)
	{
		obstacles.push_back(new obstacle(textures["Tile"],sf::Vector2f(30*i,700)));
	}
	for (unsigned i=0;i<10;i++)
	{
		obstacles.push_back(new obstacle(textures["Tile"],sf::Vector2f(600+30*i,625)));
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
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
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
	this->updateInput(dt);
	for(auto& a: obstacles)
	{
		if((a->getcollider().checkcollision(c,directionofcollison,1.0f)))
		{
			player->oncollision(directionofcollison);
		} 
		else count++;
		if(count==obstacles.size())
		{
			player->cannotjump();
		}
	}
	//std::cout<<"("<<player->getposition().x<<":"<<player->getposition().y<<")"<<":"<<"("<<obstacles[0]->getposition().x<<":"<<obstacles[0]->getposition().y<<")"<<std::endl;
	for(auto& a : obstacles)
	{
		a->update(dt);
	}
	this->player->update(dt);
	window->setView(view);
}

void GameState::render(sf::RenderTarget* target)
{
	if (!target)
	{
		target = this->window;
	}
	this->player->render(target);
	for(auto& a:this->obstacles)
	{
		a->render(*target);
	}
	for(auto a:this->underground)
	{
		a->render(*target);
	}
}
