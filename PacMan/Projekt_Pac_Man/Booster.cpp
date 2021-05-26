#include "Booster.h"

Booster::Booster(vector<pos> pmozliwe_pozycje, Texture *ptex_all)
{
	tex_all = ptex_all;
	ksztalt.setTexture(*ptex_all);
	ksztalt.setScale(1.5, 1.5);
	eaten = true;
	srand(time(NULL));
	mozliwe_pozycje = pmozliwe_pozycje;
	int indeks = rand() % mozliwe_pozycje.size();
	x = mozliwe_pozycje[indeks].x;
	y = mozliwe_pozycje[indeks].y;
	x *= Scale_times;
	x += Scale_plus;
	y *= Scale_times;
	y += Scale_plus;
	ksztalt.setPosition(x, y);
//	ksztalt.setRadius(this->promien);
	//ksztalt.setFillColor(sf::Color::Green);
	ksztalt.setOrigin(this->promien, this->promien);
}

Booster::~Booster()
{
}
