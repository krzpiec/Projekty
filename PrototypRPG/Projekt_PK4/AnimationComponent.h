#ifndef ANIMATIONCOMPONENT_H
#define ANIMATIONCOMPONENT_H

#include <string>
#include <map>
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Network.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include <fstream>
#include <iostream>
class AnimationCmp
{
private:

	class Animation
	{
	public:
		//Var
		sf::Sprite& sprite;
		sf::Texture& texSheet;

		int spritesheetSize;
		float animationTimer;
		float timer;
		bool done;
		int width;
		int height;
		sf::IntRect startRect;
		sf::IntRect currentRect;
		sf::IntRect endRect;
		

		
		Animation(sf::Sprite& sprite, sf::Texture& texSheet, 
			float animationTimer, sf::Vector2f Scale, int start_frame_x, int start_frame_y, int frames_x, int frames_y, int width, int height, int sheetSize)
			:sprite(sprite),texSheet(texSheet), animationTimer(animationTimer),timer(0.f), done(false), width(width), height(height)
		{

			this->spritesheetSize = sheetSize;
	
			this->startRect = sf::IntRect(start_frame_x * width, start_frame_y * height,width, height);
			this->currentRect = this->startRect;
			this->endRect = sf::IntRect(frames_x * width, frames_y * height, width, height);
			this->sprite.setScale(Scale);
			this->sprite.setTexture(this->texSheet);
			this->sprite.setTextureRect(this->startRect);
		};
		~Animation() {};



		//Funcions

		const bool& play(const float& dt)
		{
			this->done = false;
			this->timer += 100.f * dt;
			if (this->timer >= this->animationTimer)
			{
				this->timer = 0.f;

				//Animation
				if (this->currentRect != this->endRect)
				{
					if (this->currentRect.left + this->width <= this->width * this->spritesheetSize)
						this->currentRect.left += this->width;
					else
					{

						this->currentRect.left = 0;
						this->currentRect.top += this->height;
					}
				}
				else//reset animation
				{
					this->currentRect.left = this->startRect.left;
					this->currentRect.top = this->startRect.top;
					done = true;
				}

				this->sprite.setTextureRect(this->currentRect);
			}
			return this->done;
		}

		const bool& isDone() 
		{
			return this->done;
		}

		const bool& play(const float& dt, float modifier)
		{
			if (modifier < 0.5f)
				modifier = 0.5f;

			this->done = false;

			this->timer += modifier*100.f * dt;
			if (this->timer >= this->animationTimer)
			{
				this->timer = 0.f;
				
				//Animation
				if (this->currentRect != this->endRect)
				{
					if(this->currentRect.left + this->width <= this->width * this->spritesheetSize )
						this->currentRect.left += this->width;
					else
					{
						
						this->currentRect.left = 0;
						this->currentRect.top += this->height;
					}
				}
				else//reset animation
				{
					this->currentRect.left = this->startRect.left;
					this->currentRect.top = this->startRect.top;
					done = true;
				}

				this->sprite.setTextureRect(this->currentRect);
			}
			return this->done;
		}


		void reset()
		{
			this->timer = this->animationTimer;
			this->currentRect = this->startRect;
		}
	};


	sf::Sprite& sprite;
	sf::Texture& texture_Sheet;
	std::map<std::string, Animation*> animations;
	Animation* Last;
	Animation* priorityAnimation;
public:
	AnimationCmp(sf::Sprite& sprite, sf::Texture& texture_Sheet);
	~AnimationCmp();

	const bool& isDone(const std::string key);
	

	//Functions
	void addAnimation(const std::string key, sf::Vector2f Scale, float animationTimer, int start_frame_x, int start_frame_y,
		int frames_x, int frames_y, int width, int height, int sheetSize);


	const bool& play(const std::string key, const float& dt, const bool priority = false);
	const bool& play(const std::string key, const float& dt, const float& modifier, const float& modifier_max, const bool priority = false);
};

#endif 