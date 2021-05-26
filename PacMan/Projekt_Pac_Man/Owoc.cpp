#include "Owoc.h"

#include "SFML/Graphics.hpp"
#include "Plansza.h"
#include "Pozycja.h"
#include <chrono>
#include <random>
Owoc::Owoc(vector<pos> pmozliwe_pozycje, Texture* ptex_all)
{
	tex_all = ptex_all;
	ksztalt.setTexture(*ptex_all);
	ksztalt.setScale(1.6, 1.6);
	eaten = false;
	srand(time(NULL));
	mozliwe_pozycje = pmozliwe_pozycje;
	int indeks = rand() % mozliwe_pozycje.size();
	x = mozliwe_pozycje[indeks].x;
	y = mozliwe_pozycje[indeks].y;
	x *= Scale_times;
	x += Scale_plus;
	y *= Scale_times;
	y += Scale_plus;
	ksztalt.setPosition(x, y);
//	ksztalt.setRadius(this->promien);
	//ksztalt.setColor(sf::Color::Cyan);
	ksztalt.setOrigin(this->promien, this->promien);
}

Owoc::~Owoc()
{
}
//
//void Owoc::update(Time elapsed, Clock & clock)
//{
//
//	if (eaten and Zmien_od_Czasu(elapsed))
//		clock.restart();
//}
//
//
//
//bool Owoc::Zmien_od_Czasu(Time czas)
//{
//	//cout << czas.asSeconds() << endl;
//	if (czas.asSeconds() > 12)
//	{
//		eaten = false;
//		losuj_pozycje();
//		return true;
//	}
//	return false;
//
//}
//
//void Owoc::losuj_pozycje()
//{
//	/*std::default_random_engine silnik;
//	silnik.seed(std::chrono::system_clock::now().time_since_epoch().count());
//	std::normal_distribution<double> rozklad(0,mozliwe_pozycje.size());
//
//	int indeks = rozklad(silnik);
//	if (indeks < 0)
//		indeks = -indeks;
//	while (indeks > mozliwe_pozycje.size())
//		indeks = indeks / 2;
//	cout << indeks<<endl;*/
//
//	srand(time(NULL));
//	int indeks = rand() % mozliwe_pozycje.size();
//	x = mozliwe_pozycje[indeks].x;
//	y = mozliwe_pozycje[indeks].y;
//	x *= Scale_times;
//	x += Scale_plus;
//	y *= Scale_times;
//	y += Scale_plus;
//	move(x, y);
//}
//
//void Owoc::draw(sf::RenderTarget & target, sf::RenderStates state) const
//{
//	if (not eaten)
//		target.draw(this->ksztalt, state);
//}
