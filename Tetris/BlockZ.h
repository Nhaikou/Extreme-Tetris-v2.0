#ifndef BLOCKZ_H
#define BLOCKZ_H

#include "Block.h"

class BlockZ : public Block
{
public:
	BlockZ(Board* b);
	~BlockZ();

	bool spawn();
	//void rotate(int direction);
};
#endif;

