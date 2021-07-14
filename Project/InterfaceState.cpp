
#include "InterfaceState.h"

Interface::Interface(Statedata& state_info) :State(state_info)
{
	tilemap = new Tilemap(stateinfo.gridsize, 1000, 500);
	rect.setPosition(this->mousePosView);
	rect.setSize(sf::Vector2f(stateinfo.gridsize, stateinfo.gridsize));
	rect.setOutlineColor(sf::Color::Green);
	rect.setOutlineThickness(1.0f);
	rect.setFillColor(sf::Color::Transparent);
	this->texrect = sf::IntRect(0, 0, (int)stateinfo.gridsize, (int)stateinfo.gridsize);
	textureselector = new TextureSelector(20, 20, 10, 10, stateinfo.gridsize, tilemap->getTilesheet());
	std::string filename = "Tilepositions.txt";
	tilemap->Loadfromfile(filename);
	type = 0;
	collision = false;
	helpWindow = false;
	keytime = 0.0f;

	f.loadFromFile("Fonts/BodoniFLF-Bold.ttf");

	mousetext.setFont(f);
	mousetext.setString(std::to_string(collision));
	mousetext.setPosition(mousePosView);
	mousetext.setFillColor(sf::Color::White);
	mousetext.setCharacterSize(15);

	this->help.setSize(sf::Vector2f(80.0f, 80.0f));
	this->help.setPosition(sf::Vector2f(1840.0f, 0.0f));
	this->help.setTexture(&(State::textures["Help_Image"]));

	this->close.setSize(sf::Vector2f(50.0f, 50.0f));
	this->close.setPosition(sf::Vector2f(this->window->getView().getCenter().x - 960.0f + 50.f, this->window->getView().getCenter().x - 540.0f + 50.f));
	this->close.setTexture(&(State::textures["Close_Image"]));

	this->initView();
	this->initHelpKeys();
}

Interface::~Interface()
{
	delete textureselector;

	for (auto& a : buttons)
	{
		delete a.second;
	}
}


void Interface::initView()
{
	view.setSize(window->getDefaultView().getSize());
	view.setCenter(window->getSize().x / 2.0f, window->getSize().y / 2.0f);
}

void Interface::initHelpKeys()
{
	sf::Text buffertext;
	buffertext.setFont(f);
	buffertext.setString("A - Move the View Left");
	buffertext.setPosition(sf::Vector2f(810.0f, 115.0f));
	buffertext.setFillColor(sf::Color::Black);
	this->keys.push_back(sf::Text(buffertext));

	buffertext.setFont(f);
	buffertext.setString("S - Move the View Down");
	buffertext.setPosition(sf::Vector2f(810.0f, 215.0f));
	buffertext.setFillColor(sf::Color::Black);
	this->keys.push_back(sf::Text(buffertext));

	buffertext.setFont(f);
	buffertext.setString("D - Move the View Right");
	buffertext.setPosition(sf::Vector2f(810.0f, 315.0f));
	buffertext.setFillColor(sf::Color::Black);
	this->keys.push_back(sf::Text(buffertext));

	buffertext.setFont(f);
	buffertext.setString("W - Move the View Up");
	buffertext.setPosition(sf::Vector2f(810.0f, 415.0f));
	buffertext.setFillColor(sf::Color::Black);
	this->keys.push_back(sf::Text(buffertext));

	buffertext.setFont(f);
	buffertext.setString("Up arrow, Down arrow to change types");
	buffertext.setPosition(sf::Vector2f(810.0f, 515.0f));
	buffertext.setFillColor(sf::Color::Black);
	this->keys.push_back(sf::Text(buffertext));

	buffertext.setFont(f);
	buffertext.setString("T - To toggle the collison");
	buffertext.setPosition(sf::Vector2f(810.0f, 615.0f));
	buffertext.setFillColor(sf::Color::Black);
	this->keys.push_back(sf::Text(buffertext));

	buffertext.setFont(f);
	buffertext.setString("C - To close the texture selector");
	buffertext.setPosition(sf::Vector2f(810.0f, 715.0f));
	buffertext.setFillColor(sf::Color::Black);
	this->keys.push_back(sf::Text(buffertext));

	buffertext.setFont(f);
	buffertext.setString("O - To open the texture selector");
	buffertext.setPosition(sf::Vector2f(810.0f, 815.0f));
	buffertext.setFillColor(sf::Color::Black);
	this->keys.push_back(sf::Text(buffertext));


}

