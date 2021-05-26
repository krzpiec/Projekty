
#include "SFML/Graphics.hpp"
#include "Pozycja.h"
#include "Plansza.h"
#include "Obiekt_Dynamiczny.h"

using namespace std;
using namespace sf;


void Obiekt_dyn::change_velocity(Kierunek gdzie)
{

	switch (gdzie)
	{

	case Left:
	{
		velocity.x = -velo;
		velocity.y = 0;
		next_move = Left;
		break;
	}
	case Right:
	{
		velocity.x = velo;
		velocity.y = 0;
		next_move = Right;
		break;
	}
	case Up:
	{
		velocity.y = -velo;
		velocity.x = 0;
		next_move = Up;
		break;
	}
	case Down:
	{
		velocity.y = velo;
		velocity.x = 0;
		next_move = Down;
		break;
	}
	case Stop:
	{
		velocity.x = 0;
		velocity.y = 0;
		next_move = Nothing;
		break;
	}




	}

}

pos Obiekt_dyn::Pozycja_kafelka(Vector2f position)
{
	/*cout << "mMap kafelki: " << endl;
	for (int i = 0; i < 28; i++)
	{
		for (int j = 0; j < 31; j++)
			cout << mMap[i][j] << " ";
		cout << endl;
	}
	cout << endl << endl;*/

	int x = int(position.x);
	int y = int(position.y);

	
		x -= Scale_plus;
		x /= Scale_times;
		y -= Scale_plus;
		y /= Scale_times;
		return pos(x, y);
	



	return pos(-1, -1);
}

bool Obiekt_dyn::Is_At_Node(Vector2f position)
{

	int x = int(position.x);
	int y = int(position.y);

	if (position.x != x or position.y != y)
		return false;

	x -= Scale_plus;
	y -= Scale_plus;

	if (x % 16 == 0 and y % 16 == 0)
		return true;

	return false;
}

bool Obiekt_dyn::weryfikuj_ruch(const Plansza& Map, Vector2f position, Kierunek gdzie)
{
	pos aktualna_pozycja = Pozycja_kafelka(position);
	switch (gdzie)
	{

	case Up:
	{
		if (Map.mMap[aktualna_pozycja.x][aktualna_pozycja.y - 1] != Wall)
			return true;
			
			
		break;
	}

	case Down:
	{
		if (Map.mMap[aktualna_pozycja.x][aktualna_pozycja.y + 1] != Wall)
			return true;
			
		break;
	}
	case Left:
	{
		if (Map.mMap[aktualna_pozycja.x - 1][aktualna_pozycja.y] != Wall)
			return true;
			
		break;
	}

	case Right:
	{
		if (Map.mMap[aktualna_pozycja.x + 1][aktualna_pozycja.y] != Wall)
			return true;
			
		break;
	}
	default:
		return false;
	}
	return false;
}

void Obiekt_dyn::Change_Velocity(Vector2f& velocity, Kierunek gdzie, const float base)
{

	switch (gdzie)
	{

	case Left:
	{
		velocity.x = -base;
		velocity.y = 0;
		break;
	}

	case Right:
	{
		velocity.x = base;
		velocity.y = 0;
		break;
	}

	case Up:
	{
		velocity.y = -base;
		velocity.x = 0;
		break;
	}

	case Down:
	{
		velocity.y = base;
		velocity.x = 0;
		break;
	}

	case Nothing:
	{
		velocity.y = 0;
		velocity.x = 0;
		break;
	}


	}


}

bool Obiekt_dyn::Wall_collision(Vector2f position, Kierunek heading)
{
	pos aktualna = Pozycja_kafelka(position);
	if (not Is_At_Node(position))
		return false;

	//cornery
	if (aktualna.x == 1 and aktualna.y == 1)
		if (heading == Up or Left)
			return true;

	if (aktualna.x == 26 and aktualna.y == 1)
		if (heading == Up or Right)
			return true;


	if (aktualna.x == 1 and aktualna.y == 29)
		if (heading == Left or Down)
			return true;

	if (aktualna.x == 26 and aktualna.y == 29)
		if (heading == Right or Down)
			return true;

	/////////
	//krawedzie
	if (aktualna.y == 1 and aktualna.x!= 1  and heading == Up)
		return true;
	if (aktualna.x == 1 and heading == Left)
		return true;
	if (aktualna.x == 26 and heading == Right)
		return true;
	if (aktualna.y == 29 and heading == Down)
		return true;



	return false;
}
