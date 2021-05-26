#ifndef PACMAN_H
#define PACMAN_H


#include "SFML/Graphics.hpp"
#include "Obiekt_Dynamiczny.h"
#include "Plansza.h"
#include "Pozycja.h"
using namespace sf;


class Pacman : public Obiekt_dyn
{
	
public:
	Pacman(Plansza& Map, Texture *ptex_all);
	virtual void update(const Plansza& Mapa, Nazwy ktory, Vector2f Pac_Pos, Kierunek Pac_heading, int frames);
private:
	const float promien{ 12.0f };
};



#endif // !PACMAN_H
