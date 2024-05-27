#ifndef LEVELINFO_H
#define LEVELINFO_H

#define THEME_1_TEXTURE_SIZE sf::Vector2f(300.0f, 300.0f)
#define THEME_1_TEXTURE_POSITION sf::Vector2f(810.0f, 100.0f)
#define THEME_2_TEXTURE_SIZE sf::Vector2f(300.0f, 300.0f)
#define THEME_2_TEXTURE_POSITION sf::Vector2f(810.0f, 640.0f)

#include "State.h"
#include "Button.h"

class LevelInfo : public State
{
private:
	//Variables
	 //sf Variables
	 sf::RectangleShape rect;
	 sf::RectangleShape rect1;
	 sf::Font font;
	
	std::map<int, sf::RectangleShape> levels;
	std::map<std::string, Button*> buttons;

	//Functions
	/**
	* @brief Initializes the background of the LevelInfo State.
	*/
	void initBackground();
	/**
	* @brief Initalizes the assets/Fonts used in the LevelInfo State.
	*/
	void initFonts();
	/**
	* @brief Initalizes the buttons in the LevelInfo State.
	*/
	void initButtons();
public:
	//Constructors, Destructor
	/**
	* @brief Constructor for the LevelInfo class which initalizes the required
	* functionality for LevelInfo State.
	* @param reference to Statedata.
	*/
	LevelInfo(Statedata& state_info);
	virtual ~LevelInfo();

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
	 * @brief displays LevelInfo State objects.
	 * @param sf::RenderTarget*
	 */
	 void render(sf::RenderTarget* target = NULL);
};

#endif