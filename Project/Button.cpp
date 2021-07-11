#include "Button.h"

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
	
	this->text.setCharacterSize(40);
	this->text.setPosition(
		this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f,
		this->shape.getPosition().y + (this->shape.getGlobalBounds().height / 2.f) - this->text.getGlobalBounds().height / 2.f
	);


	this->idleColor = idleColor;
	this->hoverColor = hoverColor;
	this->activeColor = activeColor;

	

}

Button::~Button()
{

}

//Accessors

const bool Button::isPressed() const
{
	if (this->buttonStates == BTN_ACTIVE)
		return true;

	return false;
}

//Functions
void Button::update(const sf::Vector2f mousePos)
{
	/* Update the booleans for hover and pressed*/
	
	//Idle
	this->buttonStates = BTN_IDLE;

	//Hover	
	if (this->shape.getGlobalBounds().contains(mousePos))
	{
		this->buttonStates = BTN_HOVER;

		//Pressed
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->buttonStates = BTN_ACTIVE;
		}
	}
	
	switch (this->buttonStates)
	{
	case BTN_IDLE:
		this->text.setFillColor(this->idleColor);
		this->text.setCharacterSize(40);
		break;
	case BTN_HOVER:
		this->text.setFillColor(this->hoverColor);
		this->text.setCharacterSize(60);
		break;
	case BTN_ACTIVE:
		this->text.setFillColor(this->activeColor);
		this->text.setCharacterSize(40);
		break;
	default:
		this->text.setFillColor(sf::Color::Red);
		this->text.setCharacterSize(40);
		break;
	}

}

void Button::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
	target->draw(this->text);
}
