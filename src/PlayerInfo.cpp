#include "PlayerInfo.h"

/////////////////////////////////// INITILIZER FUNCTIONS ////////////////////////////////////////////

void PlayerInfo::initBackground()
{
	this->background.setSize(
		sf::Vector2f
		(
			float(this->window->getSize().x),
			float(this->window->getSize().y)
		)
	);
	this->background.setTexture(&(State::textures["PlayerInfo_Background"]));
	this->next1.setSize(NEXT_IMAGE_SIZE);
	this->next1.setTexture((&(State::textures["Next_Image1"])));
	this->next1.setPosition(NEXT_IMAGE_POSITION);

	this->next2.setSize(PREVIOUS_IMAGE_SIZE);
	this->next2.setTexture((&(State::textures["Next_Image2"])));
	this->next2.setPosition(PREVIOUS_IMAGE_POSTION);

	playerbody = State::textures["Player_body"];

}

void PlayerInfo::initFonts()
{
	if (!this->font.loadFromFile("assets/Fonts/FomoSans-Bold.ttf"))
	{
		throw("ERROR::MAINMENUSTATE::COULT NOT LOAD FONT");
	}
}

void PlayerInfo::initCoins()
{
	this->Coins.setTexture(&(State::textures["Level_1"]));
	coins.setFont(font);
	coins.setPosition(coins_POSITION);
	coins.setCharacterSize(coins_CHARACTER_SIZE);
	coins.setString(std::to_string(this->stateinfo.coins));
	coins.setFillColor(sf::Color::Yellow);
	sf::Texture tex = *Coins.getTexture();
	sf::Vector2u texturesize = tex.getSize();
	texturesize.x /= 4;
	texturesize.y /= 4;
	Coins.setSize(COINS_SIZE);
	Coins.setTextureRect(sf::IntRect(texturesize.x * 1, texturesize.y * 0, texturesize.x, texturesize.y));
	Coins.setPosition(COINS_POSTION);

	this->CoinsForCost.setTexture(&(State::textures["Level_1"]));
	tex = *CoinsForCost.getTexture();
	texturesize = tex.getSize();
	texturesize.x /= 4;
	texturesize.y /= 4;
	CoinsForCost.setSize(COINSFORCOST_SIZE);
	CoinsForCost.setTextureRect(sf::IntRect(texturesize.x * 1, texturesize.y * 0, texturesize.x, texturesize.y));
	CoinsForCost.setPosition(COINSFORCOST_POSITION);

}

