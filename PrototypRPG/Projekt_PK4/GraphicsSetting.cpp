#include "GraphicsSetting.h"

GraphicsSetting::GraphicsSetting()
{
	
		this->title = "DEFAULT";
		this->resolution = sf::VideoMode::getDesktopMode();
		this->fullscreen = false;
		this->verticalSync = false;
		this->frameRateLimit = 120;
		this->contextSettings.antialiasingLevel = 0;
		this->videoModes = sf::VideoMode::getFullscreenModes();


	
}

void GraphicsSetting::saveToFile(const std::string path)
{

		std::ofstream plik(path);


		if (plik.is_open())
		{
			plik << this->resolution.width << " " << this->resolution.height;
			plik << fullscreen;
			plik << frameRateLimit;
			plik << verticalSync;
			plik << this->contextSettings.antialiasingLevel;
		}
		plik.close();

}

void GraphicsSetting::loadDromFile(const std::string path)
{
	
		std::ifstream plik(path);


		if (plik.is_open())
		{
			plik >> this->resolution.width >> this->resolution.height;
			plik >> fullscreen;
			plik >> frameRateLimit;
			plik >> verticalSync;
			plik >> this->contextSettings.antialiasingLevel;
		}
		plik.close();

	
}
