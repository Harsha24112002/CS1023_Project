#include "Settings.h"

/////////////////////////////////// INITILIZER FUNCTIONS ////////////////////////////////////////////

void Settings::initBackground()
{
	this->background.setSize(sf::Vector2f(this->window->getSize().x, this->window->getSize().y));
}

void Settings::initView()
{
	view.setSize(window->getDefaultView().getSize());
	view.setCenter(window->getSize().x / 2.0f, window->getSize().y / 2.0f);
}

void Settings::initFonts()
{
	if (!this->font.loadFromFile("assets/Fonts/FomoSans-Bold.ttf"))
	{
		throw("ERROR::SETTINGS::COULT NOT LOAD FONT");
	}
}

void Settings::initButtons()
{
	this->addButton("MAIN_MENU_STATE", 820.f, "BACK");

	this->addButton("INSTRUCTIONS_TO_PLAY", 620.f, "HOW TO PLAY ?");
}

void Settings::initSound()
{
	this->buttonSound = new SoundEffects("assets/Audio/Button_Click.wav");
}

/////////////////////////////////// CONSTRUCTOR AND DESTRUCTOR FUNCTIONS ////////////////////////////////////////////

Settings::Settings(Statedata& state_info)
	:State(state_info)
{
	this->initBackground();
	this->initView();
	this->initFonts();
	this->initButtons();
	this->initSound();

	this->buttonSound->setVolume(70);

	this->menuText.setFont(font);
	this->menuText.setFillColor(sf::Color(100, 150, 200, 200));
	this->menuText.setCharacterSize(200);
	this->menuText.setString("S E T T I N G S");
	this->menuText.setPosition(sf::Vector2f(
		this->view.getSize().x / 2.f - this->menuText.getGlobalBounds().width / 2.f, 80.f
	));

	/*this->volumeLevel.setPosition(sf::Vector2f(this->view.getSize().x /2.f - 100.f, 400.f));
	this->volumeBarOutline.setPosition(volumeLevel.getPosition().x, volumeLevel.getPosition().y);*/
	for (int i = 0; i < 15; i++)
	{
		float x = this->view.getSize().x / 2.f - 295.f;
		float y = 400.f;
		volumeLevel[i].setSize(sf::Vector2f(20.f, ((float)i * 5) + 35));
		volumeLevel[i].setPosition(sf::Vector2f(x + (float)i * 40.f, y + (20 - (float)i) * 5));
		volumeLevel[i].setOutlineThickness(2.f);
		volumeLevel[i].setOutlineColor(sf::Color(150, 100, 200, 200));
		if (i > 10)
			volumeLevel[i].setFillColor(sf::Color::Transparent);
		else
			volumeLevel[i].setFillColor(sf::Color(200, 50, 100, 250));
	}
}

Settings::~Settings()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}

/////////////////////////////////// ACCESSOR FUNCTIONS ////////////////////////////////////////////

std::map<std::string, Button*>& Settings::getButtons()
{
	return this->buttons;
}


void Settings::addButton(const std::string key, float y, std::string text)
{
	float height = 180.f;
	float width = 650.f;
	float x = this->view.getSize().x / 2.f - width / 2.f;
	this->buttons[key] = new Button(x, y, width, height,
		&this->font, text,
		sf::Color(150, 100, 200, 200), sf::Color(200, 50, 100, 250), sf::Color(50, 0, 0, 100));
}

const bool Settings::isButtonPressed(const std::string key)
{
	return this->buttons[key]->isPressed();
}

/////////////////////////////////// UPDATE FUNCTIONS ////////////////////////////////////////////

void Settings::updateButtons()
{
	for (auto& it : this->buttons)
	{
		it.second->update(this->mousePosView);
	}

	if (this->isButtonPressed("INSTRUCTIONS_TO_PLAY"))
	{
		this->states->push(new HowToPlay(stateinfo));
	}

	if (this->isButtonPressed("MAIN_MENU_STATE"))
	{
		this->endState();
	}
}

void Settings::updateVolume()
{
	for (int i = 0; i < 15; i++)
	{
		if (this->volumeLevel[i].getGlobalBounds().contains(this->mousePosView))
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

void Settings::update(const float& dt)
{
	this->updateMousePositions(window->getView());
	this->updateInput(dt);
	this->updateButtons();
	this->updateVolume();
}

void Settings::updateInput(const float& dt)
{
	this->window->setView(view);
}

/////////////////////////////////// RENDER FUNCTIONS ////////////////////////////////////////////

void Settings::render(sf::RenderTarget* target)
{
	if (!target)
	{
		target = this->window;
	}

	target->draw(this->background);
	target->draw(this->menuText);

	for (int i = 0; i < 15; i++)
		target->draw(this->volumeLevel[i]);
	
	for (auto& i : this->buttons)
	{
		i.second->render(target);
	}
}
