#include "Edible.h"



void Edible::update()
{

	if (eaten and Zmien_od_Czasu(elapsed))
		clock.restart();
}



bool Edible::Zmien_od_Czasu(Time czas)
{
	if (czas.asSeconds() > 12)
	{
		eaten = false;
		losuj_pozycje();
		return true;
	}
	return false;

}

void Edible::losuj_pozycje()
{
	

	srand(time(NULL));
	int indeks = rand() % mozliwe_pozycje.size();
	x = mozliwe_pozycje[indeks].x;
	y = mozliwe_pozycje[indeks].y;
	x *= Scale_times;
	x += Scale_plus;
	y *= Scale_times;
	y += Scale_plus;
	move(x, y);
}

void Edible::draw(sf::RenderTarget & target, sf::RenderStates state) const
{
	if (not eaten)
		target.draw(this->ksztalt, state);
}