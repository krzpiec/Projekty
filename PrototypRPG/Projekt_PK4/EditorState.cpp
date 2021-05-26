
#include "EditorState.h"

//Initializer functions
void EditorState::initVariables()
{
	this->textureRect = sf::IntRect(0, 0, static_cast<int>(this->stateData->gridSize), static_cast<int>(this->stateData->gridSize));
	this->collision = false;
	this->type = TileTypes::DEFAULT;
	this->cameraSpeed = 400.f;
	this->texturePage = 0;
	this->maxtexturePage = 0;
	this->actualLayer = 0;
}

void EditorState::initView()
{
	this->view.setSize(
		sf::Vector2f(this->stateData->gfxSettings->resolution.width, 
			this->stateData->gfxSettings->resolution.height)
	);

	this->view.setCenter(
		sf::Vector2f(this->stateData->gfxSettings->resolution.width / 2.f,
			this->stateData->gfxSettings->resolution.height / 2.f)
	);
}

void EditorState::initBackground()
{

}

void EditorState::initFonts()
{
	try 
	{
		this->font.loadFromFile("Fonts/DejaVuSans.ttf");
	}
	catch (const std::exception& ex)
	{
		std::cerr << ex.what();
	}

}

void EditorState::initText()
{


	this->cursorText.setFont(this->font);
	this->cursorText.setCharacterSize(12);
	this->cursorText.setFillColor(sf::Color::White);
	this->cursorText.setPosition(this->mousePosView.x, this->mousePosView.y);
	

}
	

void EditorState::initKeybinds()
{
	std::ifstream plik("Config/Editorstate_keybidns.txt");
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

void EditorState::initPauseMenu()
{
	this->pmenu = new PauseMenu(*this->window, this->font);

	this->pmenu->addButton("QUIT", 500.f, 125.f, 75.f, 30, "Quit");

	this->pmenu->addButton("SAVE", 800.f, 125.f, 75.f, 30, "Save");

	this->pmenu->addButton("LOAD", 700.f, 125.f, 75.f, 30, "Load");
}

void EditorState::initButtons()
{

}

void EditorState::initGui()
{
	this->sidebar.setSize(sf::Vector2f(64.f, static_cast<float>(this->stateData->gfxSettings->resolution.height)));
	this->sidebar.setFillColor(sf::Color(50, 50, 50, 100));
	this->sidebar.setOutlineColor(sf::Color(200, 200, 200, 150));
	this->sidebar.setOutlineThickness(1.f);

	this->selectorRect.setSize(sf::Vector2f(this->stateData->gridSize, this->stateData->gridSize));

	this->selectorRect.setFillColor(sf::Color(255,255,255,100));
	this->selectorRect.setOutlineThickness(-1.f);
	this->selectorRect.setOutlineColor(sf::Color::Green);

	this->selectorRect.setTexture(this->tileMap->getTileSheet());
	this->selectorRect.setTextureRect(this->textureRect);


	this->textureSelector = new gui::TextureSelector(
		0.f, 0.f, this->tileMap->getTileSheet()->getSize().x, this->tileMap->getTileSheet()->getSize().y,
		this->stateData->gridSize, this->tileMap->getTileSheet(),
		this->font, "TS"
	);


}

void EditorState::initTileMap()
{
	this->tileMap = new TileMap(
		this->stateData->gridSize,
		this->stateData->gfxSettings->resolution.width / this->stateData->gridSize,
		this->stateData->gfxSettings->resolution.height / this->stateData->gridSize, "Resources/Images/Tiles/najsik.png"
	);
}

EditorState::EditorState(StateData* state_data)
	: State(state_data)
{
	this->initVariables();
	this->initView();
	this->initBackground();
	this->initFonts();
	this->initText();
	this->initKeybinds();
	this->initPauseMenu();
	this->initButtons();
	this->initTileMap();
	this->initGui();
	
}

EditorState::~EditorState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}

	delete this->pmenu;

	delete this->tileMap;
	delete this->textureSelector;
}

//Functions
void EditorState::updateInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->Keybinds.at("Close"))) && this->getkeytimeOverlap())
	{
		if (!this->pasued)
			this->pauseState();
		else
			this->unpauseState();
	}
}

