#include "obstacle.h"
obstacle::obstacle(sf::Texture tex,sf::Vector2f pos)
{
    this->t=tex;
   
    sprite.setTexture(t);
    sprite.setPosition(pos);
    sprite.setOrigin(sprite.getTexture()->getSize().x/2.0f,sprite.getTexture()->getSize().y/2.0f);
    this->createBoundRect();  
}

void obstacle::createBoundRect()
{
    this->rect = new Boundrect(sprite,sf::Vector2f(-14,-12.5),28,25);
}
void obstacle::render(sf::RenderTarget& window)
{
    window.draw(this->sprite);
    rect->render(&window);
}
void obstacle::update(float dt)
{
    rect->update();
}
