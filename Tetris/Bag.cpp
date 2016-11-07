#include "Bag.h"


Bag::Bag()
{

}


Bag::~Bag()
{
}

void Bag::newBag()
{
	std::vector<unsigned> blockTypes;
	for (int i = 0; i < blockTypeCount; ++i)
	{
		blockTypes.push_back(i);
	}

	unsigned blockType;
	for (int i = 0; i < blockTypeCount; ++i)
	{
		blockType = rand() % blockTypes.size();
		currentBag.push_back(blockTypes[blockType]);
		blockTypes.erase(blockTypes.begin() + blockType);
	}
}

unsigned Bag::getNextBlock()
{
	if (currentBag.size() == 0)
	{
		newBag();
	}
	unsigned nextBlock = currentBag[0];
	currentBag.erase(currentBag.begin());
	return nextBlock;
}