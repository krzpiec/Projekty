#include "SettingState.h"

SettingState::SettingState(StateData* state_data)
	: State(state_data)
{
	this->initVar();
	this->initFonts();
	this->initKeybinds();
	this->initGui();
	this->initText();
	this->initBackground();
}

SettingState::~SettingState()
{
	auto it = this->buttons.begin();
	for (auto it = this->buttons.begin(); it != buttons.end(); it++)
		delete it->second;

	auto it2 = this->dropdownLists.begin();
	for (auto it2 = this->dropdownLists.begin(); it2 != dropdownLists.end(); it2++)
		delete it2->second;
}

void SettingState::initBackground()
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

void SettingState::initVar()
{
	this->modes = sf::VideoMode::getFullscreenModes();
}

void SettingState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/DejaVuSans.ttf"))
	{
		throw("ERROR:MainMenu FONT");
	}


}

void SettingState::initKeybinds()
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

void SettingState::initGui()
{
	

	this->buttons["Exit_State"] = new gui::Button(900.f, 880.f, 250.f, 50.f, &this->font, "Back",
		50, sf::Color(255, 255, 255, 255), sf::Color(128, 128, 128, 200), sf::Color(70, 70, 70, 200),
		sf::Color(10, 100, 70, 0), sf::Color(128, 128, 128, 0), sf::Color(70, 70, 70, 0));


	this->buttons["Apply"] = new gui::Button(1300.f, 880.f, 250.f, 50.f, &this->font, "Apply",
		50, sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	std::vector<std::string> modes_str;
	for (auto& i : this->modes)
	{
		modes_str.push_back(std::to_string(i.width) + 'x' + std::to_string(i.height));
	}

	std::string li[] = { "1920", "1280", "800" };
	this->dropdownLists["RESOLUTION"] = new gui::DropDownList(800, 450, 200, 50, font, modes_str.data(), modes_str.size());

}

void SettingState::initText()
{
	this->optionsText.setFont(this->font);
	this->optionsText.setPosition(sf::Vector2f(100.f, 450.f));
	this->optionsText.setCharacterSize(30);
	this->optionsText.setFillColor(sf::Color(255, 255, 255, 200));



	this->optionsText.setString(
		" Resolution\n\n Fullscreen\n\n Vsync\n\n Antialiasing\n\n"
	);



}


void SettingState::updateInput(const float& dt)
{


}



void SettingState::updateGui(const float& dt)
{




	for (auto& it : buttons)
	{
		it.second->update(this->mousePosWindow);
	}

	if (this->buttons["Exit_State"]->isPressed())
	{
		this->endState();
	}

	if (this->buttons["Apply"]->isPressed())
	{
		this->stateData->gfxSettings->resolution = this->modes[this->dropdownLists["RESOLUTION"]->getActiveElementId()];
		this->window->create(this->stateData->gfxSettings->resolution, this->stateData->gfxSettings->title, sf::Style::Default);
	}
	//////DDl
	for (auto& it : dropdownLists)
	{
		it.second->update(this->mousePosWindow, dt);
	}
}


void SettingState::update(const float& dt)
{
	this->updateMousePos();
	this->updateInput(dt);

	this->updateGui(dt);

	
	


}

void SettingState::renderGui(sf::RenderTarget* target)
{
	for (auto& it : buttons)
	{
		it.second->render(target);
	}

	for (auto& it : dropdownLists)
	{
		it.second->render(*target);
	}
}

void SettingState::render(sf::RenderTarget* target)
{
	if (not target)
		target = this->window;
	target->draw(this->Background);
	this->renderGui(target);
	target->draw(this->optionsText);
	
	//mousepos
	//target->draw(Show_Mouse_Pos());
}