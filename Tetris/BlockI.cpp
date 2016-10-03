#include "BlockI.h"

BlockI::BlockI()
{

}

BlockI::~BlockI()
{

}

void BlockI::spawn()
{

}

void BlockI::rotate(int direction)
{
	if (rotation == 0)
	{
		rotation = 1;
	}
	else
	{
		rotation = 0;
	}
}