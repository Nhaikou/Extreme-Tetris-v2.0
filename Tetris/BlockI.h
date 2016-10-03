#ifndef BLOCKI_H
#define BLOCKI_H

#include "Block.h"

class BlockI : public Block
{
public:
	BlockI(Board *b);
	~BlockI();

	bool spawn();
	void rotate(int direction);
};

#endif