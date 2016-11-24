#ifndef BLOCK_H
#define BLOCK_H

#include "Board.h"

class Block
{
public:
	Block(Board *b);
	~Block();

	// Move functions for the current block that is in play
	void moveLeft();
	void moveRight();
	unsigned hardDrop();
	bool moveDown();

	virtual bool spawn(); // Goes to the spawn function of the block type that is spawned
	virtual void rotate(int direction); // Goes to the rotate function of the block type that is currently in play
	
	unsigned const tetra = 4; // All block types in Tetris consist of 4 smaller blocks, hence the name Tetris, useful in loops so you can get an idea why there's a 4
	std::vector<sf::Vector2i> positions; // X and Y positions of the 4 smaller blocks in the grid

	unsigned getType();

protected:
	Board* board; // Pointer to the game board
	int rotation = 0; // Current rotation of the block, can vary between block types, up to 4 different rotations
	unsigned type; // Type of the current block
};

#endif
