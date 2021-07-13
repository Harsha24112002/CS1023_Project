#include "MainMenuState.h"

//Initializer Functions
void MainMenuState::initVariables()
{

}

void MainMenuState::initBackground()
{
	this->background.setSize(
		sf::Vector2f
	    (
			static_cast<float>(this->window->getSize().x), 
		    static_cast<float>(this->window->getSize().y)
	    )
	);

	

	background.setFillColor(sf::Color(150,150,150,150));	
}

void MainMenuState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/CHLORINR.TTF"))
	{
		throw("ERROR::MAINMENUSTATE::COULT NOT LOAD FONT");
	}
}


void MainMenuState::initButtons()
{
	this->buttons["GAME_STATE"] = new Button(100, 100, 250, 75,
		&this->font, "PLAY",
		sf::Color(120,240,150,255), sf::Color::White, sf::Color(20, 20, 20, 200));

	this->buttons["SETTINGS"] = new Button(100, 300, 250, 75,
		&this->font, "Settings",
		sf::Color(120, 240, 150, 255), sf::Color::White, sf::Color(20, 20, 20, 200));

	this->buttons["Interface"] = new Button(100, 500, 250, 75,
		&this->font, "Interface",
		sf::Color(120,240,150,255), sf::Color::White, sf::Color(20, 20, 20, 200));

	this->buttons["EXIT_STATE"] = new Button(100, 700, 250, 75,
		&this->font, "Quit",
		sf::Color(120,240,150,255), sf::Color::White, sf::Color(20, 20, 20, 200));

}

MainMenuState::MainMenuState(Statedata& state_info)
	:State(state_info)
{
	this->initVariables();
	this->initBackground();
	this->initFonts();
	
	this->initButtons();

}

MainMenuState::~MainMenuState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}


void MainMenuState::updateInput(const float& dt)
{
		
}

void MainMenuState::updateButtons()
{
	/*Updates all the buttons in the state and handles their functionality. */
	for(auto &it : this->buttons)
	{
		it.second->update(this->mousePosView);
	}

	//New game
	if (this->buttons["GAME_STATE"]->isPressed())
	{
		this->states->push(new GameInfo(stateinfo));
	}

	//Quit the game
	if (this->buttons["EXIT_STATE"]->isPressed())
	{
		this->endState();
	}
	
	if(this->buttons["Interface"]->isPressed())
	{
		this->states->push(new Interface(stateinfo));
	}
}

void MainMenuState::update(const float& dt)
{
	this->updateMousePositions();
	this->updateInput(dt);

	this->updateButtons();

}

void MainMenuState::renderButtons(sf::RenderTarget* target)
{
	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}
}

void MainMenuState::render(sf::RenderTarget* target)
{
	if (!target)
	{
		target = this->window;
	}
	
	target->draw(this->background);
	this->renderButtons(target);
	
}