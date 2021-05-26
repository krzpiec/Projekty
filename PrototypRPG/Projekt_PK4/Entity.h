#ifndef ENTITY_H
#define ENTITY_H
#include "Hitbox.h"
#include "Movement.h"
#include "AnimationComponent.h"
class Entity
{
private:
	void initVar();
protected:
	
	sf::Sprite sprite;
	
	Hitbox* hitboxComponent;
	Movement* movementComponent;
	AnimationCmp* animationComponent;

	//needed by hitbox
	sf::Vector2f Scale;
	sf::Vector2f Offset;
	//tutaj
	bool collision;
	float heading;
public:
	Entity();
	virtual ~Entity();
	//
	void setTexture(sf::Texture& tex);
	void createHitbox(sf::Sprite& sprite, sf::Vector2f offset, sf::Vector2f Size, sf::Vector2f Scale);
	void createMovement(const float MaxVelocity, const float acceleration, const float deceleration);
	void createAnimationCmp(sf::Texture& tex_sheet);

	void changeHeading();
	float getHeading();


	///tutaj
	virtual const bool& getColision() const;
	
	virtual void collisionChange(sf::Vector2f position);
	virtual const sf::Vector2f& getPosition() const;
	virtual const sf::Vector2u getGridPosition(const unsigned gridSizeU) const;
	virtual const sf::FloatRect getGlobalBounds() const;
	virtual const sf::FloatRect getNextPositionBounds(const float& dt) const;
	virtual const sf::Vector2f getVelocity() const;
	//Funciotions
	virtual void setPos(const sf::Vector2f pos);
	virtual void move(const float& dt, const sf::Vector2f& direction);
	virtual void stopVelocity();
	virtual void stopVelocityX();
	virtual void stopVelocityY();
	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget& target) = 0;
};

#endif