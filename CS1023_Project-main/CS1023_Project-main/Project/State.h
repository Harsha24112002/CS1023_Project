#ifndef STATE_H
#define STATE_H


#include "Player.h"

class State;
class Statedata
{
public:
	Statedata() {};
	sf::RenderWindow* window;
	std::stack<State*>* states;
	std::string activetexture;
	unsigned activetexturenum;
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
	bool paused;
	bool totalquit;
	bool playagain;
	Statedata& stateinfo;
	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;
	sf::Vector2u mousePosGrid;
	//Resources 
	std::map<std::string, sf::Texture> textures;
	sf::Texture playerbody;

	//Functions 

public:
	State(Statedata& stateinfo);
	virtual ~State();

	bool getQuit();
	const bool& getTotalQuit() const;
	const bool& getPlayAgain() const;

	void endState();
	void pauseState();
	void unpauseState();
	void QuitGame();

	virtual void updateMousePositions(sf::View view);
	void PlayAgain();
	void inittextures();

	virtual void updateInput(const float& dt) = 0;
	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget* target = nullptr) = 0;
};

#endif
