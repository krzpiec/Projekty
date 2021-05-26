#include "Ghost.h"
#include <algorithm>
Duszek::Duszek(Plansza & Map, int pktory, Texture* ptex_all)
{
	tex_all = ptex_all;
	ksztalt.setTexture(*ptex_all);

	ktory = pktory;
	ksztalt.setTextureRect(IntRect(ktory * 24, 0, 24, 24));
	clock.restart();
	Map.mMap[Map.Duszki_pos[ktory].x][Map.Duszki_pos[ktory].y] = 1; 
	int x = Map.Duszki_pos[ktory].x * Scale_times;
	x += Scale_plus;
	int y = Map.Duszki_pos[ktory].y * Scale_times;
	y += Scale_plus;
	ksztalt.setPosition(x, y);
	ksztalt.setColor(sf::Color::White);
	ksztalt.setOrigin(this->promien, this->promien);

}

void Duszek::Zmiana_Stanu()
{
	if (Stan == Eaten)
	{
		ksztalt.setTextureRect(IntRect(96, 0, 24, 24));
		ksztalt.setColor(Color::White);
		return;
	}

	if (Stan == Frightened)
		ksztalt.setColor(sf::Color::Red);
	Frightened_end();
	Scattered_end();
	Scattered();
}

void Duszek::update(const Plansza& Mapa, Nazwy ktory, Vector2f Pac_Pos, Kierunek Pac_heading, int frames)
{
	Zmiana_Stanu();
	if (eaten_stop)
		return;
	switch (Stan)
	{
	case Scatter:
	{
		Scatter_update(Mapa, ktory);
		break;
	}
	case Chase:
	{
		Chase_update(Mapa, ktory, Pac_Pos, Pac_heading);
		break;
	}
	case Frightened:
	{
		Frightened_update(Mapa, ktory);
		break;

	}
	case Eaten:
	{
		Eaten_update(Mapa);
		break;
	}
	}

}

void Duszek::Booster_Picked()
{
	Stan = Frightened;
	clock.restart();
}

void Duszek::Frightened_end()
{
	if (Stan == Frightened and elapsed.asSeconds() > 5)
	{
		Stan = Chase;
		ksztalt.setColor(sf::Color::White);
		clock.restart();
	}

}

void Duszek::Scattered()
{
	if (elapsed.asSeconds() > 12)
	{
		Stan = Scatter;
		ksztalt.setColor(Color::Magenta);
		clock.restart();
	}
}

void Duszek::Scattered_end()
{
	if (Stan == Scatter and elapsed.asSeconds() > 5)
	{
		Stan = Chase;
		IsAtPoint = false;
		ksztalt.setColor(sf::Color::White);
		clock.restart();
	}
}

vector<pos> Duszek::mozliwe_kierunki(const Plansza & Mapa)
{
	vector<pos> mozliwe_kierunki;
	pos aktualna = Pozycja_kafelka(getPosition());

	if (weryfikuj_ruch(Mapa, getPosition(), Up) and Down != next_move)
		mozliwe_kierunki.push_back(pos(aktualna.x, aktualna.y - 1));

	if (weryfikuj_ruch(Mapa, getPosition(), Left) and Right != next_move)
		mozliwe_kierunki.push_back(pos(aktualna.x - 1, aktualna.y));

	if (weryfikuj_ruch(Mapa, getPosition(), Right) and Left != next_move)
		mozliwe_kierunki.push_back(pos(aktualna.x + 1, aktualna.y));

	if (weryfikuj_ruch(Mapa, getPosition(), Down) and Up != next_move)
		mozliwe_kierunki.push_back(pos(aktualna.x, aktualna.y + 1));

	return mozliwe_kierunki;
}

