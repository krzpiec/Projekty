#include "Pacman.h"
#include <cctype>
#include <cmath>

Pacman::Pacman(Plansza& Map, Texture* ptex_all)
{
	tex_all = ptex_all;
	ksztalt.setTexture(*ptex_all);
	ksztalt.setTextureRect(IntRect(0, 0, 24, 24));
	velo = 4.0f;

	Map.mMap[Map.Pacman_pos.x][Map.Pacman_pos.y] = 1;
	int x = Map.Pacman_pos.x  * Scale_times;
	x += Scale_plus
	int y = Map.Pacman_pos.y * Scale_times;
	y += Scale_plus
	ksztalt.setPosition(x, y);

	ksztalt.setOrigin(this->promien, this->promien);


}

void Pacman::update(const Plansza& Mapa, Nazwy ktory, Vector2f Pac_Pos, Kierunek Pac_heading,int frames)
{
	ksztalt.move(this->velocity);
	int scale = 24;
	if(frames == 0 )
		ksztalt.setTextureRect(IntRect(0, 0, scale, scale));
	if(frames == 10)
		ksztalt.setTextureRect(IntRect(scale, 0, scale, scale));
	if (frames == 20)
		ksztalt.setTextureRect(IntRect(scale*2, 0, scale, scale));

	pos aktualna = Pozycja_kafelka(getPosition());
	if (aktualna.x == -1 and aktualna.y == 13 and next_move == Left)
		ksztalt.move(448, 0);
	if (aktualna.x == 28 and aktualna.y == 13 and next_move == Right)
		ksztalt.move(-448, 0);

	if (aktualna.x <= 1 and aktualna.y == 13 and next_move == Left)
		return;
	

	if (aktualna.x >= 26 and aktualna.y == 13 and next_move == Right)
		return;
	

	if (Wall_collision(getPosition(), next_move))
	{
		Change_Velocity(velocity, Nothing, velo);
		next_move = Nothing;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
	{
		if (weryfikuj_ruch(Mapa, getPosition(), Left) and Is_At_Node(getPosition()))
		{
			Change_Velocity(velocity, Left, velo);
			change_rotation(Left);
		}
			
		next_move = Left;
		return;
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
	{
		if (weryfikuj_ruch(Mapa, getPosition(), Right) and Is_At_Node(getPosition()))
		{
			Change_Velocity(velocity, Right, velo);
			change_rotation(Right);
		}
		next_move = Right;

		return;
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
	{
		if (weryfikuj_ruch(Mapa, getPosition(), Up) and Is_At_Node(getPosition()))
		{
			Change_Velocity(velocity, Up, velo);
		}
			
		next_move = Up;
		return;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
	{
		if (weryfikuj_ruch(Mapa, getPosition(), Down) and Is_At_Node(getPosition()))
		{
			Change_Velocity(velocity, Down, velo);
		}

		next_move = Down;
		return;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
	{
		Change_Velocity(velocity, Nothing, velo);
		next_move = Nothing;
		return;
	}

		
	if (weryfikuj_ruch(Mapa, getPosition(), next_move) and Is_At_Node(getPosition()))
	{
		Change_Velocity(velocity, next_move, velo);
		change_rotation(next_move);
	}
	


}


