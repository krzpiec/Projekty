#include "Pozycja.h"

pos::pos(int px, int py)
	:x(px), y(py)
{
}


ostream & operator<<(ostream & fout, const pos & print)
{
	fout << "Pozycja X: " << print.x << ", Pozycja Y: " << print.y;
	return fout;
}