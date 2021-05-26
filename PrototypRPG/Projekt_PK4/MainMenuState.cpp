#include "MainMenuState.h"



void MainMenuState::initBackground()
{
	if (!this->backgroundtex.loadFromFile("Resources/Images/Backgrounds/MM_cat.jpg"))
	{
		throw "Error Main menu Background didnt load properly";
	}

	this->Background.setSize(
		sf::Vector2f
		(
			static_cast<float>(this->window->getSize().x),
			static_cast<float>(this->window->getSize().y)

		)
	);
	Background.setTexture(&this->backgroundtex);
}

void MainMenuState::initVar()
{
}

void MainMenuState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/DejaVuSans.ttf"))
	{
		throw("ERROR:MainMenu FONT");
	}


}

void MainMenuState::initKeybinds()
{
	std::ifstream plik("Config/MainMenu_keybidns.txt");
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

void MainMenuState::initButtons()
{
	this->buttons["Game_State"] = new gui::Button(500.f, 100.f, 300.f, 60.f, &this->font, "New Game", 
		50, sf::Color(255, 255, 255, 255), sf::Color(128, 128, 128, 200), sf::Color(70, 70, 70, 200),
			sf::Color(10, 100, 70, 0), sf::Color(128,128,128,0), sf::Color(70, 70, 70, 0));

	this->buttons["Settings_State"] = new gui::Button(525.f, 300.f, 250.f, 60.f, &this->font, "Settings",
		50,	sf::Color(255, 255, 255, 255), sf::Color(128, 128, 128, 200), sf::Color(70, 70, 70, 200),
		sf::Color(10, 100, 70, 0), sf::Color(128, 128, 128, 0), sf::Color(70, 70, 70, 0));

	this->buttons["Editor_State"] = new gui::Button(575.f, 500.f, 150.f, 60.f, &this->font, "Editor",
		50,	sf::Color(255, 255, 255, 255), sf::Color(128, 128, 128, 200), sf::Color(70, 70, 70, 200),
		sf::Color(10, 100, 70, 0), sf::Color(128, 128, 128, 0), sf::Color(70, 70, 70, 0));

	this->buttons["Exit_State"] = new gui::Button(575.f, 700.f, 150.f, 60.f, &this->font, "Quit",
		50,	sf::Color(255, 255, 255, 255), sf::Color(128, 128, 128, 200), sf::Color(70, 70, 70, 200),
		sf::Color(10, 100, 70, 0), sf::Color(128, 128, 128, 0), sf::Color(70, 70, 70, 0));

}

MainMenuState::MainMenuState(StateData* state_data)
	:State(state_data)
{
	this->initVar();
	this->initFonts();
	this->initKeybinds();
	this->initButtons();

	this->initBackground();
}


MainMenuState::~MainMenuState()
{
	for (auto it = this->buttons.begin(); it != buttons.end(); it++)
		delete it->second;
}

sf::Text MainMenuState::Show_Mouse_Pos()
{
	sf::Text text;
	text.setPosition(this->mousePosView.x, this->mousePosView.y - 20);
	text.setFont(this->font);
	text.setCharacterSize(16);
	std::stringstream ss;
	ss << this->mousePosView.x << " " << this->mousePosView.y;
	text.setString(ss.str());
	return text;
}

void MainMenuState::updateInput(const float & dt)
{


}



void MainMenuState::updateButtons()
{
	for (auto &it : buttons)
	{
		it.second->update(this->mousePosWindow);
	}
}

void MainMenuState::update(const float & dt)
{
	this->updateMousePos();
	this->updateInput(dt);
	this->updateButtons();
	
	if (this->buttons["Exit_State"]->isPressed())
	{
		this->endState();
	}
	if (this->buttons["Game_State"]->isPressed())
	{
		this->states->push(new GameState(this->stateData));
	}
	if (this->buttons["Settings_State"]->isPressed())
	{
		this->states->push(new SettingState(this->stateData));
	}
	if (this->buttons["Editor_State"]->isPressed())
	{
		this->states->push(new EditorState(this->stateData));
	}
}

void MainMenuState::renderButtons(sf::RenderTarget * target)
{
	for (auto &it : buttons)
	{
		it.second->render(target);
	}
}

void MainMenuState::render(sf::RenderTarget* target)
{
	if (not target)
		target = this->window;
	target->draw(this->Background);
	this->renderButtons(target);

	//mousepos
	//target->draw(Show_Mouse_Pos());
}