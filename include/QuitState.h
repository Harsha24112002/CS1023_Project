#ifndef QUIT_STATE
#define QUIT_STATE

#include "State.h"
#include "Button.h"

class QuitState : public State
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

	  //assets/Fonts
	  sf::Font font;

	//Init Functions
	/**
	* @brief Initializes the background of the QuitState.
	*/
	void initBackground();
	/**
	* @brief Initializes the assets/Fonts used in the QuitState.
	*/
	void initFonts();
	/**
	* @brief Initalizes the buttons in the QuitState.
	*/
	void initButtons();
public:
	//Constructor, Destructor
	/**
	* @brief Constructor for the QuitState class which initalizes the required 
	* functionality for QuitState.
	* @param reference to Statedata.
	*/
	QuitState(Statedata& state_info);
	virtual ~QuitState();

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
	 * @brief updates the all updated functions.
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
	 * @brief displays QuitState objects.
	 * @param sf::RenderTarget*
	 */
	 void render(sf::RenderTarget* target = NULL);
};

#endif