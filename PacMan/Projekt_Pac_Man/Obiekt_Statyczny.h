#ifndef OBIEKTSTATYCZNY_H
#define OBIEKTSTATYCZNY_H


#include "Obiekt.h"

class Obiekt_stat: public Obiekt
{
public:
	virtual void update() = 0;
protected:
	int x;
	int y;
	
};

#endif // !OBIEKTSTATYCZNY_H
