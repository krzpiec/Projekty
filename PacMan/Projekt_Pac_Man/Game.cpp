#include "Game.h"
#include <iostream>
#include "SFML/Graphics.hpp"
#include <fstream>

Game::Game(Plansza pMapa, Pacman pGracz, vector<Punkt> pkropeczki, vector<Duszek> pPrzeciwnicy, Owoc pwisienka, Booster pPowerPill, vector<Obiekt_dyn*> pvec)
	:Mapa(pMapa), Gracz(pGracz), kropeczki(pkropeczki), Duszki(pPrzeciwnicy), wisienka(pwisienka), PowerPill(pPowerPill), vec_dyn(pvec)
{
	stworz_vec_dyn();
	stworz_vec_stat();
}

void Game::stworz_vec_dyn()
{
	vec_dyn.clear();
	vec_dyn.push_back(&Gracz);
	for (int i = 0; i < Duszki.size(); i++)
		vec_dyn.push_back(&Duszki[i]);
}

void Game::stworz_vec_stat()
{
	vec_stat.push_back(&PowerPill);
	vec_stat.push_back(&wisienka);
	for (int i = 0; i < kropeczki.size(); i++)
		vec_stat.push_back(&kropeczki[i]);
}

bool Game::Colision_Test()
{

	

	for (int i = 0; i < 4; i++)
		if(Duszki[i].Stan != Frightened and Duszki[i].Stan != Eaten and Gracz.ksztalt.getGlobalBounds().intersects(Duszki[i].ksztalt.getGlobalBounds()))
			return true;

	for (int i = 0; i < 4; i++)
	{
		if (Duszki[i].Stan == Frightened and Gracz.ksztalt.getGlobalBounds().intersects(Duszki[i].ksztalt.getGlobalBounds()))
		{
			Duszki[i].Stan = Eaten;
			Duszki[i].eaten = true;
			return false;

		}
	}
	

	for (int i = 0; i < kropeczki.size(); i++)
		if(kropeczki[i].ksztalt.getGlobalBounds().intersects(Gracz.ksztalt.getGlobalBounds()))
		{
			kropeczki[i].move(-10, -10);
			points_count++;
			total_points++;
		}

	if (not wisienka.eaten and Gracz.ksztalt.getGlobalBounds().intersects(wisienka.ksztalt.getGlobalBounds()))
	{
		wisienka.eaten = true;
		wisienka.move(-10, -10);
		total_points += 100;
		wisienka.clock.restart();
	}
	if (not PowerPill.eaten and  Gracz.ksztalt.getGlobalBounds().intersects(PowerPill.ksztalt.getGlobalBounds()))
	{
		PowerPill.eaten = true;
		PowerPill.move(-10, -10);


		for (int i = 0; i < 4; i++)
			Duszki[i].Booster_Picked();

		PowerPill.clock.restart();

	}
	return false;

}

void Game::Draw_All(sf::RenderTarget& window)
{
	Mapa.makeWallsMap(window);

	
	for (int i = 0; i < vec_stat.size(); i++)
		window.draw(*vec_stat[i]);

	for (int i = 0; i < vec_dyn.size(); i++)
		window.draw(*vec_dyn[i]);


	
}

void Game::Update_All()
{
	for(int i=0; i<vec_dyn.size(); i++)
		vec_dyn[i]->update(Mapa, Nazwy(i), Gracz.getPosition(), Gracz.next_move, frames);
	
	for (int i = 0; i < vec_stat.size(); i++)
		vec_stat[i]->update();

	
}

void Game::Aktualizuj_czasy()
{
	wisienka.elapsed = wisienka.clock.getElapsedTime();
	PowerPill.elapsed = PowerPill.clock.getElapsedTime();
	for (int i = 0; i < 4; i++)
		Duszki[i].elapsed = Duszki[i].clock.getElapsedTime();
}

unsigned Ilosc_linii()
{
	fstream plik("Wyniki.txt", ios::in);;
	if (not plik.good())
	{
		cout << "Bledny plik wyjsciowy!" << endl;
		getchar();
	}
	string linia;
	unsigned iter = 0;
	while (getline(plik, linia))
		iter++;
	
	plik.close();
	return iter;
}

void Game::zapisz_wynik()
{
	fstream plik("Wyniki.txt", ios::out | ios::app);
	if (not plik.good())
	{
		cout << "Bledny plik wyjsciowy!" << endl;
		getchar();
	}
	string linia;
	unsigned iter = Ilosc_linii();

	plik << "["<<to_string(iter)<<"]  "<<total_points << endl;
	plik.close();

}

void Game::run()
{
	
	RenderWindow window{ VideoMode(448,576), "Okienko" };
	while (window.isOpen())
	{
		Aktualizuj_czasy();

		window.setFramerateLimit(30);
		window.clear(sf::Color::Black);
		Event evnt;
		while (window.pollEvent(evnt))
		{
			if (evnt.type == evnt.Closed)
				window.close();
		}

		Update_All();
		Draw_All(window);

		if (Colision_Test() or points_count - kropeczki.size() == 0)
			break;

		window.display();
		frames++;
		if (frames == 30)
			frames = 0;
		cout << total_points << endl;
	}
	zapisz_wynik();


}

