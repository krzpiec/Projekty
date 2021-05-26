
#include "Game.h"
using namespace std;


int main()
{

	Font font;
	if (!font.loadFromFile("DejaVuSans.ttf"))
		cout << "zle";
	Texture tex_pacman;
	if (not tex_pacman.loadFromFile("Pacmany_dobre1.png"))
		cout << "tekstura_pac" << endl;
	Texture tex_duszki;
	if (not tex_duszki.loadFromFile("Duszki.png"))
		cout << "tekstura1" << endl;

	Texture tex_kropka;
	if (not tex_kropka.loadFromFile("kropka.png"))
		cout << "tekstura_kropki" << endl;

	Texture tex_wisienka;
	if (not tex_wisienka.loadFromFile("Wisienka.png"))
		cout << "tekstura_wisienka" << endl;

	Texture tex_booster;
	if (not tex_booster.loadFromFile("Truskawa_booster.png"))
		cout << "tekstura_booster" << endl;


	Plansza Mapa("Level1.txt");
	Pacman Gracz(Mapa, &tex_pacman);
	vector<Punkt> kropeczki;
	vector<Duszek> Przeciwnicy;
	Owoc Wisienka(Mapa.punkty, &tex_wisienka);
	Booster PowerPill(Mapa.punkty, &tex_booster);
	vector<Obiekt_dyn*> vec;
	vec.push_back(&Gracz);
	for (int i = 0; i < 4; i++)
	{
		Duszek temp(Mapa, i, &tex_duszki);
		Przeciwnicy.push_back(temp);
		//vec.push_back(&temp);
	}
	for (int i = 0; i < 4; i++)
	{
		vec.push_back(&Przeciwnicy[i]);
	}
	
	for (auto i : Mapa.punkty)
	{
		Punkt temp(i, &tex_kropka);
		kropeczki.push_back(temp);
	}



	Game gra(Mapa, Gracz, kropeczki, Przeciwnicy, Wisienka, PowerPill, vec);
	gra.run();



	return 0;
}


