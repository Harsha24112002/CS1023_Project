#ifndef INTERFACESTATE_H
#define INTERFACESTATE_H

#include "Button.h"
#include "PauseMenu.h"
#include <fstream>
#include <stack>
#include "State.h"
#include <vector>
#include "Tilemap.h"
#include "TextureSelector.h"
#define PMENUVIEWCENTER sf::Vector2f(560,540)


class Interface : public State
{
private:
	//Variables
	 //sf Variables
	  //Rectangle shapes
	  sf::RectangleShape rect;
	  sf::RectangleShape close;
	  sf::RectangleShape help;
	  sf::IntRect texrect;
	  
	  //View
	  sf::View view;
	  sf::View pauseview ;
	  //Font
	  sf::Font f;
	  
	  //Text
	  sf::Text mousetext;
	 
	 //Accessor Variables
	 Tiletype type;
	 int itype;
	 bool helpWindow;
	 float keytime;

	//Objects
	Tilemap* tilemap;
	PauseMenu* pmenu;
	TextureSelector* textureselector;

	std::string filename;
	std::vector<sf::Text> keys;

	//Init Functions

	/***
	 * @brief Initialising buttons used for Pause menu in the interfacestate
	 * */
	void InitButtons();
	/**
	 * @brief Setting up the 2D camera view for placing tiles using this interface 
	*/
	void initView();

	/** 
	 * @brief Initializing function for the help button in Interface
	*/
	void initHelpKeys();
	//Update function
	/**
	 * @brief Updates the input when the state is paused
	 * @param dt deltatime
	*/
	void updatePausedInput(const float& dt);
	/**
	 * @brief Updates the inputs
	 * @param dt deltatime
	 * */
	void updateInput(const float& dt);

	//Update Functions
	/**
	 * @brief Updates the buttons in Pausemenu of interfacestate
	*/
	void updateButtons();

public:
	//Constructor, Destructor
	/**
	 * @brief Constructor for the interface state
	 * @param state_info Takes the statesinfo with reference
	*/ 
	Interface(Statedata& state_info);
	~Interface();

	

	/** 
	 * @brief Updates the Interface
	 * @param dt deltatime
	 * */
	void update(const float& dt);
	//Render Functions
	/**
	 * @brief Renders the interface to the target
	 * @param target The target on which everything in the interface is to be rendered
	 * */
	void render(sf::RenderTarget* target);
};
#endif