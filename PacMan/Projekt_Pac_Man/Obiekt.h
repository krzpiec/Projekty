#ifndef  OBIEKT_H
#define OBIEKT_H
#include "Plansza.h"

#include "SFML/Graphics.hpp"
using namespace std;
using namespace sf;

class Obiekt: public Drawable
{
public:
	void move(int x, int y);
	Clock clock;
	
	Vector2f getPosition();


	Sprite ksztalt;
protected:
	Texture * tex_all;
	
	void change_rotation(Kierunek wo);
	
	void draw(sf::RenderTarget& target, sf::RenderStates state) const;
};



#endif // ! OBIEKT_H

