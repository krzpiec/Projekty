#ifndef SETTINGSTATE_H
#define SETTINGSTATE_H
#include "State.h"
#include "Gui.h"
class SettingState :
	public State
{
private:
	//Var
	sf::Texture backgroundtex;
	sf::RectangleShape Background;
	sf::Font font;

	std::map<std::string, gui::Button*> buttons;
	std::map<std::string, gui::DropDownList*> dropdownLists;

	sf::Text optionsText;
	std::vector<sf::VideoMode> modes;
	//Functions
	void initBackground();
	void initVar();
	void initFonts();
	void initKeybinds();
	void initGui();
	void initText();
public:
	SettingState(StateData* state_data);
	virtual ~SettingState();


	void updateGui(const float& dt);
	void updateInput(const float& dt);
	void update(const float& dt);
	void renderGui(sf::RenderTarget* target);
	void render(sf::RenderTarget* target);
};

#endif