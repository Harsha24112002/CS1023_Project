#ifndef TEXTURESELECTOR_H
#define TEXTURESELECTOR_H

#include <SFML/Graphics.hpp>
class TextureSelector
{
private:
	bool active;
	float gridsize;
	bool hidden;
	sf::Vector2u MouseposGrid;
	sf::RectangleShape selector;

	sf::IntRect texturerect;
	sf::RectangleShape bounds;
	sf::Sprite sheet;

public:
	TextureSelector(unsigned x, unsigned y, unsigned width, unsigned height, float gridsize, sf::Texture* Texture);
	virtual ~TextureSelector();
	bool getactive();
	sf::IntRect getTexturerect();
	void update(sf::Vector2i Mouseposwindow);
	void render(sf::RenderTarget* target);
};


#endif