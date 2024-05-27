#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include "GameInfo.h"
#include "Settings.h"
#include "InterfaceState.h"

class MainMenuState :
    public State
{
private:
	//Variables
	sf::Texture backgroundTexture;
	sf::RectangleShape background;
	sf::Font font;

	std::map<std::string, Button*> buttons;

	//Init Functions
	/**
	* @brief initializes the MainMenuState variables.
	*/
	void initVariables();
	/**
	* @brief initalizes the MainMenuState background.
	*/
	void initBackground();
	/**
    * @brief initalizes assets/Fonts used in the MainMenuState .
    */
	void initFonts();
	/**
    * @brief initalizes the MainMenuState buttons.
    */
	void initButtons();

public:
	//Constructor, Destructor
	/**
	* @brief Constructor of MainMenuState.
	* @param reference to Statedata.
	*/
	MainMenuState(Statedata& state_info);
	virtual ~MainMenuState();

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
	* @brief displays MainMenuState objects.
	* @param sf::RenderTarget*
	*/
	void render(sf::RenderTarget* target = NULL);
};

#endif
