#ifndef STATE_H
#define STATE_H


#include "Player.h"
#include "obstacle.h"
class State;
class Statedata
{
	public:
	Statedata(){};
	sf::RenderWindow* window;
	std::stack<State*>* states;
	float gridsize;
};



class State
{
private:



protected:
	std::stack<State*>* states;
	sf::RenderWindow* window;
	std::map<std::string, int>* supportedKeys;
	std::map<std::string, int> keybinds;
	bool quit;
	Statedata& stateinfo;
	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;
	sf::Vector2u mousePosGrid;
	//Resources 
	std::map<std::string,sf::Texture> textures;

	//Functions 
	
public:
	State(Statedata& stateinfo);
	virtual ~State();

	bool getQuit() ;

	void endState();
	virtual void updateMousePositions();
	void inittextures();

	virtual void updateInput(const float& dt) = 0;
	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget* target = nullptr) = 0;
};

#endif
