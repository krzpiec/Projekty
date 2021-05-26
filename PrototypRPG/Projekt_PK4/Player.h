#ifndef PLAYER_H
#define PLAYER_H
#include "Entity.h"
class Player :
	public Entity
{
private:


	bool attacking;

	void initVar();
	void initComponents();

public:
	Player(sf::Vector2f pos, sf::Texture& ptex_sheet);
	virtual ~Player();
	void collisionChange(sf::Vector2f position);

	void update(const float& dt);

	void render(sf::RenderTarget& target);
};

#endif