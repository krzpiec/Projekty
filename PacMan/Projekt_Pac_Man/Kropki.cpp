#include "Kropki.h"
#include "Plansza.h"
#include "Pozycja.h"

	Punkt::Punkt(pos cpy, Texture* ptex_all)
	{
		tex_all = ptex_all;
		ksztalt.setTexture(*ptex_all);
		x = cpy.x;
		y = cpy.y;
		x *= Scale_times;
		x += Scale_plus;
		y *= Scale_times;
		y += Scale_plus;
		ksztalt.setPosition(x , y);
		ksztalt.setOrigin(this->promien, this->promien);
	}

	Punkt::~Punkt()
	{
	}


	