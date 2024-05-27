#include "LevelInfo.h"

/////////////////////////////////// INITILIZER FUNCTIONS ////////////////////////////////////////////

void LevelInfo::initBackground()
{
	this->rect.setTexture(&(State::textures["THEME"]));
	this->levels.insert(std::pair<int, sf::RectangleShape>(1, this->rect));

	this->levels.at(1).setSize(THEME_1_TEXTURE_SIZE);
	this->levels.at(1).setPosition(THEME_1_TEXTURE_POSITION);

	this->rect1.setTexture(&(State::textures["THEME2"]));
	this->levels.insert(std::pair<int, sf::RectangleShape>(2, this->rect1));

	this->levels.at(2).setSize(THEME_2_TEXTURE_SIZE);
	this->levels.at(2).setPosition(THEME_2_TEXTURE_POSITION);
}

void LevelInfo::initFonts()
{
	if (!this->font.loadFromFile("assets/Fonts/AbhayaLibre[wght].ttf"))
	{
		throw("ERROR::MAINMENUSTATE::COULT NOT LOAD FONT");
	}
}


void LevelInfo::initButtons()
{
	this->buttons["Level_1"] = new Button(910, 400, 100, 50,
		&this->font, "Select",
		sf::Color::Black, sf::Color::Red, sf::Color(20, 20, 20, 200));
	this->buttons["Level_1"]->ChangeMusicTo("selected_click");

	this->buttons["Level_2"] = new Button(910, 940, 100, 50,
		&this->font, "Select",
		sf::Color::Black, sf::Color::Red, sf::Color(20, 20, 20, 200));
	this->buttons["Level_2"]->ChangeMusicTo("selected_click");

	if (this->stateinfo.activelevel == "THEME")
	{
		this->buttons["Level_1"]->RenameButton("Selected");
		this->buttons["Level_1"]->FrezzeButton();
	}
	else
	{
		this->buttons["Level_2"]->RenameButton("Selected");
		this->buttons["Level_2"]->FrezzeButton();
	}

}

/////////////////////////////////// CONSTRUCTOR AND DESTRUCTOR FUNCTIONS ////////////////////////////////////////////

LevelInfo::LevelInfo(Statedata& state_info)
	:State(state_info)
{
	this->initBackground();
	this->initFonts();

	this->initButtons();

}

LevelInfo::~LevelInfo()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}

/////////////////////////////////// UPDATE FUNCTIONS ////////////////////////////////////////////

void LevelInfo::updateInput(const float& dt)
{

	if (this->stateinfo.activelevel == "THEME")
	{
		if (this->buttons.at("Level_2")->isPressed())
		{
			this->buttons.at("Level_1")->DefrezzeButton();
			this->buttons.at("Level_1")->DeRenameButton("Select");

			this->stateinfo.activelevel = "THEME2";
			stateinfo.activefiles.clear();
			this->stateinfo.activefiles.push_back("assets/Maps/t2level1.txt");
			this->stateinfo.activefiles.push_back("assets/Maps/t2level2.txt");

			this->buttons.at("Level_2")->FrezzeButton();
			this->buttons.at("Level_2")->RenameButton("Selected");

		}
	}

	else
	{
		if (this->buttons.at("Level_1")->isPressed())
		{
			this->buttons.at("Level_2")->DefrezzeButton();
			this->buttons.at("Level_2")->DeRenameButton("Select");

			this->stateinfo.activelevel = "THEME";
			stateinfo.activefiles.clear();
			this->stateinfo.activefiles.push_back("assets/Maps/t1level1.txt");
			this->stateinfo.activefiles.push_back("assets/Maps/t1level2.txt");

			this->buttons.at("Level_1")->RenameButton("Selected");
			this->buttons.at("Level_1")->FrezzeButton();
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		this->endState();
	}

}

void LevelInfo::updateButtons()
{
	/*Updates all the buttons in the state and handles their functionality. */

	if (this->stateinfo.activelevel == "THEME")
	{
		this->buttons.at("Level_2")->update(this->mousePosView);
	}
	else
	{
		this->buttons.at("Level_1")->update(this->mousePosView);
	}

}

void LevelInfo::update(const float& dt)
{
	this->updateMousePositions(window->getDefaultView());
	this->updateInput(dt);

	this->updateButtons();

}

/////////////////////////////////// RENDER FUNCTIONS ////////////////////////////////////////////

void LevelInfo::renderButtons(sf::RenderTarget* target)
{
	this->buttons.at("Level_1")->render(target);
	this->buttons.at("Level_2")->render(target);
}

void LevelInfo::render(sf::RenderTarget* target)
{
	if (!target)
	{
		target = this->window;
	}

	for (auto it = levels.begin(); it != levels.end(); ++it)
	{
		target->draw(it->second);
	}

	this->renderButtons(target);

}
