#include "GameState.h"
#include <iostream>
#include  <fstream>


GameState::GameState(Statedata& state_info, sf::Texture texture)
	:State(state_info)
{
	PlayerTexture = texture;
	this->initobjects();
	std::string s="Tilepositions.txt";
	tilemap = new Tilemap(stateinfo.gridsize,1000,500);
	tilemap->Loadfromfile(s);
	this->initView();
	std::cout<<"A"<<std::endl;
	this->initRenderTexture();
}

GameState::~GameState()
{
	delete player;

	/*
	 -To restore the default view of the screen which was disturbed
	  by the sf::View when player is moving
	*/
	this->window->setView(window->getDefaultView());
}

void GameState::resize(sf::RenderWindow* window,sf::View* view)
{
	//view->setSize((float)window->getSize().x,(float)window->getSize().y);
	//view->setCenter(player->getposition().x + 500, player->getposition().y - 200);
}

void GameState::initView()
{
	view.setSize(static_cast<sf::Vector2f>(this->window->getSize()));

	view.zoom(1);
}

void GameState::initRenderTexture()
{
	rendertexture.create(this->stateinfo.window->getSize().x,this->stateinfo.window->getSize().y);
	rendersprite.setTexture(this->rendertexture.getTexture());
	rendersprite.setTextureRect(sf::IntRect(0,0,this->stateinfo.window->getSize().x,this->stateinfo.window->getSize().y));
	rendertexture.setView(view);
}
void GameState::initBackground()
{

}

void GameState::initobjects()
{
	player =new Player(PlayerTexture);
	//obstacles.push_back(new obstacle(textures["Tile"],sf::Vector2f(200.f,200.0f)));
	
}
sf::Vector2i GameState::getPlayergrid()
{
	sf::Vector2i gridnum;
	gridnum.x=player->getposition().x/stateinfo.gridsize;
	gridnum.y=player->getposition().y/stateinfo.gridsize;
	//std::cout<<gridnum.x<<std::endl;
	return gridnum;
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

	time += dt;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && time > 0.2)
	{
		window->setView(window->getDefaultView());
		this->endState();
		time = 0;
	}

}

void GameState::update(const float& dt)
{
	
	view.setCenter(player->getposition().x+400,player->getposition().y);
	unsigned count=0;
	collider c=player->getcollider();
	sf::Vector2f directionofcollison={0.0f,0.0f};
	
	this->updateMousePositions(view);
	
	tilemap->checkcollison(player,directionofcollison);
	
	//std::cout<<"("<<player->getposition().x<<":"<<player->getposition().y<<")"<<":"<<"("<<obstacles[0]->getposition().x<<":"<<obstacles[0]->getposition().y<<")"<<std::endl;
	this->updateInput(dt);
	
	this->player->update(dt);
	tilemap->update(sf::Vector2i((view.getCenter().x/stateinfo.gridsize),(view.getCenter().y/stateinfo.gridsize)));

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
		this->endState();
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
//	window->setView(view);
	rendertexture.setView(view);
	this->rendertexture.clear(sf::Color(150,150,150,150));
	if(tilemap)
	{
		tilemap->render(&this->rendertexture);
	}
	
	
	
	this->player->render(&this->rendertexture);
	this->rendertexture.display();
	//std::cout<<rendertexture.getView().getCenter().x<<" "<<player->getposition().x<<std::endl;
	//rendertexture.setView(rendertexture.getDefaultView());
	rendersprite.setTexture(this->rendertexture.getTexture());
	target->draw(this->rendersprite);


}
