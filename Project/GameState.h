#ifndef GAME_STATE_H

#define GAME_STATE_H

#include "State.h"
#include "collider.h"
#include "Tilemap.h"
#include "QuitState.h"
#include "PlayerAttributes.h"
#include "PauseMenu.h"

class GameState :
	public State
{
private:
	sf::Font font;
	PauseMenu* pmenu;

	Player* player;
	sf::View view;
	Tilemap* tilemap;
	PlayerAttributes* attributes;
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

	void initFonts();
	void initPauseMenu();

	//Functions
	void initBackground();
	void initKeybinds();
	void initobjects();
	sf::Vector2i getPlayergrid();
public:
	GameState(Statedata& state_info);
	virtual ~GameState();

	//Functions

	void updatePausedInput(const float& dt);
	void updateInput(const float& dt);
	void updateButtons();

	void update(const float& dt);
	void render(sf::RenderTarget* target = NULL);
	void resize(sf::RenderWindow* window, sf::View* view);

};

#endif