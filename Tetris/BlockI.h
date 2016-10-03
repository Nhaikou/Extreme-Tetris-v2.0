#ifndef BLOCKI_H
#define BLOCKI_H

#include "Block.h"

class BlockI : public Block
{
public:
	BlockI();
	~BlockI();

	void spawn();
	void rotate(int rotation);
};

#endif