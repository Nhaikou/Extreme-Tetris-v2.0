#ifndef BLOCK_H
#define BLOCK_H

#include "Board.h"

class Block
{
public:
	Block(Board *b);
	~Block();

	void moveLeft();
	void moveRight();
	bool moveDown();

	virtual bool spawn();
	virtual void rotate(int direction);

	sf::Color getColor();

	unsigned const tetra = 4;

	std::vector<sf::Vector2i> positions;

protected:
	Board* board;
	int rotation = 0;
	sf::Color color;
};

#endif
