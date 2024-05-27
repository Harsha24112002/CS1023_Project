#ifndef LEVELUP_H
#define LEVELUP_H
#include "State.h"
#include "Button.h"

class Levelup : public State
{
	private:
	std::map<std::string,Button*> buttons;	
	void initButtons();
	sf::Font font;
	sf::Text text1;
	sf::Text text2;
	sf::Text text;
	unsigned totalscore;
	unsigned levelscore;
	//bool& gonext;

	public:
	Levelup(Statedata& stateinfo);
	
	virtual ~Levelup();
	void update(const float& dt);
	void updateInput(const float& dt){};
	void render(sf::RenderTarget* target);

};

#endif