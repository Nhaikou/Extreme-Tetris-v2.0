#ifndef BLOCKT_H
#define BLOCKT_H

#include "Block.h"

class BlockT : public Block
{
public:
	BlockT(Board* b);
	~BlockT();

	bool spawn();
	void rotate(int direction);
};
#endif;

