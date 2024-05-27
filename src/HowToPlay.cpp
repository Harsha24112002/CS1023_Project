#include "HowToPlay.h"

/////////////////////////////////// INITILIZER FUNCTIONS ////////////////////////////////////////////

void HowToPlay::initBackground()
{
	this->background.setSize(sf::Vector2f(this->window->getSize().x, this->window->getSize().y));
	this->background.setFillColor(sf::Color(20, 10, 30, 200));
}

void HowToPlay::initView()
{
	view.setSize(window->getDefaultView().getSize());
	view.setCenter(window->getSize().x / 2.0f, window->getSize().y / 2.0f);
}

void HowToPlay::initFonts()
{
	if (!this->font.loadFromFile("assets/Fonts/Steppe.otf"))
	{
		throw("ERROR::SETTINGS::COULT NOT LOAD FONT");
	}
}

void HowToPlay::initButtons()
{
	this->addButton("LEFT", 240.f, "LEFT KEY");
	this->addButton("RIGHT", 320.f, "RIGHT KEY");
	this->addButton("SPACE", 400.f, "SPACE KEY");

	this->addButton("COIN", 480.f, "COIN");
	this->addButton("WATER", 560.f, "WATER");
	this->addButton("POWERUP1", 640.f, "POWER UP 1");
	this->addButton("POWERUP2", 720.f, "POWER UP 2");
	this->addButton("SHIELD", 800.f, "SHIELD");
	this->addButton("ENEMY", 880.f, "ENEMY");
	this->addButton("POISON", 960.f, "POISON");
}

void HowToPlay::initImage()
{
	this->image.setPosition(sf::Vector2f(this->view.getSize().x / 3.f - 100.f, this->view.getSize().y / 4.f));
	this->image.setSize(sf::Vector2f(1567.f / 1.4f, 882.f / 1.4f));
	this->image.setTexture(&tex);
}

void HowToPlay::initTexture()
{
	if(!this->tex.loadFromFile("assets/Images/instructions.png"))
		throw("ERROR::SETTINGS::COULT NOT LOAD TEXTURE");

}

void HowToPlay::initCircle()
{
	this->pointer.setFillColor(sf::Color::Transparent);
	this->pointer.setOutlineThickness(10.f);
	this->pointer.setOutlineColor(sf::Color(50, 100, 200, 200));
	this->pointer.setRadius(45.f);
	this->pointer.setPosition(sf::Vector2f(-150.f, 0.f));
}

void HowToPlay::setBriefTextPosition()
{
	this->briefText.setPosition(sf::Vector2f(
		this->image.getPosition().x + this->image.getSize().x / 2.f - this->briefText.getGlobalBounds().width / 2.f, 920.f
	));
}

/////////////////////////////////// CONSTRUCTOR AND DESTRUCTOR FUNCTIONS ////////////////////////////////////////////

HowToPlay::HowToPlay(Statedata& state_info)
	:State(state_info)
{
	this->initBackground();
	this->initView();
	this->initFonts();
	this->initButtons();
	this->initTexture();
	this->initImage();
	this->initCircle();

	this->menuText.setFont(font);
	this->menuText.setFillColor(sf::Color(100, 150, 200, 200));
	this->menuText.setCharacterSize(150);
	this->menuText.setString("INSTRUCTIONS TO PLAY");
	this->menuText.setPosition(sf::Vector2f(
		this->view.getSize().x / 2.f - this->menuText.getGlobalBounds().width / 2.f, 50.f
	));

	this->briefText.setFont(font);
	this->briefText.setFillColor(sf::Color(50, 150, 200, 200));
	this->briefText.setCharacterSize(45);
}

HowToPlay::~HowToPlay()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}

/////////////////////////////////// ACCESSOR FUNCTIONS ////////////////////////////////////////////

std::map<std::string, Button*>& HowToPlay::getButtons()
{
	return this->buttons;
}


void HowToPlay::addButton(const std::string key, float y, std::string text)
{
	float height = 80.f;
	float width = 300.f;
	float x = this->view.getSize().x / 4.f - 450.f;
	this->buttons[key] = new Button(x, y - 30.f, width, height,
		&this->font, text,
		sf::Color(200, 50, 100, 250), sf::Color(50, 200, 50, 200), sf::Color(50, 0, 0, 100)
	);
}

