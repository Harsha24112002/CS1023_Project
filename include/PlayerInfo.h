#ifndef PLAYERINFO_H
#define PLAYERINFO_H

#define NEXT_IMAGE_POSITION sf::Vector2f(1820.f, 490.f)
#define NEXT_IMAGE_SIZE sf::Vector2f(100.f, 100.f)
#define PREVIOUS_IMAGE_POSTION sf::Vector2f(0.f, 490.f)
#define PREVIOUS_IMAGE_SIZE sf::Vector2f(100.f, 100.f)
#define coins_POSITION sf::Vector2f(1630, 195)
#define coins_CHARACTER_SIZE 35
#define COINS_POSTION sf::Vector2f(1580.f, 200.f)
#define COINS_SIZE sf::Vector2f(35.0f, 35.0f)
#define COINSFORCOST_POSITION sf::Vector2f(940.f, 405.f)
#define COINSFORCOST_SIZE sf::Vector2f(45.0f, 45.0f)
#define COST_POSITION sf::Vector2f(990.0f, 400.0f)
#define COST_CHARACTER_SIZE 45
#define PLAYERPOSTION sf::Vector2f(904.f, 460.f)
#define PLAYERSIZE sf::Vector2f(56.f, 80.f)
#define PLAYERSCALEBEFORE 2, 2
#define PLAYERSCALEAFTER 3, 3

#include "State.h"
#include "Button.h"
#include "GameState.h"
#include "animation.h"

class PlayerInfo :
	public State
{
private:

	//Variables
	 //sf Variables
	  //Rectangle shapes
	sf::RectangleShape background;
	sf::RectangleShape next1;
	sf::RectangleShape next2;
	sf::RectangleShape rect;
	sf::RectangleShape Coins;
	sf::RectangleShape CoinsForCost;

	//textures
	sf::Texture backgroundTexture;

	//assets/Fonts
	sf::Font font;
	sf::Font font1;

	//Coins
	sf::Text coins;
	sf::Text Cost;

	//Sound Variables
	sf::SoundBuffer buffer;
	sf::Sound sound;

	//Sprites
	sf::Sprite sprite;

	//Time Variables
	float time;

	//Animation
	animation* anim;

	//Accessors
	std::map<std::string, Button*> buttons;
	std::map<std::string, unsigned> cost;
	/**
	* @brief std::map of int and sf::RectangleShape which
	* stores the int value for updating the current active texture
	* of the player to the GameState.
	*/
	std::map<int, sf::RectangleShape> players;
	size_t currentnum;
	Button* PlayGameButton;

	//Iterators
	/**
	* @brief iterator which iterates through the map for displaying the
	* players.
	*/
	std::map<int, sf::RectangleShape>::iterator itr;
	/**
	* @brief iterator which iterates through the map for displaying the
	* current button.
	*/
	std::map<std::string, Button*>::iterator button_itr;


	//Init Functions
	 /**
	 * @brief Initializes the background and the required backgrounds for the
	 * PlayerInfo state.
	 */
	void initBackground();
	/**
	* @brief Initializes the assets/Fonts used in the PlayerInfo State.
	*/
	void initFonts();
	/**
	* @brief Initializes the coins which will be used for buying the players.
	*/
	void initCoins();
	/**
	* @brief Initializes the buttons of PlayerInfo State.
	*/
	void initButtons();
	/**
	* @brief Initializes the Players which are displayed on the screen.
	*/
	void initPlayers();

public:
	//Constructor, Destructor
	PlayerInfo(Statedata& state_info);
	virtual ~PlayerInfo();

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