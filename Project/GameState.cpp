#include "GameState.h"
#include <iostream>
#include  <fstream>

GameState::GameState(Statedata& state_info)
	:State(state_info)
{

	/*switch (stateinfo.activetexture)
	{
	case 0:
		PlayerTexture = &textures["Player_body"];
		break;
	case 1:
		PlayerTexture = &textures["Player_body3"];
		break;
	case 2:
		PlayerTexture = &textures["Player_body2"];
		break;
	default:
		PlayerTexture = &textures["Player_body"];
		break;
	}*/
	time = 0;
	PlayerTexture = &textures[stateinfo.activetexture];
	this->initobjects();
	attributes = new PlayerAttributes(player);
	std::string s = "Tilepositions.txt";
	tilemap = new Tilemap(stateinfo.gridsize, 1000, 500);
	tilemap->Loadfromfile(s);
	this->initView();
	this->initRenderTexture();
	this->initFonts();
	this->initPauseMenu();
}

GameState::~GameState()
{
	delete player;
	delete pmenu;
	delete tilemap;
	delete attributes;
	/*
	 -To restore the default view of the screen which was disturbed
	  by the sf::View when player is moving
	*/
	this->window->setView(window->getDefaultView());
}

void GameState::resize(sf::RenderWindow* window, sf::View* view)
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
	rendertexture.create(this->stateinfo.window->getSize().x, this->stateinfo.window->getSize().y);
	rendersprite.setTexture(this->rendertexture.getTexture());
	rendersprite.setTextureRect(sf::IntRect(0, 0, this->stateinfo.window->getSize().x, this->stateinfo.window->getSize().y));
	rendertexture.setView(view);
}
void GameState::initBackground()
{

}

void GameState::initobjects()
{
	player = new Player(*PlayerTexture);
	//obstacles.push_back(new obstacle(textures["Tile"],sf::Vector2f(200.f,200.0f)));

}
sf::Vector2i GameState::getPlayergrid()
{
	sf::Vector2i gridnum;
	gridnum.x = player->getposition().x / stateinfo.gridsize;
	gridnum.y = player->getposition().y / stateinfo.gridsize;
	//std::cout<<gridnum.x<<std::endl;
	return gridnum;
}

void GameState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/Dosis-Light.ttf"))
	{
		throw("ERROR::MAINMENUSTATE::COULT NOT LOAD FONT");
	}
}

void GameState::initPauseMenu()
{
	this->pmenu = new PauseMenu(&this->view, this->font);

	this->pmenu->addButton("CONTINUE", 200.f, "RESUME");
	
	this->pmenu->addButton("REPLAY", 300.f, "RESTART");

	this->pmenu->addButton("MAIN_MENU_STATE", 400.f, "MAIN MENU");

	this->pmenu->addButton("EXIT_STATE", 600.f, "QUIT");
}

void GameState::updatePausedInput(const float& dt)
{
	time+=dt;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)&& time>0.5f)
	{
		time=0.0f;
		if (!this->paused)
			this->pauseState();
		else
			this->unpauseState();
	}
}

void GameState::updateButtons()
{
	if (this->pmenu->isButtonPressed("CONTINUE"))
		this->unpauseState();
	
	if (this->pmenu->isButtonPressed("REPLAY"))
	{
		this->endState();
		this->states->push(new GameState(stateinfo));
	}

	if (this->pmenu->isButtonPressed("MAIN_MENU_STATE"))
	{
		this->endState();
		this->states->pop();
		this->states->pop();
	}

	if (this->pmenu->isButtonPressed("EXIT_STATE"))
		this->endState();

}

void GameState::updateInput(const float& dt)
{
	sf::Vector2f direction = { 0.0f,0.0f };
	//Update player input
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		direction = { -1.0,0.0 };
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		direction = { 1.0,0.0 };
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		direction = { 0.0,-1.0 };
	}

	this->player->move(dt, direction);

	
}

void GameState::update(const float& dt)
{
	this->updateMousePositions(window->getView());
	this->updatePausedInput(dt);

	if (!this->paused)
	{
		view.setCenter(player->getposition().x + 400, player->getposition().y);
		unsigned count = 0;
		collider c = player->getcollider();
		sf::Vector2f directionofcollison = { 0.0f,0.0f };

		this->updateMousePositions(view);

		tilemap->checkcollison(player, directionofcollison);

		//std::cout<<"("<<player->getposition().x<<":"<<player->getposition().y<<")"<<":"<<"("<<obstacles[0]->getposition().x<<":"<<obstacles[0]->getposition().y<<")"<<std::endl;
		this->updateInput(dt);

		this->player->update(dt);
		if (tilemap)
			tilemap->update(sf::Vector2i((view.getCenter().x / stateinfo.gridsize), (view.getCenter().y / stateinfo.gridsize)));
		if(attributes)
		{
			attributes->update();
		}
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
	else
	{
		this->pmenu->update(this->mousePosView);
		this->updateButtons();
	}
}

void GameState::render(sf::RenderTarget* target)
{
	if (!target)
	{
		target = this->window;
	}
	//	window->setView(view);
	
	this->rendertexture.clear(sf::Color(150, 150, 150, 150));
	
	rendertexture.setView(view);
	this->player->render(&this->rendertexture);
	if (tilemap)
	{
		tilemap->render(&this->rendertexture);
	}
	
	this->rendertexture.display();
	//std::cout<<rendertexture.getView().getCenter().x<<" "<<player->getposition().x<<std::endl;
	//rendertexture.setView(rendertexture.getDefaultView());
	rendersprite.setTexture(this->rendertexture.getTexture());
	
	target->draw(this->rendersprite);
	attributes->render(target);

	if (this->paused)
	{
		this->pmenu->render(*target);
	}
}
