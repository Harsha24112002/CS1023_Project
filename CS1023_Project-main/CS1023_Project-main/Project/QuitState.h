#ifndef QUIT_STATE
#define QUIT_STATE

#include "State.h"
#include "Button.h"

class QuitState : public State
{
private:

	//Variables
	sf::Texture backgroundTexture;
	std::map<std::string, Button*> buttons;
	sf::RectangleShape background;
	sf::Font font;

	//Functions
	void initBackground();
	void initFonts();
	void initButtons();
public:
	QuitState(Statedata& state_info);
	virtual ~QuitState();

	void updateInput(const float& dt);
	void updateButtons();
	void update(const float& dt);
	void renderButtons(sf::RenderTarget* target = NULL);
	void render(sf::RenderTarget* target = NULL);
};

#endif