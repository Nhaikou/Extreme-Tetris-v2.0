#pragma once

#include <vector>

class Bag
{
public:
	Bag();
	~Bag();

	void newBag();
	unsigned getNextBlock();
	
private:
	unsigned blockTypeCount = 7;
	std::vector<unsigned> currentBag;
};

