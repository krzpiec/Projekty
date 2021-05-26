
#ifndef PASUEMENU_H
#define PASUEMENU_H

#include <vector>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Network.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include <fstream>
#include <sstream>
#include <stack>
#include <map>

#include "Gui.h"

class PauseMenu
{
private:
	sf::Font& font;
	sf::Text menuText;
	sf::RectangleShape background;
	sf::RectangleShape container;
	std::map<std::string, gui::Button*> buttons;

public:
	PauseMenu(sf::RenderWindow& window, sf::Font& font);
	~PauseMenu();

	std::map<std::string, gui::Button*>& getButtons();


	const bool isButtonPressed(const std::string key);
	void addButton(const std::string key,
		const float y,
		const float width,
		const float height,
		const unsigned char_size,
		const std::string text);
	void update(const sf::Vector2i& mousePosWindow);
	void render(sf::RenderTarget& target);
};

#endif