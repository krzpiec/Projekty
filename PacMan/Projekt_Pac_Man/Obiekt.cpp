#include "Obiekt.h"

using namespace std;
using namespace sf;

Vector2f Obiekt::getPosition()
{
	return ksztalt.getPosition();
}

void Obiekt::change_rotation(Kierunek wo)
{
	switch (wo)
	{
	case Left:
	{
		ksztalt.setScale(-1.f, 1.f);
		break;
	}
	case Right:
	{
		ksztalt.setScale(1.f, 1.f);
		break;
	}
	case Up:
	{
		//ksztalt.rotate(90);
		break;
	}
	case Down:
	{
		break;
	}
	}

}

void Obiekt::draw(sf::RenderTarget & target, sf::RenderStates state) const
{
	target.draw(this->ksztalt, state);
}



void Obiekt::move(int x, int y)
{
	ksztalt.setPosition(x, y);
}
