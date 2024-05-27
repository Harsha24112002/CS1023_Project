#include "GameState.h"
#include <iostream>
#include  <fstream>

/////////////////////////////////// INITILIZER FUNCTIONS ////////////////////////////////////////////

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
	for (unsigned i = 0; i < this->stateinfo.coins; ++i)
	{
		player->equipcoin();
	}
}

void GameState::initFonts()
{
	if (!this->font.loadFromFile("assets/Fonts/Steppe.otf"))
	{
		throw("ERROR::MAINMENUSTATE::COULT NOT LOAD FONT");
	}
}

void GameState::initPauseMenu()
{
	this->pmenu = new PauseMenu(&this->view, this->font);

	this->pmenu->addButton("CONTINUE", 200.f, "RESUME");

	this->pmenu->addButton("REPLAY", 300.f, "RESTART");

	this->pmenu->addButton("MAIN_MENU_STATE", 500.f, "MAIN MENU");

	this->pmenu->addButton("EXIT_STATE", 600.f, "QUIT");
}

void GameState::initSounds()
{
	this->jump = new SoundEffects("assets/Audio/Jump.wav");	
	this->lost = new SoundEffects("assets/Audio/Lost.wav");
	this->won = new SoundEffects("assets/Audio/Won.wav");

	this->jump->setVolume(70);
	this->lost->setVolume(70);
	this->won->setVolume(70);
}

/////////////////////////////////// CONSTRUCTOR AND DESTRUCTOR FUNCTIONS ////////////////////////////////////////////

GameState::GameState(Statedata& state_info)
	:State(state_info)
{
	time = 0;
	is_game_over =false;
	PlayerTexture = &textures[stateinfo.activetexture];
	background.setTexture(textures["Gamestate_background"]);
	this->initobjects();
	attributes = new PlayerAttributes(player);
	file = stateinfo.activefiles; 
	first = true;
	tilemap = new Tilemap(&textures[stateinfo.activelevel], file.front());

	this->initView();
	this->initRenderTexture();
	this->initFonts();
	this->initPauseMenu();
	this->initSounds();
}

GameState::~GameState()
{
	this->stateinfo.coins = this->player->getcoins();
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

/////////////////////////////////// FUNCTIONS ////////////////////////////////////////////

void GameState::resize(sf::RenderWindow* window, sf::View* view)
{
	//view->setSize((float)window->getSize().x,(float)window->getSize().y);
	//view->setCenter(player->getposition().x + 500, player->getposition().y - 200);
}


sf::Vector2i GameState::getPlayergrid()
{
	sf::Vector2i gridnum;
	gridnum.x = player->getposition().x / stateinfo.gridsize;
	gridnum.y = player->getposition().y / stateinfo.gridsize;
	//std::cout<<gridnum.x<<std::endl;
	return gridnum;
}

/////////////////////////////////// UPDATE FUNCTIONS ////////////////////////////////////////////

void GameState::updatePausedInput(const float& dt)
{
	time += dt;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && time > 0.5f)
	{
		this->pmenu->buttonSound->playSound();
		time = 0.0f;
		if (!this->paused)
			this->pauseState();
		else
			this->unpauseState();
	}
}

void GameState::updateButtons()
{
	if (this->pmenu->isButtonPressed("CONTINUE"))
	{
		this->pmenu->buttonSound->playSound();
		this->unpauseState();
	}

	if (this->pmenu->isButtonPressed("REPLAY"))
	{
		this->pmenu->buttonSound->playSound();
		this->endState();
		this->states->push(new GameState(stateinfo));
	}

	if (this->pmenu->isButtonPressed("MAIN_MENU_STATE"))
	{
		this->pmenu->buttonSound->playSound();
		this->endState();
	}

	if (this->pmenu->isButtonPressed("EXIT_STATE"))
	{
		this->pmenu->buttonSound->playSound();
		this->totalquit = true;
	}

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
		this->jump->playSound();
		direction = { 0.0,-1.0 };
	}

	this->player->move(dt, direction);
}

void GameState::updateLevel()
{
	if (player->IslevelOver())
	{
		this->first = true;
		this->won->playSound();
		if(file.size()==1)
		{
			is_game_over = true;
		}

		if (file.size() > 1)
		{
			states->push(new Levelup(stateinfo));
			file.pop_front();
			delete tilemap;
			tilemap = new Tilemap(&textures[stateinfo.activelevel],file.front());
			player->Newlevel();
		}
		
		
	}
}

void GameState::updateVolume(int vol)
{
	this->jump->setVolume(vol);
	this->lost->setVolume(vol);
	this->won->setVolume(vol);
	this->player->coin.setVolume(vol);
	this->player->water.setVolume(vol);
	this->player->powerup.setVolume(vol);
}

void GameState::update(const float& dt)
{
	this->updateMousePositions(window->getView());
	this->updatePausedInput(dt);

	// this->updateVolume(6 * (this->pmenu->volumeBar + 1));
	if (!this->paused)
	{
		view.setCenter(player->getposition().x + 400, player->getposition().y);
		unsigned count = 0;
		collider c = player->getcollider();
		sf::Vector2f directionofcollison = { 0.0f,0.0f };

		this->updateMousePositions(view);
		if(tilemap)
			tilemap->checkcollison(player, directionofcollison);
		this->updateInput(dt);
		this->player->update(dt);
		if (tilemap)
		{
			tilemap->update(sf::Vector2i((view.getCenter().x / stateinfo.gridsize), (view.getCenter().y / stateinfo.gridsize)), dt);
		}
		if (attributes)
		{
			attributes->update();
		}
		if (player->IsGameOver() || is_game_over)
		{
			this->lost->playSound();
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
	this->updateLevel();
}

/////////////////////////////////// RENDER FUNCTIONS ////////////////////////////////////////////

void GameState::render(sf::RenderTarget* target)
{
	if (!target)
	{
		target = this->window;
	}
	//	window->setView(view);
	this->rendertexture.clear(sf::Color(150, 150, 150, 150));

		target->draw(background);
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
