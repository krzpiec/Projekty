#ifndef OBIEKTDYNAMICZNY_H
#define OBIEKTDYNAMICZNY_H

#include "Plansza.h"
#include "SFML/Graphics.hpp"
#include "Pozycja.h"
#include "Obiekt.h"
using namespace std;
using namespace sf;

enum Nazwy { A = 1, B = 2, C = 3, D = 4 };

class Obiekt_dyn: public Obiekt
{
public:
	virtual void update(const Plansza& Mapa, Nazwy ktory, Vector2f Pac_Pos, Kierunek Pac_heading, int frames) = 0;
	Kierunek next_move = Nothing;

private:
	const int ImageFrames = 10;
	int ImagesChanged = 0;

protected:
	
	sf::Vector2f velocity{ 0,0 };
	float velo{ 2.0f };
	
	void change_velocity(Kierunek gdzie);
	pos Pozycja_kafelka(Vector2f position);
	bool Is_At_Node(Vector2f position);
	bool weryfikuj_ruch(const Plansza& Map, Vector2f position, Kierunek gdzie);
	void Change_Velocity(Vector2f& velocity, Kierunek gdzie, const float base);
	bool Wall_collision(Vector2f position, Kierunek heading);
};



#endif // !OBIEKTDYNAMICZNY_H
