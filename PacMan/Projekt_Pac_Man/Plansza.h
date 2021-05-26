#ifndef PLANSZA_H
#define PLANSZA_H
using namespace std;
#include "SFML/Graphics.hpp"
#include <iostream>
#include "Pozycja.h"

#define Scale_times 16;
#define Scale_plus 8;

enum Kierunek {
	Nothing = 0, 
	Up = 1, 
	Down = 2,
	Right = 3, 
	Left = 4, 
	Stop = 5 };


enum TileType
{
	Pill = 1,
	//Booster = 2,
	Wall = 3,
	PacMan = 4,
	Tunnel = 7,
	Empty = 8,
	Ghost = 9
};

class Plansza
{
public:

	vector<pos> Cherry_vec;

	pos Duszki_pos[4];

	pos Pacman_pos;

	vector<pos> punkty;

	int mMap[28][31] = { 0 };

	void uzupelnij_swoje_dane();

	Plansza();

	Plansza(string nazwa);

	void wczytaj(string nazwa);

	void wypisz_sie();

	void makeWallsMap(sf::RenderTarget& target);

	void drawHorizontalLine(sf::RenderTarget& rt, int x1, int x2, int y);

	void drawVerticalLine(sf::RenderTarget& rt, int y1, int y2, int x);
};


#endif // !PLANSZA_H


