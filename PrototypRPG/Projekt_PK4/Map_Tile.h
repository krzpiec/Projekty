#ifndef MAP_TILE_H
#define MAP_TILE_H

#include "Tile.h"
#include "Entity.h"
#include <typeinfo>
#include "memory"
#include "Player.h"
#include "Enemy.h"
class Tile;
class Entity;
class TileMap
{
private:

	void clear();

	unsigned int gridSizeU;
	float gridSizeF;
	unsigned layers;
	sf::Vector2u maxSizeWorldGrid;
	sf::Vector2f maxSizeWorldF;
	std::vector<std::vector<std::vector<std::vector<Tile*>>>> map;
	std::string textureFile;
	sf::Texture tileSheet;

	sf::RectangleShape collisionBox;

	int fromX;
	int toX;
	int fromY;
	int toY;
	unsigned actualLayer;
	
	

public:
	TileMap(float gridSize, unsigned width, unsigned height, std::string texture_file);
	~TileMap();
	/////////
	
	/////////
	const sf::Texture* getTileSheet() const ;

	void addTile(const unsigned x, const unsigned y, const unsigned z, const sf::IntRect& texture_rect, const bool collision, const short type);
	void removeTile(const unsigned x, const unsigned y, const unsigned z);
	void saveToFile(const std::string file_name);
	void loadFromFile(const std::string file_name);

	void updateRenderCollisionRange(Entity* entity);
	void updateCollision(Entity* entity, const float& dt);
	//void clear();


	void update(const float& dt);
	void render(sf::RenderTarget& target, Entity* entity = nullptr);

	
};




#endif // !MAP_TILE_H


