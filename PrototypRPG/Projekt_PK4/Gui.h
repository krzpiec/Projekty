#ifndef GUI_H
#define GUI_H


#include <iostream>
#include <ctime>
#include <cstdlib>
#include <sstream>
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include <vector>



enum button_states { btn_IDLE = 0, btn_HOVER, btn_ACTIVE };

namespace gui
{
	class Button
	{
	private:
		short unsigned button_state;
		short unsigned id;

		sf::RectangleShape shape;
		sf::Font* font;
		sf::Text text;


		sf::Color text_idle_color;
		sf::Color text_hover_color;
		sf::Color text_active_color;


		sf::Color idle_color;
		sf::Color hover_color;
		sf::Color active_color;

		sf::Color outlineIdleColor;
		sf::Color outlineHoverColor;
		sf::Color outlineActiveColor;

	public:
		Button(float x, float y, float width, float height, sf::Font* font, std::string text,
			unsigned character_size, sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
			sf::Color idle_color, sf::Color hover_color, sf::Color active_color, 
			sf::Color outline_idle_color = sf::Color::Transparent, sf::Color outline_hover_color = sf::Color::Transparent, sf::Color outline_active_color = sf::Color::Transparent,
			short unsigned id = 0);
		~Button();

		//Accessors
		const bool isPressed() const;

		const std::string getText() const;

		const short unsigned& getId() const;

		//Modif
		void setText(std::string ptext);
		void setId(const short unsigned id);

		//Functions
		void update(const sf::Vector2i& mousePosWindow);
		void render(sf::RenderTarget* target);
	};

	class DropDownList
	{
	private:
		float keytime;
		float keytimeMax;

		sf::Font& font;
		gui::Button* activeElement;
		std::vector<gui::Button*> list;
		bool showList;

	public:
		DropDownList(float x, float y, float width, float height,
			sf::Font& font, std::string list[],
			unsigned nrOfElements, unsigned default_index = 0);
		~DropDownList();

		//Accessors
		const unsigned short& getActiveElementId() const;

		//Functions
		const bool getKeytime();
		void updateKeytime(const float& dt);
		void update(const sf::Vector2i& mousePosWindow, const float& dt);
		void render(sf::RenderTarget& target);
	};



	class TextureSelector
	{
	private:
		float keytime;
		const float keytimeMax;
		float gridSize;
		bool active;
		bool hidden;
		gui::Button* hide_btn;
		sf::RectangleShape bounds;
		sf::Sprite sheet;
		sf::RectangleShape selector;
		sf::Vector2u mousePosGrid;
		sf::IntRect textureRect;

	public:
		TextureSelector(float x, float y, float width, float height,
			float gridSize, const sf::Texture* texture_sheet,
			sf::Font& font, std::string text);
		~TextureSelector();

		//Accessors
		const bool& getActive() const;
		const sf::IntRect& getTextureRect() const;

		//Functions
		const bool getKeytime();
		void hide();
		void updateKeytime(const float& dt);
		void update(const sf::Vector2i& mousePosWindow, const float& dt);
		void render(sf::RenderTarget& target);
	};

}
#endif