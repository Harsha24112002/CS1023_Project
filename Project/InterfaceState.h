#include "Button.h"
#include <fstream>
#include <stack>
#include "State.h"
#include <vector>
#include "Tilemap.h"
#include "TextureSelector.h"
#ifndef INTERFACESTATE_H
#define INTERFACESTATE_H


class Interface : public State
{
	private:
	void initKeybinds();
	std::map<std::string,Button*> buttons;	
	Tilemap* tilemap;
	sf::RectangleShape rect;
	sf::RectangleShape close;
	sf::IntRect texrect;
	sf::RectangleShape help;
	TextureSelector* textureselector;
	sf::View view;
	sf::Font f;
	sf::Text mousetext;
	int type;
	bool collision;
	bool helpWindow;
	float keytime;
	std::vector<sf::Text> keys;

	void initView();
	void initHelpKeys();
	public:
	
	Interface(Statedata& state_info);
	~Interface();

	void updatemousepos();
	void update(const float& dt);
	void updateInput(const float& dt);
	void render(sf::RenderTarget* target);
};
#endif