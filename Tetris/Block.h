#ifndef BLOCK_H
#define BLOCK_H

#include "Board.h"

class Block
{
public:
	Block();
	~Block();

	void moveLeft(Board *board);
	void moveRight(Board *board);
	void moveDown(Board *board);

	virtual void spawn();
	virtual void rotate(int direction);

	unsigned const tetra = 4;
	int rotation = 0;
};

#endif
