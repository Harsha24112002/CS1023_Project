#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "collider.h"
#include "Tilemap.h"
#include "QuitState.h"
#include "Levelup.h"
#include "PlayerAttributes.h"
#include "PauseMenu.h"
#include "SoundEffects.h"

#include <list>

class GameState :
	public State
{
private:
	//Variables
	 //sf Variables
	  //Textures and Sprites
	  sf::Texture* PlayerTexture;
	  sf::RenderTexture rendertexture;
	  sf::Sprite rendersprite;

	  //assets/Fonts
	  sf::Font font;

	  //Views
	  sf::View view;
	 
	  //background
	  sf::Sprite background;

	 //Objects
	 PauseMenu* pmenu;
	 Player* player;
	 Tilemap* tilemap;
	 PlayerAttributes* attributes;

	 //Accessors
	 /**
	 * @brief checks if the player has fallen or not.
	 */
	 bool is_game_over;
	 bool first;
	 
	 //Time Variables
	 float time;

	 //File Variables
	 std::list<std::string> file;

	//Functions
	sf::Vector2i getPlayergrid();

	 //Init Functions

	 void initRenderTexture();
	 /**
	 * @brief initializes the view of the GameState.
	 */
	 void initView();
	 /**
	 * @brief initializes the assets/Fonts used in the GameState.
	 */
	 void initFonts();
	 /**
	 * @brief initalizes the PauseMenu requirements.
	 */
	 void initPauseMenu();
	 /**
	 * @brief initalizes the GameState Background.
	 */
	 void initBackground();
	 /**
	 * @brief initalizes the GameState Objects.
	 */
	 void initobjects();
	 /*
	 * @brief initalizes the Sounds used in the GameState.
	 */
	 void initSounds();

public:
	//Constructor, Destructors
	/*
	* @brief Constructor of GameState.
	* @param reference to Statedata.
	*/
	GameState(Statedata& state_info);
	virtual ~GameState();
	
	/*
	* @brief sounds used in the GameState.
	*/
	SoundEffects* jump, * lost, * won;

	//Functions
	 //Update Functions
	/*
	* @brief updates the paused input.
	* @param dt - delta time.
	*/
	 void updatePausedInput(const float& dt);
	 /**
	 * @brief updates the input from the user.
	 * @param dt - delta time.
	 */
	 void updateInput(const float& dt);
	 /**
	 * @brief updates the buttons functionality.
	 */
	 void updateButtons();

	 void updateLevel();
	 /**
	 * @brief updates the volume.
	 */
	 void updateVolume(int vol);
	/**
	* @brief updates the all updated functions and events of current state.
	* @param dt - delta time.
	*/
	 void update(const float& dt);
	 
	 //Render Functions
	/**
	* @brief displays LevelInfo State objects.
	* @param sf::RenderTarget*
	*/
	 void render(sf::RenderTarget* target = NULL);

	 /**
	 * @brief resizes the window
	 * @param sf::RenderWindow* , sf::View*
	 */
	 void resize(sf::RenderWindow* window, sf::View* view);
};

#endif
