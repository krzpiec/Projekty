#ifndef POZYCJA_H
#define POZYCJA_H
#include <iostream>
using namespace std;

class pos
{
public:
	int x;
	int y;
	pos() = default;
	pos(int px, int py);
	friend ostream& operator<<(ostream& fout, const pos& print);

};
#endif // !POZYCJA_H


