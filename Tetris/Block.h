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

	unsigned const tetra = 4;

protected:
	Board* board;
	int rotation = 0;
	std::vector<sf::Vector2i> positions;
	sf::Color color;
};

#endif