void Interface::updatemousepos()
{
	updateMousePositions(view);
	for (auto& a : buttons)
	{
		a.second->update(mousePosView);
	}
}
void Interface::update(const float& dt)
{
	keytime += dt;
	updatemousepos();
	tilemap->update(sf::Vector2i((view.getCenter().x / stateinfo.gridsize), (view.getCenter().y / stateinfo.gridsize)));
	this->updateInput(dt);

	textureselector->update(mousePosWindow);
	rect.setPosition(sf::Vector2f((float)mousePosGrid.x * stateinfo.gridsize, (float)mousePosGrid.y * stateinfo.gridsize));
	mousetext.setPosition(mousePosView.x + 10, mousePosView.y - 10);
	mousetext.setString("collision : " + std::to_string(collision) + "\n" + "Type: " + std::to_string(type));

}

void Interface::render(sf::RenderTarget* target)
{
	if (!target)
	{
		target = this->window;
	}

	if (!helpWindow)
	{
		target->setView(view);
		tilemap->render(target);
		this->help.setPosition(sf::Vector2f(target->getView().getCenter().x + 960.0f - 80, target->getView().getCenter().y - 540.0f));
		if (!this->help.getGlobalBounds().contains(this->mousePosView))
		{
			if (!textureselector->getactive())
			{
				target->draw(rect);
			}
			target->draw(mousetext);
		}
		target->setView(target->getDefaultView());
		this->help.setPosition(sf::Vector2f(target->getView().getCenter().x + 960.0f - 80, target->getView().getCenter().y - 540.0f));
		for (auto& a : buttons)
		{
			a.second->render(target);
		}
		textureselector->render(target);

		target->draw(this->help);
		
	}
	
	if (helpWindow)
	{
		target->setView(target->getDefaultView());
		for (auto it = keys.begin(); it != keys.end(); ++it)
		{
			target->draw(*it);
		}
		this->close.setPosition(sf::Vector2f(target->getView().getCenter().x - 960.0f , target->getView().getCenter().y - 540.0f ));
		
		target->draw(this->close);
		this->close.setPosition(sf::Vector2f(target->getView().getCenter().x - 960.0f, target->getView().getCenter().y - 540.0f));
	}

}


void Interface::initKeybinds()
{

}

void Interface::updateInput(const float& dt)
{
	if (!helpWindow)
	{
		if (!this->help.getGlobalBounds().contains(this->mousePosView))
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			{
				view.move(-100 * dt, 0);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			{
				view.move(100 * dt, 0);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			{
				view.move(0, -100 * dt);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			{
				view.move(0, 100 * dt);
			}

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				if (!textureselector->getactive())
				{
					tilemap->addtile(mousePosGrid.x, mousePosGrid.y, 0, texrect, type, collision);
				}
				else
				{
					texrect = textureselector->getTexturerect();
				}
			}
			if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
			{
				tilemap->removetile(mousePosGrid.x, mousePosGrid.y, 0);
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				std::string s = "Tilepositions.txt";
				tilemap->savetofile(s);
				this->endState();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::T) && keytime > 1.0f)
			{
				if (collision)
				{
					collision = false;
				}
				else collision = true;
				keytime = 0.0f;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && keytime > 1.0f)
			{
				++type;
				keytime = 0.0f;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && keytime > 1.0f)
			{
				type--;
				keytime = 0.0f;
			}
		}
		this->window->setView(view);
		this->help.setPosition(sf::Vector2f(this->window->getView().getCenter().x + 960.0f - 80, this->window->getView().getCenter().y - 540.0f));
		if (this->help.getGlobalBounds().contains(this->mousePosView))
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				helpWindow = true;
			}
		}
		this->help.setPosition(sf::Vector2f(this->window->getView().getCenter().x + 960.0f - 80, this->window->getView().getCenter().y - 540.0f));
		
	}

	else if (helpWindow)
	{
		this->window->setView(view);
		this->close.setPosition(sf::Vector2f(this->window->getView().getCenter().x - 960.0f, this->window->getView().getCenter().y - 540.0f));
		if (this->close.getGlobalBounds().contains(this->mousePosView))
		{
			this->close.setSize(sf::Vector2f(100.0f, 100.0f));
			this->close.setPosition(sf::Vector2f(this->window->getView().getCenter().x - 960.0f , this->window->getView().getCenter().y - 540.0f ));
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				helpWindow = false;
			}
		}
		else
		{
			this->close.setSize(sf::Vector2f(50.0f, 50.0f));
			this->close.setPosition(sf::Vector2f(this->window->getView().getCenter().x - 960.0f , this->window->getView().getCenter().y - 540.0f ));
		}
		//this->close.setPosition(sf::Vector2f(this->window->getView().getCenter().x - 960.0f, this->window->getView().getCenter().y - 540.0f));
	}
}

