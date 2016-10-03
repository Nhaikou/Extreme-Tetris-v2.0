#ifndef BLOCK_H
#define BLOCK_H

class Block
{
public:
	Block();
	~Block();

	void moveLeft();
	void moveRight();
	void moveDown();

private:
	unsigned const tetra = 4;
	unsigned rotation = 0;
};

#endif
