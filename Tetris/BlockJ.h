#ifndef BLOCKJ_H
#define BLOCKJ_H

#include "Block.h"

class BlockJ : public Block
{
public:
	BlockJ(Board* b);
	~BlockJ();

	bool spawn();
	void rotate(int direction);
};
#endif;