void PlayerInfo::initButtons()
{
	/*this->PlayGameButton = new Button(1650, 900, 100, 75,
		&this->font, "Play Game",
		sf::Color::Black, sf::Color::Green, sf::Color(20, 20, 20, 200));*/
	this->buffer.loadFromFile("assets/Audio/unlock_click.wav");
	this->sound.setBuffer(buffer);
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

	this->buttons.insert(std::pair<std::string, Button*>("Player_body", new Button(940, 740, 100, 50,
		&this->font, "Select",
		sf::Color::Black, sf::Color::Red, sf::Color(20, 20, 20, 200))
		));

	this->buttons.insert(std::pair<std::string, Button*>("Player_body2", new Button(940, 740, 100, 50,
		&this->font, "Select",
		sf::Color::Black, sf::Color::Red, sf::Color(20, 20, 20, 200))
		));

	this->cost.insert(std::pair < std::string, int >("Player_body2", 25));

	this->buttons.insert(std::pair<std::string, Button*>("Player_body3", new Button(940, 740, 100, 50,
		&this->font, "Select",
		sf::Color::Black, sf::Color::Red, sf::Color(20, 20, 20, 200))
		));

	this->cost.insert(std::pair < std::string, int >("Player_body3", 50));

	this->buttons.insert(std::pair<std::string, Button*>("Player_body4", new Button(940, 740, 100, 50,
		&this->font, "Select",
		sf::Color::Black, sf::Color::Red, sf::Color(20, 20, 20, 200))
		));

	this->cost.insert(std::pair < std::string, int >("Player_body4", 100));



	this->itr = players.find(stateinfo.activetexturenum);
	this->button_itr = buttons.find(stateinfo.activetexture);

	sf::Texture tex = *(*itr).second.getTexture();
	sf::Vector2u texturesize = tex.getSize();
	texturesize.x /= 3;
	texturesize.y /= 9;
	(*itr).second.setSize(PLAYERSIZE);
	(*itr).second.setTextureRect(sf::IntRect(texturesize.x * 1, texturesize.y * 0, texturesize.x, texturesize.y));
	(*itr).second.setPosition(PLAYERPOSTION);

	for (auto it = players.begin(); it != players.end(); ++it)
	{
		int num = itr->first;
		sf::Texture tex = *(*itr).second.getTexture();
		sf::Vector2u texturesize = tex.getSize();
		texturesize.x /= 3;
		texturesize.y /= 9;
		(*it).second.setSize(PLAYERSIZE);
		(*it).second.setTextureRect(sf::IntRect(texturesize.x * 1, texturesize.y * 0, texturesize.x, texturesize.y));
		(*it).second.setPosition(sf::Vector2f(904.f + (it->first - num) * 550, 460.f));
		(*it).second.setScale(PLAYERSCALEBEFORE);
	}
	(*itr).second.setScale(PLAYERSCALEAFTER);

	currentnum = stateinfo.activetexturenum;
	for (auto it = buttons.begin(); it != buttons.end(); ++it)
	{
		if (stateinfo.activetexture == it->first)
		{
			it->second->RenameButton("Selected");
			it->second->FrezzeButton();
		}
		else
		{
			if (stateinfo.isplayerlocked.find(it->first)->second)
			{
				if (stateinfo.coins >= cost.find(it->first)->second)
				{
					it->second->DeRenameButton("Unlock");
				}
				else
				{
					it->second->RenameButton("Locked");
					it->second->FrezzeButton();
				}
			}
		}
	}
	if (this->button_itr->first != "Player_body")
	{
		Cost.setString(std::to_string(this->cost.find(button_itr->first)->second));
		Cost.setCharacterSize(45);
		Cost.setPosition(sf::Vector2f(904.0f, 400.0f));
	}


	this->anim = new animation((&State::textures[stateinfo.activetexture]), sf::Vector2f(3, 9), 0.3);
	this->sprite.setTexture(State::textures[stateinfo.activetexture]);
	this->sprite.setScale(PLAYERSCALEAFTER);
	this->sprite.setPosition(PLAYERSIZE);
	this->sprite.setTextureRect(anim->r);
	this->sprite.setPosition(PLAYERPOSTION);
}

/////////////////////////////////// CONSTRUCTOR AND DESTRUCTOR FUNCTIONS ////////////////////////////////////////////

