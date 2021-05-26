#ifndef BOOSTER_H
#define BOOSTER_H
#include "Obiekt_Statyczny.h"
#include "SFML/Graphics.hpp"
#include "Pozycja.h"
#include "Edible.h"

using namespace std;
using namespace sf;

class Booster : public Edible
{
public:
	Booster(vector<pos> mozliwe_pozycje, Texture *ptex_all);
	~Booster();
//private:
//
//	const float promien{ 8.0f };

};


#endif // !BOOSTER_H
