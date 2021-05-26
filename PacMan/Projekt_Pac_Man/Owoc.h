#ifndef OWOC_H
#define OWOC_H

#include "Obiekt_Statyczny.h"
#include "SFML/Graphics.hpp"
#include "Pozycja.h"
#include "Edible.h"
#include "SFML/Graphics.hpp"
#include "Pozycja.h"
#include "Edible.h"
using namespace std;
using namespace sf;

class Owoc : public Edible
{
public:
	Owoc(vector<pos> pmozliwe_pozycje, Texture* ptex_all);
	~Owoc();
};

#endif // !WISIENKA_H
