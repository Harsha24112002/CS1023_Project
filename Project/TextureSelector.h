#ifndef TEXTURESELECTOR_H
#define TEXTURESELECTOR_H

#include <SFML/Graphics.hpp>
class TextureSelector
{
	private:
	sf::RectangleShape bounds;
	sf::Sprite sheet;

	public:
	TextureSelector(unsigned x,unsigned y,unsigned width,unsigned height,sf::Texture* Texture);


	void update();
	void render(sf::RenderTarget* target);
};


#endif