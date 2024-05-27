#include "animation.h"

/////////////////////////////////// CONSTRUCTOR AND DESTRUCTOR FUNCTIONS ////////////////////////////////////////////

animation::animation(sf::Texture* tex, sf::Vector2f nimages, float stime) :nofimages(nimages), switchtime(stime), texture(tex)
{

    currentimage.x = 0;
    r.width = texture->getSize().x / nofimages.x;
    r.height = texture->getSize().y / nofimages.y;
    totaltime = 0.0f;
    rightface = true;

}

animation::~animation()
{

}

/////////////////////////////////// UPDATE FUNCTIONS ////////////////////////////////////////////

void animation::update(int row, int directionx, float deltatime)
{

    /* if(directionx==0.0f)
      {
          this->pause(row);
      }*/


    currentimage.y = row;

    totaltime += deltatime;
    if (totaltime > switchtime)
    {
        totaltime = 0;
        currentimage.x++;
    }
    if (currentimage.x > nofimages.x - 1)
    {
        currentimage.x = 0;
    }
    if (directionx > 0)
    {
        rightface = true;
    }
    else if (directionx < 0)
        rightface = false;

    r.left = abs(r.width) * currentimage.x;
    r.top = r.height * currentimage.y;

}