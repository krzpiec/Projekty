#ifndef GRAPHICSSETTINGS_H
#define GRAPHICSSETTINGS_H
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
#include <map> ///POPRAWIC

class GraphicsSetting
{
public:
	std::string title;
	sf::VideoMode resolution;
	bool fullscreen;
	bool verticalSync;
	unsigned frameRateLimit;
	sf::ContextSettings contextSettings;
	std::vector<sf::VideoMode> videoModes;


	GraphicsSetting();
	


	void saveToFile(const std::string path);
	
	void loadDromFile(const std::string path);

};

#endif // !GRAPHICSSETTINGS_H