#include "PauseMenu.h"

PauseMenu::PauseMenu(sf::View* view, sf::Font& font)
	: font(font)
{
	this->container.setSize(sf::Vector2f(
		(float)view->getSize().x / 1.5f,
		(float)view->getSize().y / 1.5f)
	);
	this->container.setFillColor(sf::Color(20, 20, 20, 200));
	this->container.setPosition(sf::Vector2f(
		(float)view->getCenter().x - this->container.getSize().x / 2.f,
		(float)view->getCenter().y - this->container.getSize().y / 2.f
	));

	this->menuText.setFont(font);
	this->menuText.setFillColor(sf::Color(250, 250, 250, 250));
	this->menuText.setCharacterSize(100);
	this->menuText.setString("PAUSED");
	this->menuText.setPosition(sf::Vector2f(
		this->container.getPosition().x + this->container.getSize().x / 2.f - this->menuText.getGlobalBounds().width / 2.f,
		this->container.getPosition().y + 25.f
	));
}

PauseMenu::~PauseMenu()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}

std::map<std::string, Button*>& PauseMenu::getButtons()
{
	return this->buttons;
}

const bool PauseMenu::isButtonPressed(const std::string key)
{
	return this->buttons[key]->isPressed();
}

void PauseMenu::addButton(const std::string key, float y, std::string text)
{
	float height = 50.f;
	float width = 300.f;
	float x = this->container.getPosition().x + this->container.getSize().x / 2.f - width / 2.f;
	this->buttons[key] = new Button(x, this->container.getPosition().y + y, width, height,
		&this->font, text,
		sf::Color(150, 100, 200, 200), sf::Color(200, 50, 100, 250), sf::Color(50, 0, 0, 100));
}

void PauseMenu::update(const sf::Vector2f& mousePos)
{
	for (auto& i : this->buttons)
		i.second->update(mousePos);
}

void PauseMenu::render(sf::RenderTarget& target)
{
	target.draw(this->container);
	target.draw(this->menuText);

	for (auto& i : this->buttons)
	{
		i.second->render(&target);
	}
}
