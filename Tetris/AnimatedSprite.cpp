#include "AnimatedSprite.h"


AnimatedSprite::AnimatedSprite()
{

}

AnimatedSprite::AnimatedSprite(sf::Texture tex, sf::Vector2u fSize, float freq)
{
	setTexture(tex);
	frameSize = fSize;
	frequenzy = freq;
	setNumberOfFrames();
}

AnimatedSprite::~AnimatedSprite()
{
}

void AnimatedSprite::update(float dt)
{
	timer += dt;
	if (timer >= frequenzy)
	{
		timer = 0;

		if (direction == -1) // Backward loop (right->left, down->up)
		{
			currentFrame.x--;
			if (currentFrame.x < 0)
			{
				currentFrame.x = numberOfFrames.x - 1;
				currentFrame.y--;
				if (currentFrame.y < 0)
				{
					currentFrame.y = numberOfFrames.y - 1;
				}
			}
		}
		else if (direction == 1) // Forward loop (left->right, up->down)
		{
			currentFrame.x++;
			if (currentFrame.x >= numberOfFrames.x)
			{
				currentFrame.x = 0;
				currentFrame.y++;
				if (currentFrame.y >= numberOfFrames.y)
				{

					currentFrame.y = 0;
				}
			}
		}

		setTextureRect(sf::IntRect(currentFrame.x * frameSize.x, currentFrame.y * frameSize.y, frameSize.x, frameSize.y));
	}
}

void AnimatedSprite::setFrameSize(sf::Vector2u fSize)
{
	frameSize = fSize;
	setNumberOfFrames();
}

void AnimatedSprite::setFrameSize(unsigned width, unsigned height)
{
	frameSize = sf::Vector2u(width, height);
	setNumberOfFrames();
}

void AnimatedSprite::setCurrentFrame(sf::Vector2i curFrame)
{
	currentFrame = curFrame;
}

void AnimatedSprite::setCurrentFrame(unsigned curFrameX, unsigned curFrameY)
{
	currentFrame = sf::Vector2i(curFrameX, curFrameY);
}

void AnimatedSprite::setFrequenzy(float freq)
{
	frequenzy = freq;
}

void AnimatedSprite::setDirection(int dir)
{
	if (dir < 0)
	{
		direction = -1;
	}
	else if (dir == 0)
	{
		direction = dir;
	}
	else
	{
		direction = 1;
	}

	timer = 0;
}

void AnimatedSprite::setNumberOfFrames()
{
	numberOfFrames = sf::Vector2u(getLocalBounds().width / frameSize.x, getLocalBounds().height / frameSize.x);
	setTextureRect(sf::IntRect(currentFrame.x * frameSize.x, currentFrame.y * frameSize.y, frameSize.x, frameSize.y));
}

sf::Vector2u AnimatedSprite::getFrameSize()
{
	return frameSize;
}

sf::Vector2i AnimatedSprite::getCurrentFrame()
{
	return currentFrame;
}

float AnimatedSprite::getFrequenzy()
{
	return frequenzy;
}

int AnimatedSprite::getDirection()
{
	return direction;
}

sf::Vector2u AnimatedSprite::getNumberOfFrames()
{
	return numberOfFrames;
}