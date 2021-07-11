#ifndef GAME_H
#define GAME_H

#include "MainMenuState.h"

class Game
{
private:
	//Variables
	sf::RenderWindow *window;
	sf::Event sfevent;
	std::vector<sf::VideoMode> videoModes;
	sf::ContextSettings windowSettings;
	Statedata state_info;
	bool fullscreen;

	sf::Clock dtClock;
	float dt;

	std::stack<State*> states;

	std::map<std::string, int> supportedKeys;


	void initVariables();
	void initWindow();
	void initStateinfo();
	void initStates();
	

public:
	Game();
	virtual ~Game();

	
	void endApplication();


	void updateDt();
	void updateSFMLEvents();
	void update();

	void render();

	void run();
};

#endif