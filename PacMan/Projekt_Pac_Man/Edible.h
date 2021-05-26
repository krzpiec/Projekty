#ifndef EDIBLE_H
#define EDIBLE_H

#include "Obiekt_Statyczny.h"
#include "SFML/Graphics.hpp"
#include "Pozycja.h"

using namespace std;
using namespace sf;

class Edible :public Obiekt_stat
{
public:
	Time elapsed;
	vector<pos> mozliwe_pozycje;
	bool eaten = false;
	virtual void update();
	bool Zmien_od_Czasu(Time czas);
protected:
	void losuj_pozycje();
	const float promien{ 8.0f };
	void draw(sf::RenderTarget& target, sf::RenderStates state) const;
};
#endif // !EDIBLE_H
