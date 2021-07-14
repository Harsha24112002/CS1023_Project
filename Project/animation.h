#ifndef ANIMATION_H
#define ANIMATION_H
#include <SFML/Graphics.hpp>
class animation
{
    public:
    animation(sf::Texture* tex,sf::Vector2f nimages,float stime);
    virtual ~animation();
    void update(int row,int direction,float deltatime);
    void pause(int row);
    sf::Rect<int> r;
    private:
    float switchtime;
    float totaltime;
    sf::Vector2f currentimage;
    sf::Vector2f nofimages;
    sf::Texture* texture;
    bool rightface; 
};
#endif