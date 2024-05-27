#include "GameInfo.h"

/////////////////////////////////// INITILIZER FUNCTIONS ////////////////////////////////////////////

void GameInfo::initBackground()
{
	this->background.setSize(
		sf::Vector2f
		(
			float(this->window->getSize().x),
			float(this->window->getSize().y)
		)
	);
	this->background.setTexture(&(State::textures["GameInfo_Background"]));

	this->back.setSize(sf::Vector2f(50.f, 50.f));
	this->back.setPosition(sf::Vector2f(25.f, 25.f));
	this->back.setTexture(&(State::textures["Back_Image"]));

}

void GameInfo::initFonts()
{
	if (!this->font.loadFromFile("assets/Fonts/FomoSans-Bold.ttf"))
	{
		throw("ERROR::MAINMENUSTATE::COULT NOT LOAD FONT");
	}
}

void GameInfo::initButtons()
{
	this->buttons["GAMESTATE"] = new Button(800, 250, 250, 75,
		&this->font, "Play Game",
		sf::Color(173, 216, 230), 
		sf::Color(135, 206, 250),
		sf::Color(0, 0, 139) // DarkBlue
		 );

	this->buttons["PLAYER"] = new Button(800, 450, 250, 75,
		&this->font, "Players",
		sf::Color(173, 216, 230), 
		sf::Color(135, 206, 250),
		sf::Color(0, 0, 139) // DarkBlue
		);


	this->buttons["LEVEL"] = new Button(800, 650, 250, 75,
		&this->font, "Levels",
		sf::Color(173, 216, 230), 
		sf::Color(135, 206, 250),
		sf::Color(0, 0, 139) // DarkBlue
		);

}

/////////////////////////////////// CONSTRUCTOR AND DESTRUCTOR FUNCTIONS ////////////////////////////////////////////

GameInfo::GameInfo(Statedata& state_info)
	: State(state_info)
{
	this->initBackground();
	this->initFonts();

	this->initButtons();
}

GameInfo::~GameInfo()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}

/////////////////////////////////// UPDATE FUNCTIONS ////////////////////////////////////////////

void GameInfo::updateInput(const float& dt)
{
	if (this->back.getGlobalBounds().contains(this->mousePosView))
	{
		this->back.setSize(sf::Vector2f(100.f, 100.f));
		this->back.setPosition(sf::Vector2f(0.f, 0.f));
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->endState();
		}
	}
	else
	{
		this->back.setSize(sf::Vector2f(50.f, 50.f));
		this->back.setPosition(sf::Vector2f(25.f, 25.f));
	}

}

void GameInfo::updateButtons()
{
	/*Updates all the buttons in the state and handles their functionality. */
	for (auto& it : this->buttons)
	{
		it.second->update(this->mousePosView);
	}
	//New game
	if (this->buttons["GAMESTATE"]->isPressed())
	{
		this->states->push(new GameState(stateinfo));
	}

	if (this->buttons["PLAYER"]->isPressed())
	{
		this->states->push(new PlayerInfo(stateinfo));
	}

	if (this->buttons["LEVEL"]->isPressed())
	{
		this->states->push(new LevelInfo(stateinfo));
	}
}


void GameInfo::update(const float& dt)
{
	this->updateMousePositions(window->getView());
	this->updateInput(dt);

	this->updateButtons();
}

/////////////////////////////////// RENDER FUNCTIONS ////////////////////////////////////////////

void GameInfo::renderButtons(sf::RenderTarget* target)
{
	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}
}

void GameInfo::render(sf::RenderTarget* target)
{
	if (!target)
	{
		target = this->window;
	}

	target->draw(this->background);
	target->draw(this->back);
	this->renderButtons(target);
}