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

	//Time Variables
	sf::Clock dtClock;
	float dt;

	//Stack of states
	std::stack<State*> states;

	std::map<std::string, int> supportedKeys;

	//Init Functions
	void initVariables();
	void initWindow();
	void initStateinfo();
	void initStates();
	

public:
	//Constructor, Destructor
	Game();
	virtual ~Game();

	//Accessors
	
	/**
	* @brief endApplication displays the text "Ending Application" on console when game window is closed.
	*/
	void endApplication();

	//Update Functions

	/**
	* @brief Updates the delta time (with the time it takes to update and render one frame).
	*/
	void updateDt();
	/**
	* @brief Updates the sfml events by sf::Event type.
	*/
	void updateSFMLEvents();
	/**
	* @brief Updates the events of whole stack of states.
	*/
	void update();

	//Render Functions
	/**
	* @brief displays the current state information.
	*/
	void render();

	//Core
	/**
	* @brief runs all the update, render functions in the main.
	*/
	void run();
};

#endif