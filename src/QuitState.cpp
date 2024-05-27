#include "QuitState.h"

/////////////////////////////////// INITILIZER FUNCTIONS ////////////////////////////////////////////

void QuitState::initBackground()
{
	this->background.setSize(
		sf::Vector2f
		(
			float(this->window->getSize().x),
			float(this->window->getSize().y)
		)
	);
	this->background.setTexture(&(State::textures["Quit_Background"]));
}

void QuitState::initFonts()
{
	if (!this->font.loadFromFile("assets/Fonts/FomoSans-Bold.ttf"))
	{
		throw("ERROR::MAINMENUSTATE::COULT NOT LOAD FONT");
	}
}

void QuitState::initButtons()
{
	this->buttons["GAME_STATE"] = new Button(800, 300, 250, 75,
		&this->font, "Play Again",
		sf::Color::Black, sf::Color::Green, sf::Color(20, 20, 20, 200));


	this->buttons["EXIT_STATE"] = new Button(800, 500, 250, 75,
		&this->font, "Quit",
		sf::Color::Black, sf::Color::Red, sf::Color(20, 20, 20, 200));

}

/////////////////////////////////// CONSTRUCTOR AND DESTRUCTOR FUNCTIONS ////////////////////////////////////////////

QuitState::QuitState(Statedata& state_info)
	: State(state_info)
{
	this->initBackground();
	this->initFonts();

	this->initButtons();
}

QuitState::~QuitState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}

/////////////////////////////////// UPDATE FUNCTIONS ////////////////////////////////////////////

void QuitState::updateInput(const float& dt)
{

}

void QuitState::updateButtons()
{
	/*Updates all the buttons in the state and handles their functionality. */
	for (auto& it : this->buttons)
	{
		it.second->update(this->mousePosView);
	}
	//New game
	if (this->buttons["GAME_STATE"]->isPressed())
	{
		this->PlayAgain();
	}

	//Quit the game
	if (this->buttons["EXIT_STATE"]->isPressed())
	{
		this->QuitGame();
	}
}

void QuitState::update(const float& dt)
{
	this->updateMousePositions(window->getDefaultView());
	this->updateInput(dt);

	this->updateButtons();

}

/////////////////////////////////// RENDER FUNCTIONS ////////////////////////////////////////////

void QuitState::renderButtons(sf::RenderTarget* target)
{
	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}
}

void QuitState::render(sf::RenderTarget* target)
{
	if (!target)
	{
		target = this->window;
	}

	target->draw(this->background);
	this->renderButtons(target);
}