float Duszek::Distance(pos docelowa, Vector2f Pac_Pos)
{
	float x = docelowa.x * Scale_times;
	x += Scale_plus;
	float y = docelowa.y * Scale_times;
	y += Scale_plus;

	float skladowa_x = x - Pac_Pos.x;
	float skladowa_y = y - Pac_Pos.y;

	float x_kwadrat = pow(skladowa_x, 2);
	float y_kwadrat = pow(skladowa_y, 2);

	float dist = x_kwadrat + y_kwadrat;

	return sqrt(dist);
}

Kierunek Duszek::Pos_to_heading(pos Docelowa)
{
	int x = Docelowa.x * Scale_times;
	x += Scale_plus;
	int y = Docelowa.y * Scale_times;
	y += Scale_plus;

	if (getPosition().x < x)
		return Right;
	if (getPosition().x > x)
		return Left;
	if (getPosition().y < y)
		return Down;
	if (getPosition().y > y)
		return Up;

	return Nothing; 
}

void Duszek::Frightened_update(const Plansza & Mapa, Nazwy ktory)
{
	ksztalt.move(velocity);
	vector<pos> mozliwe_kier = mozliwe_kierunki(Mapa);
	int indeks = rand() % mozliwe_kier.size();
	Kierunek heading = Pos_to_heading(mozliwe_kier[indeks]);
	next_move = heading;
	if (Is_At_Node(getPosition()))
		Change_Velocity(velocity, heading, velo);
}

Kierunek Duszek::Which_tile(const Plansza & Mapa, Vector2f target)
{
	vector<pos> mozliwe_kier = mozliwe_kierunki(Mapa);
	vector<float> odleglosci;
	for (auto i : mozliwe_kier)
		odleglosci.push_back(Distance(i, target));
	vector<float>::iterator min = min_element(odleglosci.begin(), odleglosci.end());
	int indeks = distance(odleglosci.begin(), min);
	return Pos_to_heading(mozliwe_kier[indeks]);

}

void Duszek::Chase_update(const Plansza& Mapa, Nazwy ktory, Vector2f Pac_Pos, Kierunek Pac_heading)
{
	ksztalt.move(velocity);


	Vector2f Targer = GetTarged(ktory, Pac_Pos, Pac_heading);
	if (ktory == D)
	{
		int max_dist = 10 * Scale_times;
		if (Distance(Pozycja_kafelka(getPosition()), Pac_Pos) < max_dist)
		{
			Targer = GetTarged(A, Pac_Pos, Pac_heading);
		}

	}
	Kierunek heading = Which_tile(Mapa, Targer);
	next_move = heading;
	if (Is_At_Node(getPosition()))
		Change_Velocity(velocity, heading, velo);



}

Vector2f Duszek::GetTarged(Nazwy ktory, Vector2f Pac_Pos, Kierunek Pac_heading)
{
	Vector2f TargetPoint = Pac_Pos;
	int modify = 0;
	switch (ktory)
	{
	case A:
	{
		return Pac_Pos;
		break;
	}
	case B:
	{
		modify = 4;
		break;
	}
	case C:
	{
		modify = 2;
		break;
	}
	case D:
	{
		Vector2f pos;
		pos.x = Scale_times + Scale_plus;
		pos.y = 31 * Scale_times + Scale_plus;
		return pos;
		break;
	}
	}

	switch (Pac_heading)
	{
	case Up:
	{
		TargetPoint.y -= modify * Scale_times;
		break;
	}
	case Down:
	{
		TargetPoint.y += modify * Scale_times;
		break;
	}
	case Left:
	{
		TargetPoint.x -= modify * Scale_times;
		break;
	}
	case Right:
	{
		TargetPoint.x += modify * Scale_times;
		break;
	}

	}
	return TargetPoint;
}

void Duszek::Eaten_update(const Plansza & Mapa)
{

	if (eaten_stop)
		return;

	if (getPosition().x == 8 and getPosition().y < -10)
		eaten_stop = true;
		


	ksztalt.move(this->velocity);
	int x = Scale_times;

	Vector2f LeftTunel(-5 * x, 13 * x);
	Vector2f RightTunel(35 * x, 13 * x);

	Vector2f Targer;
	if (26 - getPosition().x > getPosition().x)
	{
		Targer = RightTunel;
	}
	else
		Targer = LeftTunel;
	Kierunek heading = Which_tile(Mapa, Targer);
	next_move = heading;
	if (Is_At_Node(getPosition()))
		Change_Velocity(velocity, heading, velo);
}

