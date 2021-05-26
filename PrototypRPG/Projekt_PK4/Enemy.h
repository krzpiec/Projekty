#ifndef ENEMY_H
#define ENEMY_H
#include "Entity.h"
class Enemy :
	public Entity
{

private:

	//Initializer functions
	void initVariables();
	void initAnimations();

public:
	Enemy(sf::Vector2f position, sf::Texture& texture_sheet);
	virtual ~Enemy();

	void collisionChange(sf::Vector2f position);

	//Functions
	void updateAnimation(const float& dt);
	void update(const float& dt);
	void render(sf::RenderTarget& target);

};

#endif //!ENEMY_H