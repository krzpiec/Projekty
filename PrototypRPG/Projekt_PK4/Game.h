#ifndef GAME_H
#define GAME_H



#include "MainMenuState.h"
class Game
{
private:
	


	//Var
	GraphicsSetting gfxSettings;
	StateData stateData;
	sf::RenderWindow *window;
	sf::Event sfEvent;
	sf::Clock dtClock;
	float dt; //delta time

	std::stack<State*> states;
	std::map<std::string, int> SupportedKeys;
	float gridSize;
	//Init
	void initVar();
	
	void initGfxSett();
	void InitWindow();
	void InitKeys();
	void initStateData();
	void initStates();
	
public:
	Game();
	virtual ~Game();


	//Functions
	void EndApp();
	void updateDt();
	void updateSFMLEvents();
	void update();
	void render();
	void run();


};


#endif