void Duszek::Scatter_update(const Plansza& Mapa, Nazwy ktory)
{
	switch (ktory)
	{
	case A:
	{
		Scatter_GhostA(Mapa);
		break;
	}
	case B:
	{
		Scatter_GhostB(Mapa);
		break;
	}
	case C:
	{
		Scatter_GhostC(Mapa);
		break;
	}
	case D:
	{
		Scatter_GhostD(Mapa);
		break;
	}


	}
}

void Duszek::Scatter_GhostA(const Plansza& Mapa)
{
	
	ksztalt.move(velocity);
	pos aktualna_pozycja = Pozycja_kafelka(getPosition());
	if (aktualna_pozycja.y != 1 and not IsAtPoint)
	{
		if (weryfikuj_ruch(Mapa, getPosition(), Up))
		{
			if (Is_At_Node(getPosition()))
			{
				next_move = Up;
				Change_Velocity(velocity, Up, velo);
				return;
			}

		}
		else
		{
			if (Is_At_Node(getPosition()))
			{
				Change_Velocity(velocity, Left, velo);

				next_move = Left;

				return;
			}

		}

	}
	if (Is_At_Node(getPosition()) and not IsAtPoint)
	{
		next_move = Left;
		Change_Velocity(velocity, Left, velo);
	}

	if (aktualna_pozycja.x == 1 and aktualna_pozycja.y == 1 and Is_At_Node(getPosition()))
	{
		IsAtPoint = true;
		next_move = Right;
		Change_Velocity(velocity, Right, velo);
	}

	if (aktualna_pozycja.x == 5 and aktualna_pozycja.y == 1 and Is_At_Node(getPosition()) and IsAtPoint)
	{
		next_move = Down;
		Change_Velocity(velocity, Down, velo);
	}

	if (aktualna_pozycja.x == 5 and aktualna_pozycja.y == 5 and Is_At_Node(getPosition()) and IsAtPoint)
	{
		next_move = Left;
		Change_Velocity(velocity, Left, velo);
	}

	if (aktualna_pozycja.x == 1 and aktualna_pozycja.y == 5 and Is_At_Node(getPosition()) and IsAtPoint)
	{
		next_move = Up;
		Change_Velocity(velocity, Up, velo);
	}
}

void Duszek::Scatter_GhostB(const Plansza & Mapa)
{
	
	ksztalt.move(velocity);
	pos aktualna_pozycja = Pozycja_kafelka(getPosition());
	if (aktualna_pozycja.x != 26 and not IsAtPoint)
	{
		if (weryfikuj_ruch(Mapa, getPosition(), Right))
		{
			if (Is_At_Node(getPosition()))
			{
				next_move = Right;
				Change_Velocity(velocity, Right, velo);
				return;
			}

		}
		else
		{
			if (Is_At_Node(getPosition()))
			{
				Change_Velocity(velocity, Up, velo);

				next_move = Up;

				return;
			}

		}

	}
	if (Is_At_Node(getPosition()) and not IsAtPoint)
	{
		next_move = Up;
		Change_Velocity(velocity, Up, velo);
	}

	if (aktualna_pozycja.x == 26 and aktualna_pozycja.y == 1 and Is_At_Node(getPosition()))
	{
		IsAtPoint = true;
		next_move = Left;
		Change_Velocity(velocity, Left, velo);
	}

	if (aktualna_pozycja.x == 21 and aktualna_pozycja.y == 1 and Is_At_Node(getPosition()) and IsAtPoint)
	{
		next_move = Down;
		Change_Velocity(velocity, Down, velo);
	}

	if (aktualna_pozycja.x == 21 and aktualna_pozycja.y == 5 and Is_At_Node(getPosition()) and IsAtPoint)
	{
		next_move = Right;
		Change_Velocity(velocity, Right, velo);
	}

	if (aktualna_pozycja.x == 26 and aktualna_pozycja.y == 5 and Is_At_Node(getPosition()) and IsAtPoint)
	{
		next_move = Up;
		Change_Velocity(velocity, Up, velo);
	}
}

