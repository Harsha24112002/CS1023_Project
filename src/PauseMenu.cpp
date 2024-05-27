#include "PauseMenu.h"

/////////////////////////////////// INITILIZER FUNCTIONS ////////////////////////////////////////////

void PauseMenu::initSound()
{
	this->buttonSound = new SoundEffects("assets/Audio/Button_Click.wav");
}

/////////////////////////////////// CONSTRUCTOR AND DESTRUCTOR FUNCTIONS ////////////////////////////////////////////

PauseMenu::PauseMenu(sf::View* view, sf::Font& font)
	: font(font)
{
	this->container.setSize(sf::Vector2f(
		(float)view->getSize().x / 1.5f,
		(float)view->getSize().y / 1.5f)
	);
	this->container.setFillColor(sf::Color(20, 20, 20, 200));
	this->container.setPosition(sf::Vector2f(
		(float)view->getCenter().x - 180.f,
		(float)view->getCenter().y - this->container.getSize().y / 2.f + 50.f
	));

	this->menuText.setFont(font);
	this->menuText.setFillColor(sf::Color(250, 250, 250, 250));
	this->menuText.setCharacterSize(100);
	this->menuText.setString("RUN 2 WiN");
	this->menuText.setPosition(sf::Vector2f(
		this->container.getPosition().x + this->container.getSize().x / 2.f - this->menuText.getGlobalBounds().width / 2.f,
		this->container.getPosition().y + 25.f
	));
		
	for (int i = 0; i < 15; i++)
	{
		float x = this->container.getPosition().x + this->container.getSize().x / 2.f - 155.f;
		float y = this->container.getPosition().y + 400.f;
		volumeLevel[i].setSize(sf::Vector2f(10.f, ((float)i * 2) + 15));
		volumeLevel[i].setPosition(sf::Vector2f(x + (float)i * 20.f, y+(20-(float)i)*2));
		volumeLevel[i].setOutlineThickness(1.f);
		volumeLevel[i].setOutlineColor(sf::Color(150, 100, 200, 200));
		if (i > 10)
			volumeLevel[i].setFillColor(sf::Color::Transparent);
		else
			volumeLevel[i].setFillColor(sf::Color(200, 50, 100, 250));
	}

	this->initSound();
	this->buttonSound->setVolume(70);
}

PauseMenu::~PauseMenu()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}

/////////////////////////////////// ACCESSOR FUNCTIONS ////////////////////////////////////////////

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
	this->buttons[key]->ChangeMusicTo("Button_Click");
}

/////////////////////////////////// UPDATE FUNCTIONS ////////////////////////////////////////////

void PauseMenu::update(const sf::Vector2f& mousePos)
{
	for (auto& i : this->buttons)
		i.second->update(mousePos);

	for (int i=0; i < 15; i++)
	{
		if (this->volumeLevel[i].getGlobalBounds().contains(mousePos))
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				this->buttonSound->playSound();
				volumeBar = i;
				this->buttonSound->setVolume(6 * (volumeBar + 1));
			}
		}
		if (i <= volumeBar)
			volumeLevel[i].setFillColor(sf::Color(200, 50, 100, 250));
		if (i > volumeBar)
			volumeLevel[i].setFillColor(sf::Color::Transparent);
	}
}

/////////////////////////////////// RENDER FUNCTIONS ////////////////////////////////////////////

void PauseMenu::render(sf::RenderTarget& target)
{
	target.draw(this->container);
	target.draw(this->menuText);
	
	for (int i = 0; i < 15; i++)
		target.draw(this->volumeLevel[i]);

	for (auto& i : this->buttons)
	{
		i.second->render(&target);
	}
}
