#include "Button.h"
#include <fstream>
#include <stack>
#include "State.h"
#include <vector>

#ifndef INTERFACESTATE_H
#define INTERFACESTATE_H

bool alreadythere(sf::Vector2f);

class Interface : public State
{
	private:
	void initKeybinds();
	std::vector<sf::RectangleShape> a;
	sf::RectangleShape rect;
	

	public:
	
	Interface(sf::RenderWindow* window,std::stack<State*>* states);

	
	void update(const float& dt);
	void updateInput(const float& dt);
	void render(sf::RenderTarget* target);
};
#endif