void Duszek::Scatter_GhostC(const Plansza & Mapa)
{
	ksztalt.move(velocity);
	pos aktualna_pozycja = Pozycja_kafelka(getPosition());
	if (aktualna_pozycja.y != 29 and not IsAtPoint)
	{
		if (weryfikuj_ruch(Mapa, getPosition(), Down))
		{
			if (Is_At_Node(getPosition()))
			{
				next_move = Down;
				Change_Velocity(velocity, Down, velo);
				return;
			}

		}
		else
		{
			if (Is_At_Node(getPosition()))
			{
				Change_Velocity(velocity, Right, velo);

				next_move = Right;

				return;
			}

		}

	}
	if (Is_At_Node(getPosition()) and not IsAtPoint)
	{
		next_move = Right;
		Change_Velocity(velocity, Right, velo);
	}

	if (aktualna_pozycja.x == 26 and aktualna_pozycja.y == 29 and Is_At_Node(getPosition()))
	{
		IsAtPoint = true;
		next_move = Up;
		Change_Velocity(velocity, Up, velo);
	}

	if (aktualna_pozycja.x == 26 and aktualna_pozycja.y == 25 and Is_At_Node(getPosition()) and IsAtPoint)
	{
		next_move = Left;
		Change_Velocity(velocity, Left, velo);
	}

	if (aktualna_pozycja.x == 21 and aktualna_pozycja.y == 25 and Is_At_Node(getPosition()) and IsAtPoint)
	{
		next_move = Down;
		Change_Velocity(velocity, Down, velo);
	}

	if (aktualna_pozycja.x == 21 and aktualna_pozycja.y == 29 and Is_At_Node(getPosition()) and IsAtPoint)
	{
		next_move = Right;
		Change_Velocity(velocity, Right, velo);
	}
}

void Duszek::Scatter_GhostD(const Plansza & Mapa)
{

	ksztalt.move(velocity);
	pos aktualna_pozycja = Pozycja_kafelka(getPosition());

	if (aktualna_pozycja.x != 1 and not IsAtPoint)
	{

		if (weryfikuj_ruch(Mapa, getPosition(), Left))
		{
			if (Is_At_Node(getPosition()))
			{
				next_move = Left;
				Change_Velocity(velocity, Left, velo);
				return;
			}

		}
		else
		{
			if (Is_At_Node(getPosition()))
			{
				Change_Velocity(velocity, Down, velo);

				next_move = Down;

				return;
			}

		}

	}
	if (Is_At_Node(getPosition()) and not IsAtPoint)
	{
		next_move = Down;
		Change_Velocity(velocity, Down, velo);
	}
	if (aktualna_pozycja.x == 1 and aktualna_pozycja.y == 29 and Is_At_Node(getPosition()))
	{
		IsAtPoint = true;
		next_move = Right;
		Change_Velocity(velocity, Right, velo);
	}

	if (aktualna_pozycja.x == 5 and aktualna_pozycja.y == 29 and Is_At_Node(getPosition()) and IsAtPoint)
	{
		next_move = Up;
		Change_Velocity(velocity, Up, velo);
	}

	if (aktualna_pozycja.x == 5 and aktualna_pozycja.y == 25 and Is_At_Node(getPosition()) and IsAtPoint)
	{
		next_move = Left;
		Change_Velocity(velocity, Left, velo);
	}

	if (aktualna_pozycja.x == 1 and aktualna_pozycja.y == 25 and Is_At_Node(getPosition()) and IsAtPoint)
	{
		next_move = Down;
		Change_Velocity(velocity, Down, velo);
	}



}