#include "Button.h"
#include <fstream>
#include <stack>
#include "State.h"
#include <vector>
#include "Tilemap.h"

#ifndef INTERFACESTATE_H
#define INTERFACESTATE_H


class Interface : public State
{
	private:
	void initKeybinds();
	std::map<std::string,Button*> buttons;	
	Tilemap* tilemap;
	sf::RectangleShape rect;
	sf::IntRect texrect;
	public:
	
	Interface(Statedata& state_info);

	void updatemousepos();
	void update(const float& dt);
	void updateInput(const float& dt);
	void render(sf::RenderTarget* target);
};
#endif