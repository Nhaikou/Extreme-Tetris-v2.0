#ifndef BLOCKL_H
#define BLOCKL_H

#include "Block.h"

class BlockL : public Block
{
public:
	BlockL(Board* b);
	~BlockL();

	bool spawn();
	void rotate(int direction);
};
#endif;

