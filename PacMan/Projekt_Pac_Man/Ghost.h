
#ifndef GHOST_H
#define GHOST_H
#include "Obiekt_Dynamiczny.h"
#include "Plansza.h"
#include "Pozycja.h"
#include "SFML/Graphics.hpp"
enum Mode{Chase = 0, Frightened = 1, Scatter = 2, Eaten = 3};
using namespace std;
using namespace sf;



class Duszek : public Obiekt_dyn
{
public:
	Time elapsed;
	Mode Stan = Chase;
	
	Duszek(Plansza& Map, int ktory, Texture* ptex_all);
	void Zmiana_Stanu();
	virtual void update(const Plansza& Mapa, Nazwy ktory, Vector2f Pac_Pos, Kierunek Pac_heading, int frames);
	void Booster_Picked();
	
	bool eaten = false;

private:


	void Frightened_end();
	void Scattered();
	void Scattered_end();
	vector<pos> mozliwe_kierunki(const Plansza & Mapa);
	Kierunek Which_tile(const Plansza& Mapa, Vector2f Pac_Pos);
	Vector2f GetTarged(Nazwy ktory, Vector2f Pac_Pos, Kierunek Pac_heading);
	float Distance(pos docelowa, Vector2f Pac_Pos);
	Kierunek Pos_to_heading(pos Docelowa);
	void Frightened_update(const Plansza& Mapa, Nazwy ktory);
	void Chase_update(const Plansza& Mapa, Nazwy ktory, Vector2f target, Kierunek Pac_heading);


	void Eaten_update(const Plansza& Mapa);
	void Scatter_update(const Plansza& Mapa, Nazwy ktory);
	void Scatter_GhostA(const Plansza& Mapa);
	void Scatter_GhostB(const Plansza& Mapa);
	void Scatter_GhostC(const Plansza& Mapa);
	void Scatter_GhostD(const Plansza& Mapa);
	const float promien{ 12.0f };
	bool eaten_stop = false;
	bool IsAtPoint = false;
	int ktory;
};




#endif // !GHOST_H