const bool HowToPlay::isButtonPressed(const std::string key)
{
	return this->buttons[key]->isPressed();
}

/////////////////////////////////// UPDATE FUNCTIONS ////////////////////////////////////////////

void HowToPlay::updateButtons()
{
	for (auto& it : this->buttons)
	{
		it.second->update(this->mousePosView);
	}

	if (this->isButtonPressed("LEFT"))
	{
		this->briefText.setString("PLAYER MOVES TO THE LEFT");
		this->setBriefTextPosition();
	}

	if (this->isButtonPressed("RIGHT"))
	{
		this->briefText.setString("PLAYER MOVES TO THE RIGHT");
		this->setBriefTextPosition();
	}

	if (this->isButtonPressed("SPACE"))
	{
		this->briefText.setString("PLAYER JUMPS");
		this->setBriefTextPosition();
	}

	if (this->isButtonPressed("COIN"))
	{
		this->briefText.setString("YOU GAIN 1 COIN");
		this->setBriefTextPosition();
		this->pointer.setPosition(sf::Vector2f(	this->image.getPosition().x + 454.f, this->image.getPosition().y + 272.f));
	}

	if (this->isButtonPressed("WATER"))
	{
		this->briefText.setString("YOU LOSE LIFE IF YOU ARE IN WATER");
		this->setBriefTextPosition();
		this->pointer.setPosition(sf::Vector2f(this->image.getPosition().x + 600.f, this->image.getPosition().y + 500.f));
	}

	if (this->isButtonPressed("POWERUP1"))
	{
		this->briefText.setString("YOUR HP WILL REACH MAX");
		this->setBriefTextPosition();
		this->pointer.setPosition(sf::Vector2f(this->image.getPosition().x + 568.f, this->image.getPosition().y + 157.f));
	}

	if (this->isButtonPressed("POWERUP2"))
	{
		this->briefText.setString("YOU CAN JUMP EVEN HIGHER");
		this->setBriefTextPosition();
		this->pointer.setPosition(sf::Vector2f(this->image.getPosition().x + 168.f, this->image.getPosition().y - 13.f));
	}

	if (this->isButtonPressed("SHIELD"))
	{
		this->briefText.setString("YOU WILL BE SHIELDED UNDERWATER FOR 5 SECONDS");
		this->setBriefTextPosition();
		this->pointer.setPosition(sf::Vector2f(this->image.getPosition().x - 5.f, this->image.getPosition().y + 155.f));
	}

	if (this->isButtonPressed("ENEMY"))
	{
		this->briefText.setString("    YOU SHOULD JUMP ON YOUR ENEMY TO KILL HIM\nYOU WILL LOSE LIFE IF YOU ARE IN CONTACT WITH HIM");
		this->setBriefTextPosition();
		this->pointer.setPosition(sf::Vector2f(this->image.getPosition().x + 785.f, this->image.getPosition().y + 506.f));
	}

	if (this->isButtonPressed("POISON"))
	{
		this->briefText.setString("YOU WILL DIE AND GAME OVER!");
		this->setBriefTextPosition();
		this->pointer.setPosition(sf::Vector2f(this->image.getPosition().x + 340.f, this->image.getPosition().y + 504.f));
	}
}

void HowToPlay::update(const float& dt)
{
	this->updateMousePositions(window->getView());
	this->updateInput(dt);
	this->updateButtons();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		this->states->pop();
	}
}

void HowToPlay::updateInput(const float& dt)
{
	this->window->setView(view);
}

/////////////////////////////////// RENDER FUNCTIONS ////////////////////////////////////////////

void HowToPlay::render(sf::RenderTarget* target)
{
	if (!target)
	{
		target = this->window;
	}

	target->draw(this->background);
	target->draw(this->menuText);
	target->draw(this->image);
	target->draw(this->briefText);
	target->draw(this->pointer);

	for (auto& i : this->buttons)
	{
		i.second->render(target);
	}
}
