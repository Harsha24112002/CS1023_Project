#ifndef GAMEINFO_H
#define GAMEINFO_H

#include "GameState.h"
#include "PlayerInfo.h"
#include "LevelInfo.h"

class GameInfo : public State
{
private:
	//Variables
	 //Accessors
	 std::map<std::string, Button*> buttons;
	 
	 //sf Variables
	  //Textures
	  sf::Texture backgroundTexture;

	  //Rectangle shapes
	  sf::RectangleShape background;
	  sf::RectangleShape back;
	  
	  //assets/Fonts
	  sf::Font font;
	
	//Init Functions
	/**
	* @brief Initializes the background of the GameInfo State.
	*/
	void initBackground();
	/**
	* @brief initalizes assets/Fonts used in the GameInfo State .
	*/
	void initFonts();
	/**
	* @brief initalizes the GameInfo State buttons.
	*/
	void initButtons();

public: 
	//Constructor, Destructor
	/**
	* @brief Constructor of GameInfo.
	* @param reference to Statedata.
	*/
	GameInfo(Statedata& state_info);
	virtual ~GameInfo();

	//Functions
	 //Update Functions

	 /**
	 * @brief updates the input from the user.
	 * @param dt - delta time.
	 */
	 void updateInput(const float& dt);
	 /**
	 * @brief updates the buttons functionality.
	 */
	 void updateButtons();
	 /**
	 * @brief updates the all updated functions and events of current state.
	 * @param dt - delta time.
	 */
	 void update(const float& dt);

	 //Render Functions
	 /**
	 * @brief displays the buttons.
	 * @param sf::RenderTarget*
	 */
	 void renderButtons(sf::RenderTarget* target = NULL);
	 /**
	 * @brief displays GameInfo State objects.
	 * @param sf::RenderTarget*
	 */
	 void render(sf::RenderTarget* target = NULL);

};

#endif
