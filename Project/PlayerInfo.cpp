#include "PlayerInfo.h"

void PlayerInfo::initBackground()
{
	/*this->background.setSize(
		sf::Vector2f
		(
			float(this->window->getSize().x),
			float(this->window->getSize().y)
		)
	);
	this->background.setTexture(&(State::textures["GameInfo_Background"]));*/
	this->next1.setSize(sf::Vector2f(100.f, 100.f));
	this->next1.setTexture((&(State::textures["Next_Image1"])));
	this->next1.setPosition(sf::Vector2f(1820.f, 490.f));

	this->next2.setSize(sf::Vector2f(100.f, 100.f));
	this->next2.setTexture((&(State::textures["Next_Image2"])));
	this->next2.setPosition(sf::Vector2f(0.f, 490.f));

	playerbody = State::textures["Player_body"];

}

void PlayerInfo::initFonts()
{
	if (!this->font.loadFromFile("Fonts/BodoniFLF-Bold.ttf"))
	{
		throw("ERROR::MAINMENUSTATE::COULT NOT LOAD FONT");
	}
}

void PlayerInfo::initButtons()
{
	this->PlayGameButton = new Button(1650, 900, 100, 75,
		&this->font, "Play Game",
		sf::Color::Black, sf::Color::Green, sf::Color(20, 20, 20, 200));

}

void PlayerInfo::initPlayers()
{
	this->rect.setTexture(&(State::textures["Player_body"]));
	this->players.insert(std::pair<int, sf::RectangleShape>(1, this->rect));
	this->rect.setTexture(&(State::textures["Player_body2"]));
	this->players.insert(std::pair<int, sf::RectangleShape>(2, this->rect));
	this->rect.setTexture(&(State::textures["Player_body3"]));
	this->players.insert(std::pair<int, sf::RectangleShape>(3, this->rect));
	this->rect.setTexture(&(State::textures["Player_body4"]));
	this->players.insert(std::pair<int, sf::RectangleShape>(4, this->rect));
	this->buttons.insert(std::pair<std::string, Button*>("Player_body", new Button(910, 640, 100, 50,
		&this->font, "Select",
		sf::Color::Black, sf::Color::Red, sf::Color(20, 20, 20, 200))
		));

	this->buttons.insert(std::pair<std::string, Button*>("Player_body2", new Button(910, 640, 100, 50,
		&this->font, "Select",
		sf::Color::Black, sf::Color::Red, sf::Color(20, 20, 20, 200))
		));

	this->buttons.insert(std::pair<std::string, Button*>("Player_body3", new Button(910, 640, 100, 50,
		&this->font, "Select",
		sf::Color::Black, sf::Color::Red, sf::Color(20, 20, 20, 200))
		));
	this->buttons.insert(std::pair<std::string, Button*>("Player_body4", new Button(910, 640, 100, 50,
		&this->font, "Select",
		sf::Color::Black, sf::Color::Red, sf::Color(20, 20, 20, 200))
		));

	this->itr = players.find(stateinfo.activetexturenum);
	this->button_itr = buttons.find(stateinfo.activetexture);

	sf::Texture tex = *(*itr).second.getTexture();
	sf::Vector2u texturesize = tex.getSize();
	texturesize.x /= 3;
	texturesize.y /= 9;
	(*itr).second.setSize(sf::Vector2f(56.f, 80.f));
	(*itr).second.setTextureRect(sf::IntRect(texturesize.x * 1, texturesize.y * 0, texturesize.x, texturesize.y));
	(*itr).second.setPosition(sf::Vector2f(904.f, 460.f));
	(*itr).second.setScale(2, 2);

	/*button_itr->second->RenameButton("Selected");
	button_itr->second->FrezzeButton();*/

	currentnum = stateinfo.activetexturenum;
	for (auto it = buttons.begin(); it != buttons.end(); ++it)
	{
		if (stateinfo.activetexture == it->first)
		{
			it->second->RenameButton("Selected");
			it->second->FrezzeButton();
		}
	}
}

PlayerInfo::PlayerInfo(Statedata& state_info)
	: State(state_info)
{
	this->initBackground();
	this->initFonts();
	this->initPlayers();

	this->initButtons();
}

PlayerInfo::~PlayerInfo()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}

