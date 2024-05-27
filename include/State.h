#ifndef STATE_H
#define STATE_H

#include "Player.h"
#include <list>

class State;

class Statedata
{
public:
	//Constructor
	Statedata() {};
	
	//Window and States
	sf::RenderWindow* window;
	std::stack<State*>* states;
	
	//Player active texture and current player number
	std::string activetexture;
	unsigned activetexturenum;
	
	//Active level of game
	std::string activelevel;
	
	float gridsize;
	
	//Coins Picked in the gamestate
	unsigned coins;
	
	//Player locked or not
	std::map<std::string, int> isplayerlocked;

	std::list<std::string> activefiles;
};

class State
{
private:

protected:
	//Variables
	std::stack<State*>* states;
	sf::RenderWindow* window;
	
	std::map<std::string, int>* supportedKeys;
	std::map<std::string, int> keybinds;
	
	//Game Accessors
	bool quit;
	bool paused;
	bool totalquit;
	bool playagain;

	Statedata& stateinfo;
	
	//Mouse Position Variables
	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;
	sf::Vector2u mousePosGrid;

	//Resources 
	std::map<std::string, sf::Texture> textures;
	sf::Texture playerbody; 

public:
	//Constructor, Destructor
	/**
	* @brief Constructor for the State function.
	* @param reference to Statedata.
	*/
	State(Statedata& stateinfo);
	virtual ~State();

	//Game quiting accessors
	/**
	* @brief getQuit() function checks if the current state is active or not.
	* @return boolean.
	*/
	bool getQuit();
	/**
	* @brief getTotalQWit() function checks if whole game is active or not.
	* @return boolen.
	*/
	const bool& getTotalQuit() const;
	/**
	* @brief getTotalQuit() function checks if the playagain button is pressed 
	* or not if pressed only MainMenuState will be in the stack of states in game.cpp
	* @return boolen.
	*/
	const bool& getPlayAgain() const;

	//Game state changing functions

	/**
	* @brief endState() function changes the boolen quit to true for quiting the current state.
	*/
	void endState();
	/**
	* @brief pauseState() function changes the boolen paused to true for pausing the current state.
	*/
	void pauseState();
	/**
	* @brief unpauseState() function changes the boolen paused to false for unpausing the current state.
	*/
	void unpauseState();
	/**
	* @brief QuitGame() function changes the boolen totalquit to true for total quiting the game.
	*/
	void QuitGame();
	/**
	* @brief PlayAgain() function changes the boolen playagain to true for deleting all states in stack
	* other than MainMenuState.
	*/
	void PlayAgain();

	//MousePostions Update
	/**
	* @brief update the mouse positions.
	* @param sf::View
	*/
	virtual void updateMousePositions(sf::View view);

	//Init Variables
	/**
	* @brief initializes all the textures which are used in the states.
	*/
	void inittextures();

	//Update and Render Functions
	/**
	* @brief updateInput is a pure virtual function which will be used by the subclasses and
	* implement their own functionality for updating the user input.
	* @param dt - delta time
	*/
	virtual void updateInput(const float& dt) = 0;
	/**
	* @brief update is a pure virtual function which will be used by the subclasses and 
	* implement their own functionality for updating the all updates in the inherited classes.
	* @param dt - delta time
	*/
	virtual void update(const float& dt) = 0;
	/**
	* @brief render is a pure virtual function which will be used by the subclasses and
	* implement thier own functionality for rendering(displaying) the objects of inherited classes.
	* @param sf::RenderTarget*
	*/
	virtual void render(sf::RenderTarget* target = nullptr) = 0;
};

#endif
