#include "Plansza.h"
#include "Pozycja.h"
#include <fstream>
#include <sstream>

using namespace std;


Plansza::Plansza()
{
}

Plansza::Plansza(string name)
{
	wczytaj(name);
	uzupelnij_swoje_dane();
}

void Plansza::wczytaj(std::string nazwa)
{


	ifstream plik;
	plik.open(nazwa);
	if (not plik.good())
	{
		cout << "Bledny plik wejsciowy z plansza!" << endl;
		getchar();
	}
	string linia;
	int y = 0;
	while (getline(plik, linia))
	{
		int x = 0;
		stringstream ss(linia);
		int temp;
		while (ss)
		{
			if (ss >> temp)
			{
				mMap[x][y] = temp;
				x++;
			}
		}
		y++;



	}
	plik.close();

}

void Plansza::makeWallsMap(sf::RenderTarget & target)
{
	sf::Vertex arr[4];
	arr[0].color = sf::Color::Blue;
	arr[1].color = sf::Color::Blue;
	arr[2].color = sf::Color::Blue;
	arr[3].color = sf::Color::Blue;
	for (int x = 0; x < 27; ++x)
	{
		if ((mMap[x][0] == Wall) && (mMap[x + 1][0] == Wall)) drawHorizontalLine(target, x, x + 1, 0);
		if ((mMap[x][30] == Wall) && (mMap[x + 1][30] == Wall)) drawHorizontalLine(target, x, x + 1, 30);
	}
	for (int y = 0; y < 30; ++y)
	{
		if ((mMap[0][y] == Wall) && (mMap[0][y + 1] == Wall)) drawVerticalLine(target, y, y + 1, 0);
		if ((mMap[27][y] == Wall) && (mMap[27][y + 1] == Wall)) drawVerticalLine(target, y, y + 1, 27);
	}
	for (int x = 1; x < 27; ++x) for (int y = 1; y < 30; ++y)
	{
		if (mMap[x][y] == Wall)
		{
			if (mMap[x - 1][y] == Wall) drawHorizontalLine(target, x - 1, x, y);
			if (mMap[x + 1][y] == Wall) drawHorizontalLine(target, x + 1, x, y);
			if (mMap[x][y - 1] == Wall) drawVerticalLine(target, y - 1, y, x);
			if (mMap[x][y + 1] == Wall) drawVerticalLine(target, y + 1, y, x);
		}
	}//for x for y
}

void Plansza::drawHorizontalLine(sf::RenderTarget & rt, int x1, int x2, int y)
{
	sf::Vertex arr[4];
	arr[0].color = sf::Color::Blue;
	arr[1].color = sf::Color::Blue;
	arr[2].color = sf::Color::Blue;
	arr[3].color = sf::Color::Blue;
	arr[0].position = sf::Vector2f(16.f*(x1 + 0.5f), 16.f*(y + 0.5f) - 1.5f);
	arr[1].position = sf::Vector2f(16.f*(x1 + 0.5f), 16.f*(y + 0.5f) + 1.5f);
	arr[2].position = sf::Vector2f(16.f*(x2 + 0.5f), 16.f*(y + 0.5f) + 1.5f);
	arr[3].position = sf::Vector2f(16.f*(x2 + 0.5f), 16.f*(y + 0.5f) - 1.5f);
	rt.draw(arr, 4, sf::Quads);
}

void Plansza::drawVerticalLine(sf::RenderTarget & rt, int y1, int y2, int x)
{
	sf::Vertex arr[4];
	arr[0].color = sf::Color::Blue;
	arr[1].color = sf::Color::Blue;
	arr[2].color = sf::Color::Blue;
	arr[3].color = sf::Color::Blue;
	arr[0].position = sf::Vector2f(16.f*(x + 0.5f) - 1.5f, 16.f*(y1 + 0.5f));
	arr[1].position = sf::Vector2f(16.f*(x + 0.5f) + 1.5f, 16.f*(y1 + 0.5f));
	arr[2].position = sf::Vector2f(16.f*(x + 0.5f) + 1.5f, 16.f*(y2 + 0.5f));
	arr[3].position = sf::Vector2f(16.f*(x + 0.5f) - 1.5f, 16.f*(y2 + 0.5f));
	rt.draw(arr, 4, sf::Quads);
}

void Plansza::wypisz_sie()
{
	cout << "////////////////////////////////////" << endl;
	cout << "mMap: " << endl;
	for (int i = 0; i < 28; i++)
	{
		for (int j = 0; j < 31; j++)
			cout << mMap[i][j] << " ";
		cout << endl;
	}
	cout << endl << endl;
	cout << "Pozycje duszkow: " << endl;
	for (int i = 0; i < 4; i++)
		cout << Duszki_pos[i];
	cout << endl;
	cout << "Pozycja Pacmana: " << Pacman_pos << endl;
}

void Plansza::uzupelnij_swoje_dane()
{
	int iter = 0;
	for (int i = 0; i < 28; i++)
	{
		for (int j = 0; j < 31; j++)
		{
			if (mMap[i][j] == Pill || mMap[i][j] == 2) punkty.push_back(pos(i, j));
			if (mMap[i][j] == 2) Cherry_vec.push_back(pos(i, j));
			if (mMap[i][j] == PacMan) { Pacman_pos.x = i; Pacman_pos.y = j; };
			if (mMap[i][j] == Ghost) { Duszki_pos[iter].x = i; Duszki_pos[iter].y = j; iter++; }
		}
	}


}
