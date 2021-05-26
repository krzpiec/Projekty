#ifndef STATE_H
#define STATE_H

#include "Player.h"
#include "GraphicsSetting.h"



class Player;
class GraphicsSetting;
class State;

class StateData
{
public:
	float gridSize;
	GraphicsSetting* gfxSettings;
	sf::RenderWindow* window;
	std::map<std::string, int>* supportedKeys;
	std::stack<State*>* states;

	StateData()
	{


	};
};




class State
{
private:



protected:
	StateData* stateData;
	std::stack<State*>* states;
	sf::RenderWindow* window;
	bool quit;
	bool pasued;
	float keytime;
	float keytimeMax;
	float gridSize;
	//recources
	std::map<std::string, sf::Texture> textures;
	std::map<std::string, int>* supportedKeys;
	std::map<std::string, int> Keybinds;

	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;
	sf::Vector2u mousePosGrid;
	//Functions
	virtual void initKeybinds() = 0;

public:
	const bool& getQuit() const;
	const bool getkeytimeOverlap();


	State(StateData* state_data);
	virtual ~State();

	void endState();
	void pauseState();
	void unpauseState();

	virtual void updateMousePos(sf::View* view = nullptr);
	virtual void updateKeytime(const float& dt);
	virtual void updateInput(const float & dt) = 0;
	virtual void update(const float & dt) = 0;
	virtual void render(sf::RenderTarget* target = nullptr) = 0;
};

#endif

