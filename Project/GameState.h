#ifndef GAME_STATE_H

#define GAME_STATE_H

#include "State.h"
#include "collider.h"
#include "Tilemap.h"
#include "QuitState.h"

class GameState:
	public State
{
private:
	Player* player;
	std::vector<obstacle*> obstacles;
	std::vector<obstacle*> underground;
	sf::View view;

	bool is_game_over;
	bool check;

	//Functions
	void initKeybinds();
	void initobjects();

public:
	GameState(Statedata& state_info);
	virtual ~GameState();

	//Functions
	
	void updateInput(const float& dt);
	void update(const float& dt);
	void render(sf::RenderTarget* target = NULL);
	void resize(sf::RenderWindow* window,sf::View* view);

};

#endif