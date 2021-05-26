#include "Enemy.h"
void Enemy::initVariables()
{
	this->Scale = sf::Vector2f(1.0f, 1.0f);
	this->Offset = sf::Vector2f(60.f, 45.f);

}

void Enemy::initAnimations()
{
	this->animationComponent->addAnimation("WALK_LEFT", this->Scale, 8.f, 0, 0, 7, 2, 225, 225, 7);
	this->animationComponent->addAnimation("WALK_RIGHT", this->Scale, 4.f, 0, 0, 7, 2, 225, 225, 7);
	
}

//Constructors / Destructors
Enemy::Enemy(sf::Vector2f position, sf::Texture& texture_sheet)
{
	this->initVariables();
	this->createHitbox(this->sprite, this->Offset, sf::Vector2f(100.f, 140.f), this->Scale);
	this->createMovement(300.f, 10.f, 3.f);
	this->createAnimationCmp(texture_sheet);

	this->setPos(position);
	this->initAnimations();
}

Enemy::~Enemy()
{

}

void Enemy::collisionChange(sf::Vector2f position)
{
	this->setPos(position);
	this->heading = -heading;
}

void Enemy::updateAnimation(const float& dt)
{
	if (this->movementComponent->getStatus() == MoveStatus::Walk_Left)
	{
	this->animationComponent->play("WALK_LEFT", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
	this->sprite.setScale(-Scale.x, Scale.y);
	}
	else if (this->movementComponent->getStatus() == MoveStatus::Walk_Right)
	{
	this->animationComponent->play("WALK_RIGHT", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
	this->sprite.setScale(Scale.x, Scale.y);
	}
}

void Enemy::update(const float& dt)
{
	this->movementComponent->update(dt);
	this->hitboxComponent->update();
	Entity::update(dt);

	this->animationComponent->play("WALK_RIGHT", dt);

}

void Enemy::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);

	//this->hitboxComponent->render(&target);
}
