#ifndef MOVEMENT_H
#define MOVEMENT_H

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


enum MoveStatus {Idle = 0, Walk_Right, Walk_Left, Walk_Up, Walk_Down, Error};

class Movement
{
private:
	sf::Sprite& sprite;

	float maxVelocity;
	float acceleration;
	float deceleration;
	sf::Vector2f velocity;

public:
	Movement(float maxvelo, float acceleration, float deceleration, sf::Sprite& sprite);
	~Movement();

	//Getters
	const sf::Vector2f& getVelocity() const;

	//init
	void initVar();

	const float& getMaxVelocity() const;
	void stopVelocity();
	void stopVelocityX();
	void stopVelocityY();
	MoveStatus getStatus() const;


	void move(sf::Vector2f dir, const float& dt);
	void update(const float& dt);
};

#endif // !MOVEMENT_H