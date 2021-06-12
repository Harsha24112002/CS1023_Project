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

	

	this->background.setTexture(&(State::textures["Main_Menu_Background"]));
}

void MainMenuState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/BodoniFLF-Bold.ttf"))
	{
		throw("ERROR::MAINMENUSTATE::COULT NOT LOAD FONT");
	}
}


void MainMenuState::initButtons()
{
	this->buttons["GAME_STATE"] = new Button(100, 100, 250, 75,
		&this->font, "New Game",
		sf::Color::Green, sf::Color::White, sf::Color(20, 20, 20, 200));
	
	this->buttons["SETTINGS"] = new Button(100, 300, 250, 75,
		&this->font, "Settings",
		sf::Color::Green, sf::Color::White, sf::Color(20, 20, 20, 200));

	this->buttons["Interface"] = new Button(100, 500, 250, 75,
		&this->font, "Interface",
		sf::Color::Green, sf::Color::White, sf::Color(20, 20, 20, 200));

	this->buttons["EXIT_STATE"] = new Button(100, 700, 250, 75,
		&this->font, "Quit",
		sf::Color::Green, sf::Color::White, sf::Color(20, 20, 20, 200));

}

MainMenuState::MainMenuState(sf::RenderWindow* window, std::stack<State*>* states)
	:State(window, states)
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
		this->states->push(new GameState(this->window, this->states));
	}

	//Quit the game
	if (this->buttons["EXIT_STATE"]->isPressed())
	{
		this->endState();
	}
	
	if(this->buttons["Interface"]->isPressed())
	{
		this->states->push(new Interface(this->window,this->states));
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