#include "Hitbox.h"

Hitbox::Hitbox(sf::Sprite& sprite, sf::Vector2f offset, sf::Vector2f Size, sf::Vector2f Scale)
: sprite(sprite)
{
	this->nextPosition.left = 0.f;
	this->nextPosition.top = 0.f;
	this->nextPosition.width = Size.x;
	this->nextPosition.height = Size.y;

	this->offset = offset;
	this->offset.x *= Scale.x;
	this->offset.y *= Scale.y;
	this->hitbox.setPosition(this->sprite.getPosition() + this->offset);
	this->hitbox.setSize(Size);
	this->hitbox.setFillColor(sf::Color(200,200,200,100));
	this->hitbox.setOutlineColor(sf::Color::Green);
	this->hitbox.setOutlineThickness(-0.5f);
	this->hitbox.setScale(Scale);


}

Hitbox::~Hitbox()
{
}


const sf::Vector2f& Hitbox::getPosition() const
{
	return this->hitbox.getPosition();
}


const sf::FloatRect Hitbox::getGlobalBounds() const
{
	return this->hitbox.getGlobalBounds();
}

const sf::FloatRect& Hitbox::getNextPosition(const sf::Vector2f& velocity)
{
	this->nextPosition.left = this->hitbox.getPosition().x + velocity.x;
	this->nextPosition.top = this->hitbox.getPosition().y + velocity.y;

	return this->nextPosition;
}


void Hitbox::setPosition(const sf::Vector2f& position)
{
	this->hitbox.setPosition(position);
	this->sprite.setPosition(position.x - this->offset.x, position.y - this->offset.y);
}


bool Hitbox::intersects(const sf::FloatRect& frect)
{
	return this->hitbox.getGlobalBounds().intersects(frect);
}

void Hitbox::update()
{
	this->hitbox.setPosition(this->sprite.getPosition() + this->offset);
}


void Hitbox::render(sf::RenderTarget* target)
{
	target->draw(this->hitbox);
}

void Hitbox::Change_offset(sf::Vector2f new_offset)
{
	this->offset.x = new_offset.x * this->hitbox.getScale().x;
	this->offset.y = new_offset.y * this->hitbox.getScale().y;
}
