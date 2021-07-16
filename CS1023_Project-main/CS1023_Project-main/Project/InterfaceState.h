#include "Button.h"
#include "PauseMenu.h"
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
	Tilemap* tilemap;
	std::string filename;
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
	PauseMenu* pmenu;
	void InitButtons();
	void initView();
	void initHelpKeys();
	void updatePausedInput(const float& dt);
	public:
	
	Interface(Statedata& state_info);
	~Interface();

	void updateButtons();
	void update(const float& dt);
	void updateInput(const float& dt);
	void render(sf::RenderTarget* target);
};
#endif