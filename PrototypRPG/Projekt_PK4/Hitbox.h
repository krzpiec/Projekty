#ifndef HITBOX_H
#define HITBOX_H


#include <vector>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Network.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include <fstream>
#include <sstream>
#include <stack>
#include <map>

class Hitbox
{
private:

	sf::Sprite& sprite;
	sf::RectangleShape hitbox;
	sf::FloatRect nextPosition;
	sf::Vector2f offset;


public:
	Hitbox(sf::Sprite& sprite, sf::Vector2f offset, sf::Vector2f Size, sf::Vector2f Scale);
	~Hitbox();


	const sf::Vector2f& getPosition() const;
	const sf::FloatRect getGlobalBounds() const;
	const sf::FloatRect& getNextPosition(const sf::Vector2f& velocity);

	//Modifiers
	void setPosition(const sf::Vector2f& position);
	//void setPosition(const float x, const float y);

	bool intersects(const sf::FloatRect& frect);

	void update();
	void render(sf::RenderTarget* target);
	void Change_offset(sf::Vector2f new_offset);

};



#endif // !HITBOX_H

