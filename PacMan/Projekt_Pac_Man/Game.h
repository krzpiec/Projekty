#ifndef GAME_H
#define GAME_H

#include "Pozycja.h"
#include "Plansza.h"
#include "PacMan.h"
#include "Ghost.h"
#include "Kropki.h"
#include "Owoc.h"
#include "Booster.h"
class Game
{
public:

	Game(Plansza pMapa, Pacman pGracz, vector<Punkt> pkropeczki, vector<Duszek> pPrzeciwnicy, Owoc pwisienka, Booster pPowerPill, vector<Obiekt_dyn*> pvec);

	Time elapsed;
	int total_points = 0;
	int points_count = 0;
	Plansza Mapa;
	Pacman Gracz;
	vector<Punkt> kropeczki;
	vector<Duszek> Duszki;
	vector<Obiekt_dyn*> vec_dyn;
	vector<Obiekt_stat*> vec_stat;
	Owoc wisienka;
	Booster PowerPill;
	int frames;

	void stworz_vec_dyn();
	void stworz_vec_stat();

	template < class T1, class T2> bool IsIntersecting(T1& a, T2& b);
	bool Colision_Test();
	void Draw_All(sf::RenderTarget& window);
	void run();
	void Update_All();
	void Aktualizuj_czasy();
	void zapisz_wynik();
};


#endif // !GAME_H

template<class T1, class T2> inline bool Game::IsIntersecting(T1 & a, T2 & b)
{
		return a.right() > b.left() && a.left() < b.right()
			&& a.bottom() > b.top() && a.top() < b.bottom();
}
