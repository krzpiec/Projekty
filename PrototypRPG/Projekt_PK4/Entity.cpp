#include "Entity.h"

void Entity::initVar()
{
	this->hitboxComponent = nullptr;
	this->movementComponent = nullptr;
	this->hitboxComponent = nullptr;

	//tutaj
	this->heading = 1.f;
	this->collision = true;
}

Entity::Entity()
{
	this->initVar();
}

Entity::~Entity()
{
	delete this->hitboxComponent;
	delete this->movementComponent;
	delete this->hitboxComponent;
}
////

void Entity::setTexture(sf::Texture & ptex)
{

	this->sprite.setTexture(ptex);

}

void Entity::createHitbox(sf::Sprite& sprite, sf::Vector2f offset, sf::Vector2f Size, sf::Vector2f Scale)
{
	this->hitboxComponent = new Hitbox(sprite, offset, Size, Scale);
}

void Entity::createMovement(const float MaxVelocity, const float acceleration, const float deceleration)
{
	this->movementComponent = new Movement(MaxVelocity, acceleration ,deceleration, this->sprite);

}

void Entity::createAnimationCmp(sf::Texture & tex_sheet)
{
	this->animationComponent = new AnimationCmp(this->sprite, tex_sheet);
}

void Entity::changeHeading()
{
	this->heading = -heading;
	std::cout << "Changing\n";
}

float Entity::getHeading()
{
	return this->heading;
}

const bool& Entity::getColision() const
{
	return this->collision;
}


void Entity::collisionChange(sf::Vector2f position)
{
}

const sf::Vector2f& Entity::getPosition() const
{
	if (this->hitboxComponent)
		return this->hitboxComponent->getPosition();
	return this->sprite.getPosition();
}

const sf::Vector2u Entity::getGridPosition(const unsigned gridSizeU) const
{
	if (this->hitboxComponent)
		return sf::Vector2u(
			static_cast<int>(this->hitboxComponent->getPosition().x) / gridSizeU,
			static_cast<int>(this->hitboxComponent->getPosition().y) / gridSizeU
		);

	return sf::Vector2u(
		static_cast<int>(this->sprite.getPosition().x) / gridSizeU,
		static_cast<int>(this->sprite.getPosition().y) / gridSizeU
	);
}

const sf::FloatRect Entity::getGlobalBounds() const
{

	if (this->hitboxComponent)
		return this->hitboxComponent->getGlobalBounds();

	return this->sprite.getGlobalBounds();
}

const sf::FloatRect Entity::getNextPositionBounds(const float& dt) const
{
	if (this->hitboxComponent && this->movementComponent)
		return this->hitboxComponent->getNextPosition(this->movementComponent->getVelocity() * dt);

	return sf::FloatRect(-1.f, -1.f, -1.f, -1.f);
}

const sf::Vector2f Entity::getVelocity() const
{
	return this->movementComponent->getVelocity();
}

void Entity::setPos(sf::Vector2f pos)
{
	
	if (this->hitboxComponent)
		this->hitboxComponent->setPosition(pos);
	else
		this->sprite.setPosition(pos);
}


/////
void Entity::move(const float& dt, const sf::Vector2f& direction)
{
	if (this->movementComponent)
	{
		this->movementComponent->move(direction, dt);
	}
}

void Entity::stopVelocity()
{
	if (this->movementComponent)
		this->movementComponent->stopVelocity();

}

void Entity::stopVelocityX()
{
	if (this->movementComponent)
		this->movementComponent->stopVelocityX();
}

void Entity::stopVelocityY()
{
	if (this->movementComponent)
		this->movementComponent->stopVelocityY();
}


void Entity::update(const float & dt)
{
}

void Entity::render(sf::RenderTarget & target)
{
		
}
