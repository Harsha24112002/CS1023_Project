#ifndef GAME_STATE_H

#define GAME_STATE_H

#include "State.h"
#include "collider.h"
#include "Tilemap.h"
#include "QuitState.h"

class GameState :
	public State
{
private:
	Player* player;
	sf::View view;
	Tilemap* tilemap;

	sf::RenderTexture rendertexture;
	sf::Sprite rendersprite;
	bool is_game_over;
	bool check;

	//Functions
	void initRenderTexture();
	void initView();
	float time;
	sf::RectangleShape background;
	sf::Texture* PlayerTexture;

	//Functions
	void initBackground();
	void initKeybinds();
	void initobjects();
	sf::Vector2i getPlayergrid();
public:
	GameState(Statedata& state_info);
	virtual ~GameState();

	//Functions

	void updateInput(const float& dt);
	void update(const float& dt);
	void render(sf::RenderTarget* target = NULL);
	void resize(sf::RenderWindow* window, sf::View* view);

};

#endif