#ifndef PAUSEMENU_H
#define PAUSEMENU_H

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <sstream>
#include <fstream>
#include <stack>
#include <map>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>

#include "Button.h"
#include "SoundEffects.h"

class PauseMenu
{
private:
	sf::RectangleShape container;
	sf::Font& font;
	sf::Text menuText;

	std::map<std::string, Button*> buttons;

public:
	PauseMenu(sf::View* view, sf::Font& font);
	virtual ~PauseMenu();

	std::map<std::string, Button*>& getButtons();
	
	int volumeBar = 10;
	SoundEffects* buttonSound;
	sf::RectangleShape volumeLevel[15];

	const bool isButtonPressed(const std::string key);
	void addButton(const std::string key, float y, std::string text);
	void initSound();
	void update(const sf::Vector2f& mousePos);
	void render(sf::RenderTarget& target);
};


#endif // !PAUSEMENU_H

