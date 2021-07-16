
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
	 filename = "Tilepositions.txt";
	
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
	this->InitButtons();
}

Interface::~Interface()
{
	delete textureselector;
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

void Interface::InitButtons()
{
	this->pmenu = new PauseMenu(&this->view, this->f);

	this->pmenu->addButton("LOAD", 200.f, "LOAD");
	
	this->pmenu->addButton("LOAD2", 300.f, "LOAD2");

	this->pmenu->addButton("QUIT", 400.f, "QUIT");

	//this->pmenu->addButton("EXIT_STATE", 600.f, "QUIT");

}

void Interface::updateButtons()
{
	if(pmenu->isButtonPressed("LOAD"))
	{
		filename="Tilepositions.txt";
		tilemap->Loadfromfile(filename);
	}
	if(pmenu->isButtonPressed("LOAD2"))
	{
		filename="Tilepositions2.txt";
		tilemap->Loadfromfile(filename);
	}
	if(pmenu->isButtonPressed("QUIT"))
	{
		tilemap->savetofile(filename);
		this->endState();
	}
	
	
}
void Interface::updatePausedInput(const float& dt)
{

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)&& keytime>0.5f)
	{
		keytime=0.0f;
		if (!this->paused)
			this->pauseState();
		else
			this->unpauseState();
	}
}
void Interface::update(const float& dt)
{
	
	keytime += dt;
	updateMousePositions(view);
	updatePausedInput(dt);
	this->updateInput(dt);

	if(!paused)
	{
	tilemap->update(sf::Vector2i((view.getCenter().x / stateinfo.gridsize), (view.getCenter().y / stateinfo.gridsize)),dt);
	

	textureselector->update(mousePosWindow);
	rect.setPosition(sf::Vector2f((float)mousePosGrid.x * stateinfo.gridsize, (float)mousePosGrid.y * stateinfo.gridsize));
	mousetext.setPosition(mousePosView.x + 10, mousePosView.y - 10);
	mousetext.setString("collision : " + std::to_string(collision) + "\n" + "Type: " + std::to_string(type));
	}
	else
	{
		this->pmenu->update(this->mousePosView);
		this->updateButtons();
	}
	
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
		if(tilemap)
		{
		tilemap->render(target);
		}

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
	if(paused)
	{
		pmenu->render(*target);
	}

}


void Interface::initKeybinds()
{

}

void Interface::updateInput(const float& dt)
{
	if(!paused)
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
					tilemap->addtile(mousePosGrid.x, mousePosGrid.y, texrect, type, collision);
				}
				else
				{
					texrect = textureselector->getTexturerect();
				}
			}
			if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
			{
				tilemap->removetile(mousePosGrid.x, mousePosGrid.y);
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
}

