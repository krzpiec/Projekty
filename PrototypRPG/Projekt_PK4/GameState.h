#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "State.h"
#include "Map_Tile.h";
#include "PasueMenu.h"
#include "Enemy.h"
class PauseMenu;
class Player;
class TileMap;
class sf::View;
class sf::Font;
class sf::RenderTexture;

class GameState :
	public State
{
private:
	sf::View view;
	sf::RenderTexture renderTexture;
	sf::Sprite renderSprite;
	sf::Font font;
	Player* player;
	PauseMenu* pmenu;
	TileMap* tileMap;
	Enemy* enemy;
	//Functions
	void initDeferredRender();
	void initView();
	void initPlayer();
	void initEnemies();
	void initPauseMenu();
	void initTextures();
	void initKeybinds();
	void initFonts();
	void initTileMap();
public:
	GameState(StateData* state_data);
	~GameState();

	void updateView(const float& dt);
	void updateInput(const float& dt);
	void updatePlayerInput(const float & dt);
	void updatePMenuButtons();
	void updateTileMap(const float& dt);
	void update(const float & dt);
	void render(sf::RenderTarget* target);


	

};



#endif // !GAMESTATE_H

