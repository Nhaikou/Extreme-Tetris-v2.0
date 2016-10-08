#ifndef BLOCKS_H
#define BLOCKS_H

#include "Block.h"

class BlockS : public Block
{
public:
	BlockS(Board* b);
	~BlockS();

	bool spawn();
	void rotate(int direction);
};
#endif;

