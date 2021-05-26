#ifndef MainMenuState_H
#define MainMenuState_H

#include "GameState.h"
#include "Gui.h"
#include "SettingState.h"
#include "EditorState.h"
class MainMenuState :
	public State
{
private:
	//Var
	
	sf::Texture backgroundtex;
	sf::RectangleShape Background;
	sf::Font font;
	
	std::map<std::string, gui::Button*> buttons;

	//Functions
	void initBackground();
	void initVar();
	void initFonts();
	void initKeybinds();
	void initButtons();
public:
	MainMenuState(StateData* state_data);
	virtual ~MainMenuState();

	sf::Text Show_Mouse_Pos(); //Debug, buttons

	void updateButtons();
	void updateInput(const float & dt);
	void update(const float & dt);
	void renderButtons(sf::RenderTarget* target);
	void render(sf::RenderTarget* target);



};
#endif // !MainMenuState_H

