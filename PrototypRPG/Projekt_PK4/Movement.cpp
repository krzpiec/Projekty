#include "Movement.h"

Movement::Movement(float maxvelo, float acceleration, float deceleration, sf::Sprite& sprite)
	:sprite(sprite),  maxVelocity(maxvelo), acceleration(acceleration), deceleration(deceleration)
{
	
}

Movement::~Movement()
{
	
}

const sf::Vector2f & Movement::getVelocity() const
{
	return this->velocity;
}

const float& Movement::getMaxVelocity() const
{
	return this->maxVelocity;
}

void Movement::initVar()
{
	
}

MoveStatus Movement::getStatus() const
{
	if (this->velocity.x == 0 and this->velocity.y == 0)
		return Idle;
	if (this->velocity.x > 0)
		return Walk_Right;
	if (this->velocity.x < 0)
		return Walk_Left;
	if (this->velocity.y > 0)
		return Walk_Down;
	if (this->velocity.y < 0)
		return Walk_Up;
	return Error;
}

void Movement::stopVelocity()
{

	this->velocity.x = 0.f;
	this->velocity.y = 0.f;
}

void Movement::stopVelocityX()
{

	this->velocity.x = 0.f;
}

void Movement::stopVelocityY()
{
	 
	this->velocity.y = 0.f;
}

void Movement::move(sf::Vector2f dir, const float& dt)
{
	/*Deals with acceleration*/
	this->velocity.x += this->acceleration * dir.x;

	this->velocity.y += this->acceleration * dir.y;

	
}

void Movement::update(const float & dt)
{
	

	if (this->velocity.x > 0.f)//Heading right
	{
		//Over max
		if (this->velocity.x > this->maxVelocity)
			this->velocity.x = this->maxVelocity;

		//Decelerate
		this->velocity.x -= this->deceleration;
		if (this->velocity.x < 0.f)
			this->velocity.x = 0.f;
	}
	else if (this->velocity.x < 0.f) //Heading left
	{
		//Over max
		if (this->velocity.x < -this->maxVelocity)
			this->velocity.x = -this->maxVelocity;

		//Decelerate
		this->velocity.x += this->deceleration;
		if (this->velocity.x > 0.f)
			this->velocity.x = 0.f;
	}

	if (this->velocity.y > 0.f)//Heading  Down
	{
		//Over max
		if (this->velocity.y > this->maxVelocity)
			this->velocity.y = this->maxVelocity;

		//Decelerate
		this->velocity.y -= this->deceleration;
		if (this->velocity.y < 0.f)
			this->velocity.y = 0.f;
	}
	else if (this->velocity.y < 0.f) //Heading Up
	{
		//Over max
		if (this->velocity.y < -this->maxVelocity)
			this->velocity.y = -this->maxVelocity;

		//Decelerate
		this->velocity.y += this->deceleration;
		if (this->velocity.y > 0.f)
			this->velocity.y = 0.f;
	}


	//Final move
	this->sprite.move(this->velocity*dt);
}
