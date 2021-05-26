#include "Player.h"

void Player::initVar()
{
	this->attacking = false;
	this->Scale = sf::Vector2f(1.0f, 1.0f);
	this->Offset = sf::Vector2f(60.f,45.f);
}

void Player::initComponents()
{

	
}

Player::Player(sf::Vector2f pos, sf::Texture& ptex_sheet)
{
	this->initVar();
	this->initComponents();
	this->setPos(pos);

	this->createHitbox(this->sprite, this->Offset, sf::Vector2f(100.f, 140.f), this->Scale);
	this->createMovement(300.f, 10.f, 3.f);
	this->createAnimationCmp(ptex_sheet);

	this->animationComponent->addAnimation("Player_Idle",this->Scale, 8.f, 0, 0, 0, 1, 225,225, 16);
	this->animationComponent->addAnimation("Shooting", this->Scale, 8.f, 1, 1, 9, 1, 225, 225, 16);
	this->animationComponent->addAnimation("Player_Walk_Left", this->Scale, 5.f, 10, 1, 16, 2, 225, 225, 16);
	this->animationComponent->addAnimation("Player_Walk_Right", this->Scale, 5.f, 10, 1, 16, 2, 225, 225, 16);
}

Player::~Player()
{
}

void Player::collisionChange(sf::Vector2f position)
{
	this->setPos(position);
}

void Player::update(const float& dt)
{
	this->movementComponent->update(dt);
	this->hitboxComponent->update();
	Entity::update(dt);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
		this->attacking = true;

	if (this->attacking)
	{
		this->animationComponent->play("Shooting", dt, true);
		if (this->animationComponent->isDone("Shooting"))
			this->attacking = false;
	}

	switch (this->movementComponent->getStatus())
	{
	case Idle:
	{

		this->animationComponent->play("Player_Idle", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
		break;
	}
	case Walk_Right:
	{
		//
		this->hitboxComponent->Change_offset(this->Offset);
		//
		this->sprite.setOrigin({ 0, 0 });
		this->sprite.setScale(Scale);
		this->animationComponent->play("Player_Walk_Right", dt);
		break;
	}
	case Walk_Left:
	{
		//
		this->hitboxComponent->Change_offset(sf::Vector2f(this->Offset.x + 5.f, this->Offset.y));
		//
		this->sprite.setOrigin({ sprite.getLocalBounds().width, 0 });
		this->sprite.setScale(-Scale.x, Scale.y);
		this->animationComponent->play("Player_Walk_Left", dt);
		break;
	}
	case Walk_Down:
	{
		//
		if(this->sprite.getScale().x > 0.f) // down
			this->animationComponent->play("Player_Walk_Left", dt);
		else
			this->animationComponent->play("Player_Walk_Right", dt);
		break;
	}
	case Walk_Up:
	{
		//
		if (this->sprite.getScale().x > 0.f) // up
			this->animationComponent->play("Player_Walk_Left", dt);
		else
			this->animationComponent->play("Player_Walk_Right", dt);
		break;
	}
	default:
	{
		this->animationComponent->play("Player_Idle", dt);
		break;
	}

	}

}
void Player::render(sf::RenderTarget & target)
	{
		target.draw(this->sprite);

		//this->hitboxComponent->render(&target);
	}


