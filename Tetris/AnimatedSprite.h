#ifndef ANIMATEDSPRITE_H
#define ANIMATEDSPRITE_H

#include <SFML/Graphics.hpp>

// Note: The right texture has to be set before frameSize since frameSize divides the current texture
//       Wrong texture results in wrong frame dimensions.

enum Direction : int
{
	FORWARD = 1,
	BACKWARD = -1,
	PAUSED = 0
};

class AnimatedSprite : public sf::Sprite
{
public:
	AnimatedSprite();
	AnimatedSprite(sf::Texture tex, sf::Vector2u fSize, float freq);
	~AnimatedSprite();

	void update(float dt);

	void setFrameSize(sf::Vector2u fSize);
	void setFrameSize(unsigned width, unsigned height);
	void setCurrentFrame(sf::Vector2i curFrame);
	void setCurrentFrame(unsigned curFrameX, unsigned curFrameY);
	void setFrequenzy(float freq);
	void setDirection(int dir); // Direction::FORWARD (1) || Direction::BACKWARD (-1) || Direction::PAUSED (0)

	sf::Vector2u getFrameSize();
	sf::Vector2i getCurrentFrame();
	float getFrequenzy();
	int getDirection();
	sf::Vector2u getNumberOfFrames();

protected:
	void setNumberOfFrames();

private:
	int direction = 1;
	float timer = 0, frequenzy = 0;
	sf::Vector2u frameSize = { 0, 0 }, numberOfFrames = { 0, 0 };
	sf::Vector2i currentFrame = { 0, 0 };
	sf::Texture texture;
};

#endif