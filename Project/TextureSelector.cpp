#include "TextureSelector.h"

TextureSelector::TextureSelector(unsigned x,unsigned y,unsigned width,unsigned height,sf::Texture* texture)
{
	bounds.setSize(sf::Vector2f(width,height));
	bounds.setPosition(x,y);
	bounds.setOutlineThickness(1.0f);
	bounds.setOutlineColor(sf::Color::Red);
	bounds.setFillColor(sf::Color::Transparent);

	sheet.setTexture(*texture);

	if(sheet.getGlobalBounds().width>bounds.getGlobalBounds().width)
	{
		bounds.setSize(sf::Vector2f(sheet.getGlobalBounds().width,bounds.getGlobalBounds().height));
	}
	if(sheet.getGlobalBounds().height>bounds.getGlobalBounds().height)
	{
		bounds.setSize(sf::Vector2f(bounds.getGlobalBounds().width,sheet.getGlobalBounds().height));
	}
}

void TextureSelector::update()
{

}

void TextureSelector::render(sf::RenderTarget* target)
{
	target->draw(sheet);
	target->draw(bounds);
}