void PlayerInfo::updateInput(const float& dt)
{
	time += dt;
	if (time > 0.1)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			this->endState();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			if (currentnum != players.size())
			{
				itr++;
				button_itr++;
				sf::Texture tex = *(*itr).second.getTexture();
				sf::Vector2u texturesize = tex.getSize();
				texturesize.x /= 3;
				texturesize.y /= 9;
				(*itr).second.setSize(sf::Vector2f(56.f, 80.f));
				(*itr).second.setTextureRect(sf::IntRect(texturesize.x * 1, texturesize.y * 0, texturesize.x, texturesize.y));
				(*itr).second.setPosition(sf::Vector2f(904.f, 460.f));
				(*itr).second.setScale(2, 2);
				currentnum++;

			}
		}

		if (this->next1.getGlobalBounds().contains(this->mousePosView))
		{
			if (currentnum != players.size())
			{
				this->next1.setSize(sf::Vector2f(200.f, 200.f));
				this->next1.setPosition(sf::Vector2f(1720.f, 440.f));

				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{

					itr++;
					button_itr++;
					sf::Texture tex = *(*itr).second.getTexture();
					sf::Vector2u texturesize = tex.getSize();
					texturesize.x /= 3;
					texturesize.y /= 9;
					(*itr).second.setSize(sf::Vector2f(56.f, 80.f));
					(*itr).second.setTextureRect(sf::IntRect(texturesize.x * 1, texturesize.y * 0, texturesize.x, texturesize.y));
					(*itr).second.setPosition(sf::Vector2f(904.f, 460.f));
					(*itr).second.setScale(2, 2);
					currentnum++;

				}
			}
		}
		else
		{
			this->next1.setSize(sf::Vector2f(100.f, 100.f));
			this->next1.setPosition(sf::Vector2f(1820.f, 490.f));
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			if (currentnum != 1)
			{
				itr--;
				button_itr--;
				sf::Texture tex = *(*itr).second.getTexture();
				sf::Vector2u texturesize = tex.getSize();
				texturesize.x /= 3;
				texturesize.y /= 9;
				(*itr).second.setSize(sf::Vector2f(56.f, 80.f));
				(*itr).second.setTextureRect(sf::IntRect(texturesize.x * 1, texturesize.y * 0, texturesize.x, texturesize.y));
				(*itr).second.setPosition(sf::Vector2f(904.f, 460.f));
				(*itr).second.setScale(2, 2);
				currentnum--;
			}
		}

		if (this->next2.getGlobalBounds().contains(this->mousePosView))
		{
			if (currentnum != 1)
			{
				this->next2.setSize(sf::Vector2f(200.f, 200.f));
				this->next2.setPosition(sf::Vector2f(0.f, 440.f));

				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{

					itr--;
					button_itr--;
					sf::Texture tex = *(*itr).second.getTexture();
					sf::Vector2u texturesize = tex.getSize();
					texturesize.x /= 3;
					texturesize.y /= 9;
					(*itr).second.setSize(sf::Vector2f(56.f, 80.f));
					(*itr).second.setTextureRect(sf::IntRect(texturesize.x * 1, texturesize.y * 0, texturesize.x, texturesize.y));
					(*itr).second.setPosition(sf::Vector2f(904.f, 460.f));
					(*itr).second.setScale(2, 2);
					currentnum--;
				}
			}
		}
		else
		{
			this->next2.setSize(sf::Vector2f(100.f, 100.f));
			this->next2.setPosition(sf::Vector2f(0.f, 490.f));
		}
		time = 0;
	}

}

void PlayerInfo::updateButtons()
{
	/*Updates all the buttons in the state and handles their functionality. */
	/*for (auto& it : this->buttons)
	{
		it.second->update(this->mousePosView);
	}*/

	/*if (this->buttons["Select"]->isPressed())
	{
		this->playerbody = *(*itr).getTexture();
		this->buttons["Select"]->RenameButton("Selected");
		this->buttons["Select"]->FrezzeButton();
	}*/

	PlayGameButton->update(this->mousePosView);
	button_itr->second->update(this->mousePosView);

	if ((button_itr)->second->isPressed())
	{
		for (auto it = buttons.begin(); it != buttons.end(); ++it)
		{
			it->second->DeRenameButton("Select");
			it->second->DefrezzeButton();
		}

		stateinfo.activetexture = button_itr->first;
		stateinfo.activetexturenum = itr->first;
		this->button_itr->second->RenameButton("Selected");
		this->button_itr->second->FrezzeButton();
	}

	if (this->PlayGameButton->isPressed())
	{
		this->states->push(new GameState(stateinfo));
	}

}


void PlayerInfo::update(const float& dt)
{
	this->updateMousePositions(window->getView());
	this->updateInput(dt);

	this->updateButtons();
}

void PlayerInfo::renderButtons(sf::RenderTarget* target)
{
	/*for (auto& it : this->buttons)
	{
		it.second->render(target);
	}*/

	PlayGameButton->render(target);

	button_itr->second->render(target);

}

void PlayerInfo::render(sf::RenderTarget* target)
{
	if (!target)
	{
		target = this->window;
	}

	//target->draw(this->background);

	target->draw(itr->second);
	target->draw(this->next1);
	target->draw(this->next2);
	this->renderButtons(target);
}