#ifndef KROPKI_H
#define KROPKI_H


#include "SFML/Graphics.hpp"
#include "Obiekt_Statyczny.h"

using namespace std;
using namespace sf;

class Punkt : public Obiekt_stat
{
	
public:
	virtual void update()
	{

	}
	Punkt(pos cpy, Texture* ptex_all);
	~Punkt();
	
private:

	const float promien{4.0f };
};


#endif // !KROPKI_H
