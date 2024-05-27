#ifndef TEXTURESELECTOR_H
#define TEXTURESELECTOR_H

#include <SFML/Graphics.hpp>

class TextureSelector
{
private:
	//Accessor Variables
	bool active;
	float gridsize;
	bool hidden;
	
	//sf Variables
	sf::Vector2u MouseposGrid;
	sf::RectangleShape selector;

	sf::IntRect texturerect;
	sf::RectangleShape bounds;
	sf::Sprite sheet;

public:
	//Constructor, Destructor
	TextureSelector(unsigned x, unsigned y, unsigned width, unsigned height, float gridsize, sf::Texture* Texture);
	virtual ~TextureSelector();

	//Functions
	bool getactive();
	sf::IntRect getTexturerect();
	
	//Update and Render Functions
	void update(sf::Vector2i Mouseposwindow);
	void render(sf::RenderTarget* target);
};


#endif