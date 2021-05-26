#include "Game.h"
//Static f


void Game::initVar()
{
	this->window = nullptr;
	this->dt = 0;
	this->gridSize = 64.f;
}

void Game::initStateData()
{
	this->stateData.window = this->window;
	this->stateData.gfxSettings = &this->gfxSettings;
	this->stateData.supportedKeys = &this->SupportedKeys;
	this->stateData.states = &this->states;
	this->stateData.gridSize = this->gridSize;
}

void Game::initGfxSett()
{
	this->gfxSettings.loadDromFile("Config\Graphics.txt");


}

//Init f
void Game::InitWindow()
{
	
	if(this->gfxSettings.fullscreen)
		this->window = new sf::RenderWindow(this->gfxSettings.resolution, this->gfxSettings.title, sf::Style::Fullscreen | sf::Style::Titlebar |sf::Style::Close, this->gfxSettings.contextSettings);
	else
		this->window = new sf::RenderWindow(this->gfxSettings.resolution, this->gfxSettings.title, sf::Style::Titlebar | sf::Style::Close, this->gfxSettings.contextSettings);

	this->window->setFramerateLimit(this->gfxSettings.frameRateLimit);
	this->window->setVerticalSyncEnabled(this->gfxSettings.verticalSync);


}

void Game::InitKeys()
{
	std::ifstream plik("Config/Supported_Keys.txt");
	if (plik.is_open())
	{
		std::string key = "";
		int key_val = 0;
		
		while (plik >> key >> key_val)
		{
			this->SupportedKeys[key] = key_val;
		}
	}
	plik.close();
	//debug
	for (auto i : this->SupportedKeys)
		std::cout << i.first << " " << i.second << std::endl;
}

void Game::initStates()
{
	this->states.push(new MainMenuState(&this->stateData));
	//this->states.push(new GameState(this->window, &this->SupportedKeys));
}


//Constr/Destr 


Game::Game()
{
	this->initVar();
	this->initGfxSett();
	this->InitWindow();
	this->InitKeys();
	this->initStateData();
	this->initStates();
	
}

Game::~Game()
{
	delete this->window;
	while (!this->states.empty())
	{
		delete this->states.top();
		this->states.pop();
	}
		

}




//Functions

void Game::EndApp()
{
	std::cout << "Ending" << std::endl;
}

void Game::updateDt()
{
	this->dt = this->dtClock.restart().asSeconds();
}

void Game::updateSFMLEvents()
{
	while (this->window->pollEvent(this->sfEvent))
	{
		if (this->sfEvent.type = sf::Event::Closed)
			this->window->close();
	}


}

void Game::update()
{
	this->updateSFMLEvents();
	if (!this->states.empty() )
	{
		this->states.top()->update(this->dt);
		if (this->states.top()->getQuit())
		{

			this->states.top()->endState();

			//delete this->states.top();

			this->states.pop();
		}

	}
	else //app end
	{
		this->EndApp();
		this->window->close();
	}
}

void Game::render()
{
	this->window->clear();


	if (!this->states.empty())
		this->states.top()->render(this->window);


	this->window->display();
}

void Game::run()
{
	while(this->window->isOpen())
	{
		this->updateDt();
		this->update();
		this->render();

	}


}
