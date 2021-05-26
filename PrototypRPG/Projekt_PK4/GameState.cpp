#include "GameState.h"



void GameState::initDeferredRender()
{
	this->renderTexture.create(
		this->stateData->gfxSettings->resolution.width, 
		this->stateData->gfxSettings->resolution.height
	);

	this->renderSprite.setTexture(this->renderTexture.getTexture());
	this->renderSprite.setTextureRect(sf::IntRect(
		0,0,
		this->stateData->gfxSettings->resolution.width,
		this->stateData->gfxSettings->resolution.height
	));
}

void GameState::initView()
{
	this->view.setSize(sf::Vector2f(
		this->stateData->gfxSettings->resolution.width, 
		this->stateData->gfxSettings->resolution.height)
	);

	this->view.setCenter(sf::Vector2f(
		this->stateData->gfxSettings->resolution.width / 2.f,
		this->stateData->gfxSettings->resolution.height / 2.f)
	);

}

void GameState::initPlayer()
{
	this->player = new Player(sf::Vector2f(400.f, 500.f), this->textures["Player"]);
}

void GameState::initEnemies()
{
	this->enemy = new Enemy(sf::Vector2f(1100.f, 500.f), this->textures["Enemies"]);
}

void GameState::initPauseMenu()
{
	this->pmenu = new PauseMenu(*this->window, this->font);
	this->pmenu->addButton("QUIT", 500.f, 125.f, 75.f, 30, "Quit");
}

void GameState::initTextures()
{

if (!this->textures["Player"].loadFromFile("Resources/Images/Sprites/Player/gracz1.png"))
{
	throw "ERROR PLAYER_TEX";
}

if (!this->textures["Enemies"].loadFromFile("Resources/Images/Sprites/Enemies/enemy.png"))
{
	throw "ERROR PLAYER_TEX";
}

}

void GameState::initKeybinds()
{
	std::ifstream plik("Config/Gamestate_keybidns.txt");
	if (plik.is_open())
	{
		std::string key = "";
		std::string key2 = "";

		while (plik >> key >> key2)
		{
			this->Keybinds[key] = this->supportedKeys->at(key2);
		}
	}
	plik.close();
	
}

void GameState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/DejaVuSans.ttf"))
	{
		throw("ERROR:MainMenu FONT");
	}
}

void GameState::initTileMap()
{

	this->tileMap = new TileMap(
		this->stateData->gridSize, 
		this->stateData->gfxSettings->resolution.width/ this->stateData->gridSize, 
		this->stateData->gfxSettings->resolution.height / this->stateData->gridSize,"Resources/Images/Tiles/najsik.png"
	);
	this->tileMap->loadFromFile("text.slmp");
}

GameState::GameState(StateData* state_data)
	:State(state_data)
{
	this->initDeferredRender();
	this->initView();
	this->initKeybinds();
	this->initFonts();
	this->initTextures();
	this->initPauseMenu();
	this->initPlayer();
	this->initEnemies();
	this->initTileMap();

}


GameState::~GameState()
{
	delete this->pmenu;
	delete this->player;
	delete this->tileMap;
	delete this->enemy;
}

void GameState::updateView(const float& dt)
{
	this->view.setCenter(std::floor(this->player->getPosition().x), std::floor(this->player->getPosition().y));

}

void GameState::updateInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->Keybinds.at("Close"))) and this->getkeytimeOverlap())
	{
		//this->endState();
		if (not this->pasued)
			this->pauseState();
		else
		{
			this->unpauseState();
		}

	}
	

}

void GameState::updatePlayerInput(const float & dt)
{

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->Keybinds.at("Move_Left"))))
		this->player->move(dt, sf::Vector2f(-1.0f, 0.f));

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->Keybinds.at("Move_Right"))))
		this->player->move(dt, sf::Vector2f(1.0f, 0.f));

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->Keybinds.at("Move_Up"))))
		this->player->move(dt, sf::Vector2f(0.f, -1.0f));

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->Keybinds.at("Move_Down"))))
		this->player->move(dt, sf::Vector2f(0.f, 1.0f));

	//std::cout << this->enemy->getHeading() << std::endl;
	this->enemy->move(dt, sf::Vector2f(0.f,this->enemy->getHeading()));

}

void GameState::updatePMenuButtons()
{
	if (this->pmenu->isButtonPressed("QUIT") and this->getkeytimeOverlap())
	{
		this->endState();
	}
		

}

void GameState::updateTileMap(const float& dt)
{
	this->tileMap->update(dt);
	this->tileMap->updateCollision(this->player, dt);
	this->tileMap->updateCollision(this->enemy, dt);
}


void GameState::update(const float & dt)
{

	this->updateMousePos(&this->view);
	this->updateKeytime(dt);
	this->updateInput(dt);

	if (not this->pasued)
	{
		this->updateView(dt);
		this->updatePlayerInput(dt);

		
		

		this->updateTileMap(dt);



		this->player->update(dt);
		this->enemy->update(dt);
	}
	else
	{
		
		this->pmenu->update(this->mousePosWindow);
		this->updatePMenuButtons();
	}
	

}

void GameState::render(sf::RenderTarget* target)
{
	if (not target)
		target = this->window;

	this->renderTexture.clear();

	this->renderTexture.setView(this->view);
	//this->tileMap->render(this->renderTexture, this->player);
	this->tileMap->render(this->renderTexture);
	this->player->render(this->renderTexture);
	this->enemy->render(this->renderTexture);

	if (this->pasued)
	{
		this->renderTexture.setView(this->renderTexture.getDefaultView());
		this->pmenu->render(this->renderTexture);
	}
	

	this->renderTexture.display();
	//this->renderSprite.setTexture(this->renderTexture.getTexture());
	target->draw(this->renderSprite);

}
