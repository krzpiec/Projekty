#include "AnimationComponent.h"

AnimationCmp::AnimationCmp(sf::Sprite& sprite, sf::Texture& texture_Sheet)
	:sprite(sprite), texture_Sheet(texture_Sheet), Last(nullptr), priorityAnimation(nullptr)
{
}

AnimationCmp::~AnimationCmp()
{
	for (auto &i : this->animations)
		delete i.second;
}

const bool& AnimationCmp::isDone(const std::string key) 
{
	return this->animations[key]->isDone();
}

void AnimationCmp::addAnimation(const std::string key, sf::Vector2f pScale, float animationTimer, int start_frame_x, int start_frame_y, int frames_x, int frames_y, int width, int height, int sheetSize)
{

	this->animations[key] = new Animation(this->sprite, this->texture_Sheet, animationTimer, pScale,
		start_frame_x, start_frame_y, frames_x, frames_y, width, height, sheetSize);

}



const bool& AnimationCmp::play(const std::string key, const float & dt, const bool priority)
{
	if (this->priorityAnimation)
	{
		if (this->priorityAnimation == this->animations[key])
		{
			if (this->Last != this->animations[key])
			{
				if (this->Last != nullptr)
				{
					this->Last->reset();

				}
				this->Last = this->animations[key];
			}
			if (this->animations[key]->play(dt))
			{
				this->priorityAnimation = nullptr;
			}
		}

	}
	else
	{
		if (priority)
		{
			this->priorityAnimation = this->animations[key];
		}
		if (this->Last != this->animations[key])
		{
			if (this->Last != nullptr)
			{
				this->Last->reset();

			}
			this->Last = this->animations[key];
		}
		this->animations[key]->play(dt);
	}
	return this->animations[key]->isDone();
}

const bool& AnimationCmp::play(const std::string key, const float& dt, const float& modifier, const float& modifier_max, const bool priority)
{
	
	if (this->priorityAnimation)
	{
		if (this->priorityAnimation == this->animations[key])
		{
			if (this->Last != this->animations[key])
			{
				if (this->Last != nullptr)
				{
					this->Last->reset();

				}
				this->Last = this->animations[key];
			}
			if (this->animations[key]->play(dt, abs(modifier / modifier_max)))
			{
				this->priorityAnimation = nullptr;
			}
		}
		
	}
	else
	{
		if (priority)
		{
			this->priorityAnimation = this->animations[key];
		}
		if (this->Last != this->animations[key])
		{
			if (this->Last != nullptr)
			{
				this->Last->reset();

			}
			this->Last = this->animations[key];
		}
		this->animations[key]->play(dt, abs(modifier / modifier_max));
	}

	return this->animations[key]->isDone();
}