PlayerInfo::PlayerInfo(Statedata& state_info)
	: State(state_info)
{
	this->initBackground();
	this->initFonts();
	this->initPlayers();
	this->initCoins();
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

/////////////////////////////////// UPDATE FUNCTIONS ////////////////////////////////////////////

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
				this->sprite.setTexture(State::textures[button_itr->first]);
				for (auto it = players.begin(); it != players.end(); ++it)
				{
					int num = itr->first;
					sf::Texture tex = *(*itr).second.getTexture();
					sf::Vector2u texturesize = tex.getSize();
					texturesize.x /= 3;
					texturesize.y /= 9;
					(*it).second.setSize(PLAYERSIZE);
					(*it).second.setTextureRect(sf::IntRect(texturesize.x * 1, texturesize.y * 0, texturesize.x, texturesize.y));
					(*it).second.setPosition(sf::Vector2f(904.f + (it->first - num) * 550, 460.f));
					(*it).second.setScale(PLAYERSCALEBEFORE);
				}
				(*itr).second.setScale(PLAYERSCALEAFTER);
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
					this->sprite.setTexture(State::textures[button_itr->first]);
					for (auto it = players.begin(); it != players.end(); ++it)
					{
						int num = itr->first;
						sf::Texture tex = *(*itr).second.getTexture();
						sf::Vector2u texturesize = tex.getSize();
						texturesize.x /= 3;
						texturesize.y /= 9;
						(*it).second.setSize(PLAYERSIZE);
						(*it).second.setTextureRect(sf::IntRect(texturesize.x * 1, texturesize.y * 0, texturesize.x, texturesize.y));
						(*it).second.setPosition(sf::Vector2f(904.f + (it->first - num) * 550, 460.f));
						(*it).second.setScale(PLAYERSCALEBEFORE);
					}
					(*itr).second.setScale(PLAYERSCALEAFTER);
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
				this->sprite.setTexture(State::textures[button_itr->first]);
				for (auto it = players.begin(); it != players.end(); ++it)
				{
					int num = itr->first;
					sf::Texture tex = *(*itr).second.getTexture();
					sf::Vector2u texturesize = tex.getSize();
					texturesize.x /= 3;
					texturesize.y /= 9;
					(*it).second.setSize(PLAYERSIZE);
					(*it).second.setTextureRect(sf::IntRect(texturesize.x * 1, texturesize.y * 0, texturesize.x, texturesize.y));
					(*it).second.setPosition(sf::Vector2f(904.f + (it->first - num) * 550, 460.f));
					(*it).second.setScale(PLAYERSCALEBEFORE);
				}
				(*itr).second.setScale(PLAYERSCALEAFTER);
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
					this->sprite.setTexture(State::textures[button_itr->first]);
					for (auto it = players.begin(); it != players.end(); ++it)
					{
						int num = itr->first;
						sf::Texture tex = *(*itr).second.getTexture();
						sf::Vector2u texturesize = tex.getSize();
						texturesize.x /= 3;
						texturesize.y /= 9;
						(*it).second.setSize(PLAYERSIZE);
						(*it).second.setTextureRect(sf::IntRect(texturesize.x * 1, texturesize.y * 0, texturesize.x, texturesize.y));
						(*it).second.setPosition(sf::Vector2f(904.f + (it->first - num) * 550, 460.f));
						(*it).second.setScale(PLAYERSCALEBEFORE);
					}
					(*itr).second.setScale(PLAYERSCALEAFTER);
					currentnum--;
				}
			}
		}
		else
		{
			this->next2.setSize(sf::Vector2f(100.f, 100.f));
			this->next2.setPosition(sf::Vector2f(0.f, 490.f));
		}

		button_itr->second->update(this->mousePosView);

		if ((button_itr)->second->isPressed())
		{

			if (stateinfo.isplayerlocked.find(button_itr->first)->second)
			{
				this->stateinfo.isplayerlocked.find(button_itr->first)->second = 0;
				this->stateinfo.coins -= cost.at(button_itr->first);
				this->coins.setString(std::to_string(this->stateinfo.coins));

				this->sound.play();

				button_itr->second->DeRenameButton("Select");
				for (auto it = buttons.begin(); it != buttons.end(); ++it)
				{
					if (it != buttons.begin() && it != button_itr && stateinfo.isplayerlocked.find(it->first)->second)
					{
						if (stateinfo.coins < cost.at(it->first))
						{
							it->second->RenameButton("Locked");
							it->second->FrezzeButton();
						}

						if (stateinfo.coins >= cost.at(it->first))
						{
							it->second->RenameButton("Unlock");
						}
					}
				}
			}

			else /*if (button_itr->second->GetButtonName() == "Select")*/
			{
				for (auto it = buttons.begin(); it != buttons.end(); ++it)
				{
					if (stateinfo.isplayerlocked.find(it->first)->second == 0)
					{
						it->second->DeRenameButton("Select");
						it->second->DefrezzeButton();
					}
				}

				stateinfo.activetexture = button_itr->first;
				stateinfo.activetexturenum = itr->first;
				this->button_itr->second->RenameButton("Selected");
				this->button_itr->second->FrezzeButton();
			}
		}

		time = 0;
	}

	this->sprite.setTextureRect(anim->r);
	anim->update(0, 0, dt);
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
	if (this->button_itr->first != "Player_body")
	{
		Cost.setFont(font);
		Cost.setFillColor(sf::Color::Black);
		Cost.setString(std::to_string(this->cost.find(button_itr->first)->second));
		Cost.setCharacterSize(COST_CHARACTER_SIZE);
		Cost.setPosition(COST_POSITION);
	}

}

void PlayerInfo::update(const float& dt)
{
	this->updateMousePositions(window->getView());
	this->updateInput(dt);

	this->updateButtons();
}

/////////////////////////////////// RENDER FUNCTIONS ////////////////////////////////////////////

void PlayerInfo::renderButtons(sf::RenderTarget* target)
{
	/*for (auto& it : this->buttons)
	{
		it.second->render(target);
	}*/

	button_itr->second->render(target);

}

void PlayerInfo::render(sf::RenderTarget* target)
{
	if (!target)
	{
		target = this->window;
	}

	target->draw(this->background);

	for (auto it = players.begin(); it != players.end(); ++it)
	{
		if (itr->first != it->first)
			target->draw(it->second);
		else
		{
			target->draw(this->sprite);
		}
	}
	target->draw(this->next1);
	target->draw(this->next2);
	target->draw(this->coins);
	target->draw(this->Coins);
	if (this->button_itr->first != "Player_body")
	{
		target->draw(this->Cost);
		target->draw(this->CoinsForCost);
	}
	this->renderButtons(target);
}
