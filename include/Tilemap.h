#ifndef TILEMAP_H
#define TILEMAP_H

#include "Enemytile.h"
#include "Floortile.h"
#include "Player.h"
#include "Enemy.h"
#include <memory>
#include "Collisionvisitor.h"

class Tilemap
{
private:
	//Variables
	 //sf Variables
	 sf::Vector2f mapsize;
	 sf::Texture texture;
	 sf::Texture enemytex;

	 //Objects
	 std::vector<std::vector<std::vector<Tile*>>> map ;
	 std::vector<Enemy*> Enemies;
	 Visitor* v;

	 //Accessor Variables
	 unsigned gridsizeu;
	 float gridsizef;
	 int fromX;
	 int fromY;
	 int toX;
	 int toY;
     int colfromX;
	 int colfromY;
	 int coltoX;
	 int coltoY;
	//Functions
	bool checksametype(std::vector<Tile*>, Tiletype type);
	void clear();
public:
	//Constructors, Destructor
	/**
	 * @brief Constructor
	 * @param texture tilesheet of the map
	 * @param gridsize size of the grid
	 * @param width width of the tilemap
	 * @param height height of the tilemap
	 * */
	Tilemap(sf::Texture* texture, float gridsize, unsigned width, unsigned height);
	/**
	 * @brief Constructor (Loading from file)
	 * @param texture texture of the tilesheet
	 * @param filename name of the file containing the map
	 * */
	Tilemap(sf::Texture* texture, std::string filename);

	// Destructor
	virtual ~Tilemap();
	
	//Functions 
	/**
	 * @brief Gives the tilesheet 
	 * @return returns an object of type sf::Texture*
	 * */
	sf::Texture* getTilesheet() { return &texture; }
	 
	 //Accessors Functions
	 /**
	  * @brief Adds the tile to tilemap
	  * @param x x-coordinate of the tile position
	  * @param y y-coordinate of the tile position
	  * @param texturerect texture rectangle of the tile
	  * @param type type of the tile
	  * */
	 void addtile(unsigned x,unsigned y,sf::IntRect& texturerect,Tiletype type);
	 /**
	  * @brief Removes the tile from the tilemap
	  * @param x x-coordinate of the tile
	  * @param y y-coordinate of the tile
	  * */
	 void removetile(unsigned x,unsigned y );

	/**
	 * @brief Checks collision with the tiles of the tilemap
	 * @param player Player* on which collision is to be checked
	 * @param direction Used for storing the direction of collision
	 * */
	 void checkcollison(Player* player,sf::Vector2f& direction);
	 /**
	  * @brief Saves the tilemap in a file
	  * @param filename name of the file in which the map should be saved
	  * */
	 void savetofile(std::string& filename);

	 /**
	  * @brief Loads the tilemap from the file
	  * @param filename name of the file in which the map should be loaded
	  * */
 	 void Loadfromfile(std::string& filename);
 
	 //Update and Render Functions
	 /**
	  * @brief Updates the tiles, tile culling
	  * @param Pos Position from where the tile distances are measured for culling
	  * @param dt deltatime
	  * */
	 void update(sf::Vector2i Pos, float dt);
	 /**
	  * @brief Renders the tilemap to target
	  * @param target The target for rendering
	  * */
	 void render(sf::RenderTarget* target);
};

#endif