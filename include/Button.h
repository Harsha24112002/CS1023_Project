#ifndef BUTTON_H
#define BUTTON_H

#define BUTTON_DEFAULT_SIZE 40
#define BUTTON_ZOOMED_SIZE 60

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <sstream>
#include <fstream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

enum button_states { BTN_IDLE = 0, BTN_HOVER, BTN_ACTIVE };

class Button
{
private:
	//Variables
	 //Accessors
	 unsigned buttonStates;
	 bool isButtonFrezzed;

	 //sf Variables
	 sf::RectangleShape shape;
	 sf::Font* font;
	 sf::Text text;
	 sf::SoundBuffer buffer;
	 sf::Sound sound;

	 sf::Color idleColor;
	 sf::Color hoverColor;
	 sf::Color activeColor;

	 //Init Functions
	 /*
	 * @brief initializes the button clicking sound.
	 */
	 void initSound();

public:
	//Constructor, Destructor
	/*
	* @brief Constructor for the button 
	* @param button position, size, font, text, idleColor, hoverColor, activeColor,
	*/
	Button(float x, float y, float width, float height,
		sf::Font* font, std::string text,
		sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor);
	
	virtual ~Button();


	//Accessors
	/*
	* @brief checks if the buttons is pressed or not with the help of enum button_states.
	*/
	const bool isPressed() const;
	/*
	* @brief renames the button and puts the button color and size to green color and 60 respectively.
	* @param std::string.
	*/
	void RenameButton(std::string str);
	/*
	* @brief renames the buttons and puts the button color and size to black color and 40 respectively.
	* @param std::string
	*/
	void DeRenameButton(std::string str);
	/*
	* @brief FrezzeButton sets the boolen isButtonFrezzed to true.
	*/
	void FrezzeButton();
	/*
	* @brief DefrezzeButton sets the boolen isButtonFrezzed to false.
	*/
	void DefrezzeButton();
	/*
	* @brief ChangeMusicTo changes the button music to desired sound.
	* @param std::string
	*/
	void ChangeMusicTo(std::string);

	//Update and Render Functions
	/*
	* @brief updates the button pressing by different modes.
	* @param mouseposition for checking the click.
	*/
	void update(const sf::Vector2f& mousePos);
	/*
	* @brief displays the buttons.
	* @param sf::RenderTarget*.
	*/
	void render(sf::RenderTarget* target);


};

#endif