void EditorState::updateEditorInput(const float& dt)
{

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->Keybinds.at("MOVE_CAMERA_UP"))))
	{
		this->view.move(0.f, -this->cameraSpeed * dt);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->Keybinds.at("MOVE_CAMERA_DOWN"))))
	{
		this->view.move(0.f, this->cameraSpeed * dt);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->Keybinds.at("MOVE_CAMERA_LEFT"))))
	{
		this->view.move(-this->cameraSpeed * dt,0.f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->Keybinds.at("MOVE_CAMERA_RIGHT"))))
	{
		this->view.move(this->cameraSpeed * dt, 0.f);
	}


	//Add a tile to the tilemap
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) and this->getkeytimeOverlap())
	{
		if (!this->sidebar.getGlobalBounds().contains(sf::Vector2f(this->mousePosWindow)))
		{
			if (!this->textureSelector->getActive())
			{
				this->tileMap->addTile(this->mousePosGrid.x, this->mousePosGrid.y, this->actualLayer , this->textureRect, this->collision, this->type);
			}
			else
			{
				this->textureRect = this->textureSelector->getTextureRect();
			}
		}
	}
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Right) and this->getkeytimeOverlap())
	{
		if (!this->sidebar.getGlobalBounds().contains(sf::Vector2f(this->mousePosWindow)))
		{
			if (!this->textureSelector->getActive())
				this->tileMap->removeTile(this->mousePosGrid.x, this->mousePosGrid.y, 0);
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) and this->getkeytimeOverlap())
	{
		if (!this->sidebar.getGlobalBounds().contains(sf::Vector2f(this->mousePosWindow)))
			if (!this->textureSelector->getActive())
				this->tileMap->removeTile(this->mousePosGrid.x, this->mousePosGrid.y, 0);
	}


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->Keybinds.at("TOOGLE_COLLISION"))) && this->getkeytimeOverlap())
	{
		this->collision = !this->collision;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->Keybinds.at("INCREASE_TYPE"))) && this->getkeytimeOverlap())
	{
		this->type++;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->Keybinds.at("DECREASE_TYPE"))) && this->getkeytimeOverlap())
	{
		if(this->type > 0)
		this->type--;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->Keybinds.at("INCREASE_LAYER"))) && this->getkeytimeOverlap())
	{
		if (this->actualLayer <= this->maxLayer)
			this->actualLayer++;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->Keybinds.at("DECREASE_LAYER"))) && this->getkeytimeOverlap())
	{
		if (this->actualLayer > 0)
			this->actualLayer--;
	}
}

void EditorState::updateButtons()
{
	/*Updates all the buttons in the state and handles their functionlaity.*/

	for (auto& it : this->buttons)
	{
		it.second->update(this->mousePosWindow);
	}
}

void EditorState::updateGui(const float& dt)
{
	this->textureSelector->update(this->mousePosWindow, dt);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) and this->getkeytimeOverlap())
		this->textureSelector->hide();

	if (!this->textureSelector->getActive())
	{
		this->selectorRect.setTextureRect(this->textureRect);
		this->selectorRect.setPosition(this->mousePosGrid.x * this->stateData->gridSize, this->mousePosGrid.y * this->stateData->gridSize);
	}

	this->selectorRect.setPosition(this->mousePosGrid.x * this->stateData->gridSize, this->mousePosGrid.y * this->stateData->gridSize);

	cursorText.setPosition(this->mousePosView.x+ 100.f, this->mousePosView.y - 50);
	std::stringstream ss;
	ss <<
		this->mousePosView.x << " " << this->mousePosView.y << "\n" <<
		this->mousePosGrid.x << " " << this->mousePosGrid.y << "\n" <<
		this->textureRect.left << " " << this->textureRect.top << "\n" <<
		"Collision: " << std::boolalpha << this->collision << " \n" <<
		"Type:  " << this->type <<" " <<this->actualLayer;
	cursorText.setString(ss.str());

	this->textureSelector->update(this->mousePosWindow, dt);

}


void EditorState::updatePauseMenuButtons()
{
	if (this->pmenu->isButtonPressed("QUIT"))
		this->endState();

	if (this->pmenu->isButtonPressed("SAVE"))
		this->tileMap->saveToFile("text.slmp");

	if (this->pmenu->isButtonPressed("LOAD"))
		this->tileMap->loadFromFile("text.slmp");
}

void EditorState::update(const float& dt)
{
	this->updateMousePos(&this->view);
	this->updateKeytime(dt);
	this->updateInput(dt);

	if (!this->pasued) //Unpaused
	{
		this->updateButtons();
		this->updateGui(dt);
		this->updateEditorInput(dt);
	}
	else //Paused
	{
		this->pmenu->update(this->mousePosWindow);
		this->updatePauseMenuButtons();
	}
}

void EditorState::renderButtons(sf::RenderTarget& target)
{
	for (auto& it : this->buttons)
	{
		it.second->render(&target);
	}
}

void EditorState::renderGui(sf::RenderTarget& target)
{
	if (!this->textureSelector->getActive())
	{
		target.setView(this->view);
		target.draw(this->selectorRect);
	}
		
	target.setView(this->window->getDefaultView());
	this->textureSelector->render(target);
	target.draw(this->sidebar);


	target.setView(this->view);
	target.draw(this->cursorText);

	

}

void EditorState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;


	target->setView(this->view);
	this->tileMap->render(*target);

	target->setView(this->window->getDefaultView());

	this->renderButtons(*target);
	this->renderGui(*target);

	


	if (this->pasued) //Pause menu render
	{
		target->setView(this->window->getDefaultView());
		this->pmenu->render(*target);
	}

	//REMOVE LATER!!!
	
	
}