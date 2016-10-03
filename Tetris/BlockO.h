#ifndef BLOCKO_H
#define BLOCKO_H

#include "Block.h"

class BlockO : public Block
{
public:
	BlockO(Board* b);
	~BlockO();

	bool spawn();
};
#endif;

