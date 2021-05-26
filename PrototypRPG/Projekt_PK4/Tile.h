#ifndef TILE_H
#define TILE_H

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include <vector>
#include <iostream>
#include <ctime>
#include <fstream>
#include <sstream>
enum TileTypes { DEFAULT = 0, DAMAGING };

class Tile
{
private:

protected:
	sf::RectangleShape shape;
	bool collision;
	short type;

public:
	Tile();
	~Tile();
	Tile(unsigned grid_x, unsigned grid_y, float gridSizeF, const sf::Texture& texture, const sf::IntRect& texture_rect,
		bool collision = false, short type = TileTypes::DEFAULT);


	////
	
	///
	const bool intersects(const sf::FloatRect bounds);
	const sf::FloatRect getGlobalBounds() const;
	const std::string getAsString() const;
	const sf::Vector2f& getPosition() const;
	const bool& getCollision() const;

	

	void update();
	void render(sf::RenderTarget& target);
};



#endif // !TILE_H

