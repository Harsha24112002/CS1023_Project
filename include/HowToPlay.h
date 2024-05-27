#ifndef HOWTOPLAY_H
#define HOWTOPLAY_H

#include "State.h"
#include "Button.h"

class HowToPlay : public State
{
private:
	//Variables
	 //sf Variables
	  //Rectangle shape
	sf::RectangleShape background;
	sf::RectangleShape image;
	sf::CircleShape pointer;

	//View
	sf::View view;

	//assets/Fonts
	sf::Font font;

	//Text
	sf::Text menuText;
	sf::Text briefText;

	std::map<std::string, Button*> buttons;

	sf::Texture tex;

	//Init Functions
	void initBackground();
	void initView();
	void initFonts();
	void initButtons();
	void initImage();
	void initTexture();
	void initCircle();
	void setBriefTextPosition();

public:
	//Constructor, Destructor
	HowToPlay(Statedata& state_info);
	virtual ~HowToPlay();

	//Functions
	std::map<std::string, Button*>& getButtons();

	void addButton(const std::string key, float y, std::string text);
	const bool isButtonPressed(const std::string key);

	//Update Functions
	void updateButtons();
	void update(const float& dt);
	void updateInput(const float& dt);

	//Render Functions
	void render(sf::RenderTarget* target = NULL);
};

#endif // !HOWTOPLAY_H
