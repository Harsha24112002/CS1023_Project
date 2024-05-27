#include "Button.h"

/////////////////////////////////// CONSTRUCTOR AND DESTRUCTOR FUNCTIONS ////////////////////////////////////////////

void Button::initSound()
{
	this->buffer.loadFromFile("assets/Audio/soft_click.wav");
	sound.setBuffer(buffer);
}

Button::Button(float x, float y, float width, float height,
	sf::Font* font, std::string text,
	sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor)
{
	this->buttonStates = BTN_IDLE;

	this->shape.setPosition(sf::Vector2f(x, y));
	this->shape.setSize(sf::Vector2f(width, height));
	this->shape.setFillColor(sf::Color::Transparent);
	this->font = font;
	this->text.setFont(*this->font);
	this->text.setString(text);
	
	this->text.setCharacterSize(BUTTON_DEFAULT_SIZE);
	this->text.setPosition(
		this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f,
		this->shape.getPosition().y + (this->shape.getGlobalBounds().height / 2.f) - this->text.getGlobalBounds().height / 2.f
	);


	this->idleColor = idleColor;
	this->hoverColor = hoverColor;
	this->activeColor = activeColor;
	this->isButtonFrezzed = false;

	this->initSound();
}

Button::~Button()
{

}

/////////////////////////////////// ACCESSOR FUNCTIONS ////////////////////////////////////////////

const bool Button::isPressed() const
{
	if (this->buttonStates == BTN_ACTIVE)
	{
		return true;
	}

	return false;
}

void Button::RenameButton(std::string str) 
{
	this->text.setString(str);
	this->text.setFillColor(sf::Color::Green);
	this->text.setCharacterSize(BUTTON_ZOOMED_SIZE);
	this->text.setPosition(
		this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f,
		this->shape.getPosition().y + (this->shape.getGlobalBounds().height / 2.f) - this->text.getGlobalBounds().height / 2.f
	);
}

void Button::DeRenameButton(std::string str)
{
	this->text.setString(str);
	this->text.setFillColor(sf::Color::Black);
	this->text.setCharacterSize(BUTTON_DEFAULT_SIZE);
	this->text.setPosition(
		this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f,
		this->shape.getPosition().y + (this->shape.getGlobalBounds().height / 2.f) - this->text.getGlobalBounds().height / 2.f
	);
}



void Button::FrezzeButton()
{
	this->isButtonFrezzed = true;
}

void Button::DefrezzeButton()
{
	this->isButtonFrezzed = false;
}

void Button::ChangeMusicTo(std::string str)
{
	if (str == "click_error")
	{
		this->buffer.loadFromFile("assets/Audio/click_error.wav");
		this->sound.setBuffer(buffer);
	}
	if (str == "selected_click")
	{
		this->buffer.loadFromFile("assets/Audio/selected_click.wav");
		this->sound.setBuffer(buffer);
	}
	if (str == "unlock_click")
	{
		this->buffer.loadFromFile("assets/Audio/unlock_click.wav");
		this->sound.setBuffer(buffer);
	}
	if (str == "Button_Click")
	{
		this->buffer.loadFromFile("assets/Audio/Button_Click.wav");
		this->sound.setBuffer(buffer);
	}

}

/////////////////////////////////// UPDATE FUNCTIONS ////////////////////////////////////////////

void Button::update(const sf::Vector2f& mousePos)
{
	/* Update the booleans for hover and pressed*/
	
	//Idle
	if (1)
	{
		this->buttonStates = BTN_IDLE;

		//Hover	
		if (this->shape.getGlobalBounds().contains(mousePos))
		{
			this->buttonStates = BTN_HOVER;

			//Pressed
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				if (!isButtonFrezzed)
				{
					this->sound.play();
					this->buttonStates = BTN_ACTIVE;
				}
				else
				{
					ChangeMusicTo("click_error");
					this->sound.play();
				}
			}
		}

		switch (this->buttonStates)
		{
		case BTN_IDLE:
			this->text.setFillColor(this->idleColor);
			this->text.setCharacterSize(BUTTON_DEFAULT_SIZE);
			this->text.setPosition(
				this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f,
				this->shape.getPosition().y + (this->shape.getGlobalBounds().height / 2.f) - this->text.getGlobalBounds().height / 2.f
			);
			break;
		case BTN_HOVER:
			this->text.setFillColor(this->hoverColor);
			this->text.setCharacterSize(BUTTON_ZOOMED_SIZE);
			this->text.setPosition(
				this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f,
				this->shape.getPosition().y + (this->shape.getGlobalBounds().height / 2.f) - this->text.getGlobalBounds().height / 2.f
			);
			break;
		case BTN_ACTIVE:
			this->text.setFillColor(this->activeColor);
			this->text.setCharacterSize(BUTTON_DEFAULT_SIZE);
			this->text.setPosition(
				this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f,
				this->shape.getPosition().y + (this->shape.getGlobalBounds().height / 2.f) - this->text.getGlobalBounds().height / 2.f
			);
			break;
		default:
			this->text.setFillColor(sf::Color::Red);
			this->text.setCharacterSize(BUTTON_DEFAULT_SIZE);
			break;
		}
	}

}

/////////////////////////////////// RENDER FUNCTIONS ////////////////////////////////////////////

void Button::render(sf::RenderTarget* target)
{
	if(!isButtonFrezzed)
		target->draw(this->shape);
	target->draw(this->text);
}
