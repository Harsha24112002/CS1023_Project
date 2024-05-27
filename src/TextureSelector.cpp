#include "TextureSelector.h"
#include <iostream>

/////////////////////////////////// CONSTRUCTOR AND DESTRUCTOR FUNCTIONS ////////////////////////////////////////////

TextureSelector::TextureSelector(unsigned x, unsigned y, unsigned width, unsigned height, float gridsize, sf::Texture* texture)
{
	active = false;
	hidden = false;
	this->gridsize = gridsize;
	selector.setSize(sf::Vector2f(gridsize, gridsize));
	selector.setPosition(x, y);
	selector.setFillColor(sf::Color::Transparent);
	selector.setOutlineThickness(1.0f);
	selector.setOutlineColor(sf::Color::Blue);
	bounds.setSize(sf::Vector2f(width, height));
	bounds.setPosition(x, y);
	bounds.setOutlineThickness(1.0f);
	bounds.setOutlineColor(sf::Color::Red);
	bounds.setFillColor(sf::Color::Transparent);

	sheet.setTexture(*texture);
	sheet.setPosition(x, y);
	if (sheet.getGlobalBounds().width > bounds.getGlobalBounds().width)
	{
		bounds.setSize(sf::Vector2f(sheet.getGlobalBounds().width, bounds.getGlobalBounds().height));
	}
	if (sheet.getGlobalBounds().height > bounds.getGlobalBounds().height)
	{
		bounds.setSize(sf::Vector2f(bounds.getGlobalBounds().width, sheet.getGlobalBounds().height));
	}
	texturerect.width = gridsize;
	texturerect.height = gridsize;
	texturerect.left = 0;
	texturerect.top = 0;

}

TextureSelector::~TextureSelector()
{

}

/////////////////////////////////// ACCESSOR FUNCTIONS ////////////////////////////////////////////

bool TextureSelector::getactive()
{
	return this->active;
}

sf::IntRect TextureSelector::getTexturerect()
{
	return texturerect;
}

/////////////////////////////////// UPDATE FUNCTIONS ////////////////////////////////////////////

void TextureSelector::update(sf::Vector2i Mouseposwindow)
{
	if (!hidden)
	{
		if (bounds.getGlobalBounds().contains(static_cast<sf::Vector2f>(Mouseposwindow)))
		{
			this->active = true;
		}
		else this->active = false;
		if (active)
		{
			MouseposGrid.x = (int)(Mouseposwindow.x - bounds.getPosition().x) / gridsize;
			MouseposGrid.y = (int)(Mouseposwindow.y - bounds.getPosition().y) / gridsize;
			selector.setPosition((static_cast<float>(MouseposGrid.x) * gridsize + bounds.getPosition().x), (static_cast<float>(MouseposGrid.y) * gridsize + bounds.getPosition().y));
			texturerect.left = (MouseposGrid.x) * gridsize;
			texturerect.top = (MouseposGrid.y) * gridsize;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::O))
	{
		if (hidden)
			hidden = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
	{
		if (!hidden)
		{
			hidden = true;
			active = false;
		}
	}
}

/////////////////////////////////// RENDER FUNCTIONS ////////////////////////////////////////////

void TextureSelector::render(sf::RenderTarget* target)
{
	if (!hidden)
	{
		target->draw(sheet);
		target->draw(bounds);
		if (active)
		{
			target->draw(selector);
		}
	}
}